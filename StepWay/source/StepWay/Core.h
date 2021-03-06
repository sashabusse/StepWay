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

#ifdef SW_DEBUG
#define DBG_BREAK() __debugbreak()
#else
#define DBG_BREAK()
#endif

#define SW_ASSERT(cond, ...)\
 {if(!(cond)){SW_ERROR("Assertion failed on condition: {}",#cond);\
			SW_ERROR("In function {2}\n\t\t{0}:{1}",__FILE__, __LINE__, __FUNCTION__);\
			SW_ERROR("assertion message(arg):");\
			SW_ERROR(__VA_ARGS__);DBG_BREAK();}}


#define SW_CORE_ASSERT(cond, ...)\
 {if(!(cond)){SW_CORE_ERROR("Assertion failed on condition: {}",#cond);\
			SW_CORE_ERROR("In function {2}\n\t\t{0}:{1}",__FILE__, __LINE__, __FUNCTION__);\
			SW_CORE_ERROR("assertion message(arg):");\
			SW_CORE_ERROR(__VA_ARGS__);DBG_BREAK();}}


#define SW_BIND_METH(meth, ...) std::bind(&meth,this,__VA_ARGS__)
#define SW_BIND_METH_TO(meth, inst, ...) std::bind(&meth, inst, __VA_ARGS__)
#define SW_BIND_METH_1(meth) std::bind(&meth,this,std::placeholders::_1)
#define SW_BIND_METH_1_TO(meth, inst) std::bind(&meth,inst,std::placeholders::_1)


#define BIT(x) (1<<x)
