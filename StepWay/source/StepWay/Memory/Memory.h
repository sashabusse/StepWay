#pragma once
#include "MemoryConfig.h"
#include "Core.h"


/*    Not realised yet
//override-allocators-here----------------------------------------------|
//should suply static members:
//public:
//	static void* Allocate(size_t size);
//	static void Free(void* ptr);
//	static size_t MaxAllocation();
//	--------------------------------------------------------------------|
//	probably add later
//	static void* AllocateDebug(size_t size,const char* file,int line);
//	static void FreeDebug(void* ptr);

#if SW_MEMORY_ALLOC_SYSTEM == SW_MEMORY_ALLOC_STD
#include "MemorySTDAllocators.h"
namespace StepWay
{
	class GlobalAllocator :public MemorySTDAllocator
	{};

	template<int Alignment>
	class GlobalAlignedAllocator :public MemorySTDAlignedAllocator<Alignment>
	{
		int AlignmentCheck[Alignment <= 128 && ((Alignment&(Alignment - 1)) == 0) ? +1 : -1];//alignment check
	};
}
#endif

//allocators-overriden---------------------------------------------------|


#if !SW_FORCE_STD_NEW
inline void* operator new  (std::size_t count)
{
	return ::StepWay::GlobalAllocator::Allocate(count);
}

inline void* operator new[](std::size_t count)
{
	return ::StepWay::GlobalAllocator::Allocate(count);
}

inline void operator delete  (void* ptr)
{
	::StepWay::GlobalAllocator::Free(ptr);
}

inline void operator delete[](void* ptr)
{
	::StepWay::GlobalAllocator::Free(ptr);
}
#endif
*/


#if defined(SW_USE_CRT_DBG) && defined(_DEBUG)
	#define _CRTDBG_MAP_ALLOC
	#include <crtdbg.h>
#endif


#if defined(SW_USE_CRT_DBG) && defined(_DEBUG)
#define SW_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define SW_NEW								new
#endif
#define SW_DELETE							delete


/*
#if !SW_FORCE_STD_MALLOC

#define SW_MALLOC(size)						::StepWay::GlobalAllocator::Allocate(size)
#define SW_FREE(ptr)						::StepWay::GlobalAllocator::Free(ptr)

#define SW_ALIGNED_MALLOC(size,alignment)	::StepWay::GlobalAlignedAllocator<alignment>::Allocate(size)
#define SW_ALIGNED_FREE(ptr)				::StepWay::GlobalAlignedAllocator<1>::Free(ptr)

#define SW_SIMD_MALLOC(size_in_bytes)		SW_ALIGNED_MALLOC(size_in_bytes,SW_SIMD_ALIGNMENT)
#define SW_SIMD_FREE(ptr)					SW_ALIGNED_FREE(ptr)

#define SW_CACHE_LINE_MALLOC(size_in_bytes)	SW_ALIGNED_MALLOC(size_in_bytes,SW_CACHE_LINE_ALIGNMENT)
#define SW_CACHE_LINE_FREE(ptr)				SW_ALIGNED_FREE(ptr)

#else

#define SW_MALLOC(size)						malloc(size)
#define SW_FREE(ptr)						free(ptr)

#define SW_ALIGNED_MALLOC(size,alignment)	malloc(size)
#define SW_ALIGNED_FREE(ptr)				free(ptr)

#define SW_SIMD_MALLOC(size_in_bytes)		malloc(size)
#define SW_SIMD_FREE(ptr)					free(ptr)

#define SW_CACHE_LINE_MALLOC(size_in_bytes)	malloc(size)
#define SW_CACHE_LINE_FREE(ptr)				free(ptr)

#endif
*/






