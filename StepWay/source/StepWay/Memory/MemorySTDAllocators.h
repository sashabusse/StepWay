#pragma once
#include "Core.h"
#include <stdlib.h>
#include <limits>
#include "MemoryUtil.h"


class MemorySTDAllocator
{
public:
	static inline void* Allocate(size_t size) { return malloc(size); };
	static inline void Free(void* ptr) { free(ptr); };
	static inline size_t MaxAllocation() { return std::numeric_limits<size_t>::max(); }
};

template<int Alignment>
class MemorySTDAlignedAllocator
{
public:
	static void* Allocate(size_t size);
	static void Free(void* ptr);
	static inline size_t MaxAlloc() { return std::numeric_limits<size_t>::max() - Alignment; }
};

template<int Alignment>
inline void * MemorySTDAlignedAllocator<Alignment>::Allocate(size_t size)
{
	return AlignedMalloc(size,Alignment);
}

template<int Alignment>
inline void MemorySTDAlignedAllocator<Alignment>::Free(void * ptr)
{
	AlignedFree(ptr);
}
