#pragma once
#include "OS.h"

namespace StepWay
{
	namespace Win32
	{
		class Win32OS : public OS
		{
		public:
			virtual void SetUp() override;
			virtual void ShutDown() override;
		};
	}
}