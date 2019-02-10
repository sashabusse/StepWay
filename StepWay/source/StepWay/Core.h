#pragma once
//always include first cause definition below

#ifdef SW_PLATFORM_WINDOWS
	#ifdef SW_BUILD_DLL
		#define SW_API __declspec(dllexport)
	#elif defined(SW_USE_DLL)
		#define SW_API __declspec(dllimport)
	#else
		#define SW_API
	#endif
#else
	#error StepWay works ony under windows
#endif


#define DBG_BREAK __debugbreak

#define SW_ASSERT(cond, ...)\
 {if(!(cond)){SW_ERROR("Assertion failed on condition: {}",#cond);\
			SW_ERROR("assertion message(arg): {}",__VA_ARGS__);DBG_BREAK();}}

#define SW_CORE_ASSERT(cond, ...)\
 {if(!(cond)){SW_ERROR("Assertion failed on condition: {}",#cond);\
			SW_ERROR("assertion message(arg): {}",__VA_ARGS__);DBG_BREAK();}}



#define BIT(x) (1<<x)