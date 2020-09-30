#pragma once


namespace StepWay
{
	class FileSystem
	{
	public:
		static FileSystem* Create();

		virtual std::vector<std::string> FileChooseDialog() = 0;
		virtual std::string GetWorkingDirectory() = 0;

		virtual ~FileSystem() {};
	private:
	};
}