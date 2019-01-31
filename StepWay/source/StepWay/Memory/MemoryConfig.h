#pragma once

//force not to override new operator
#define SW_FORCE_STD_NEW 0
//force use malloc for all MALLOC macros
#define SW_FORCE_STD_MALLOC 0

//specify set of allocators used
//-----------------------------------------------------
#define SW_MEMORY_ALLOC_STD 1

#define SW_MEMORY_ALLOC_SYSTEM SW_MEMORY_ALLOC_STD
//-----------------------------------------------------


#define SW_SIMD_ALIGNMENT 16

#define SW_CACHE_LINE_ALIGNMENT 64	//common for x86