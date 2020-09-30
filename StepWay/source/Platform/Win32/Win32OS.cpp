#include "StepWayPCH.h"
#include "Win32OS.h"

#include <Ole2.h>
namespace StepWay
{
	namespace Win32
	{
		void Win32OS::SetUp()
		{
			OleInitialize(NULL);
		}

		void Win32OS::ShutDown()
		{
			OleUninitialize();
		}
	}
}
