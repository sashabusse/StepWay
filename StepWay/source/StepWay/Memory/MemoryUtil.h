#pragma once
#include "Core.h"


SW_API void* AlignedMalloc(size_t size, size_t alignment);
SW_API void  AlignedFree(void* ptr);

