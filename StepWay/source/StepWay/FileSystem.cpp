#include "StepWayPCH.h"
#include "FileSystem.h"


#ifdef SW_PLATFORM_WINDOWS
#include "Win32/Win32FileSystem.h"
#endif

namespace StepWay
{
	FileSystem* FileSystem::Create()
	{
#ifdef SW_PLATFORM_WINDOWS
		return new Win32::Win32FileSystem();
#else
		SW_CORE_ASSERT(false, "no support for this OS");
		return nullptr;
#endif 
	}
}