#include "StepWayPCH.h"
#include "OS.h"

#ifdef SW_PLATFORM_WINDOWS
#include "Win32/Win32OS.h"
#endif


namespace StepWay
{
	OS* OS::Create()
	{
#ifdef SW_PLATFORM_WINDOWS
		return new Win32::Win32OS();
#else
		SW_CORE_ASSERT(false, "no support for this OS");
		return nullptr;
#endif 
	}
}