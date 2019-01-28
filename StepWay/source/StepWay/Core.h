#pragma once
//always include first cause definition below

#ifdef SW_PLATFORM_WINDOWS
	#ifdef SW_BUILD_DLL
		#define SW_API __declspec(dllexport)
	#else
		#define SW_API __declspec(dllimport)
	#endif
#else
	#error StepWay works ony under windows
#endif


//define memory leak detection
//should be defined before <cstdio.h>
//To enable need to be compiled in debug and use SW_DEBUG
#if defined(SW_PLATFORM_WINDOWS) && defined(_DEBUG) && defined(SW_DEBUG)
	#ifndef _CRTDBG_MAP_ALLOC
		#define _CRTDBG_MAP_ALLOC
	#endif
	#include <crtdbg.h>
#endif

