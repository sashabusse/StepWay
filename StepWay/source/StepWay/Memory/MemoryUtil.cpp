#include "StepWayPCH.h"
#include "MemoryUtil.h"



void * AlignedMalloc(size_t size, size_t alignment)
{
#ifdef SW_MSVC
	return _aligned_malloc(size, alignment);
#else
	uint unaligned = reinterpret_cast<uint>(malloc(size + alignment));
	ubyte offset = alignment - (unaligned & (alignment - 1));
	ubyte* ret = reinterpret_cast<ubyte*>(unaligned + offset);
	*(ret - 1) = offset;
	return reinterpret_cast<void*>(ret);
#endif
}

void AlignedFree(void * ptr)
{
#ifdef SW_MSVC
	_aligned_free(ptr);
#else
	ubyte offset = *(reinterpret_cast<ubyte*>(ptr) - 1);
	free(reinterpret_cast<char*>(ptr) - offset);
#endif
}
