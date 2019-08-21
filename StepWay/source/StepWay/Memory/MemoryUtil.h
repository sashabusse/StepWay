#pragma once
#include "Core.h"


void* AlignedMalloc(size_t size, size_t alignment);
void  AlignedFree(void* ptr);

