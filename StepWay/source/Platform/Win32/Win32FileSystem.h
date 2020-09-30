#include "FileSystem.h"
#include <vector>
#include <string>

namespace StepWay
{
	namespace Win32
	{

		class Win32FileSystem : public FileSystem
		{
		public:
			virtual std::vector<std::string> FileChooseDialog() override;
			virtual std::string GetWorkingDirectory() override;
		private:
		};

	}
}