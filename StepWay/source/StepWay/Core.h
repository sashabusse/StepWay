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


#define SW_ASSERT(cond, ...)\
 {if(!(cond)){SW_ERROR("Assertion failed on condition: {}",#cond);\
			SW_ERROR("assertion message(arg): {}",__VA_ARGS__);__debugbreak();}}

#define SW_CORE_ASSERT(cond, ...)\
 {if(!cond){SW_ERROR("Assertion failed on condition: {}",#cond);\
			SW_ERROR("assertion message(arg): {}",__VA_ARGS__);__debugbreak();}}


#define BIT(x) (1<<x)