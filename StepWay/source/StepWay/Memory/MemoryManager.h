#pragma once
#include "Core.h"
#include "Types.h"


namespace StepWay
{

	struct SystemMemoryInfo
	{
		uint64 VirtualMemoryTotal;
		uint64 VirtualMemoryAvail;
		uint64 PhysMemoryTotal;
		uint64 PhysMemoryAvail;
		SystemMemoryInfo() {};
		SystemMemoryInfo(uint64 _VirtualMemoryTotal , uint64 _VirtualMemoryAvail , uint64 _PhysMemoryTotal , uint64 _PhysMemoryAvail);
	};


	class MemoryManager
	{
	public:
	private:
		SystemMemoryInfo m_SysMemInfo;

	public:
		MemoryManager();
		~MemoryManager();

		void SetUp();
		void ShutDown();

		inline SystemMemoryInfo GetSystemMemoryInfo() { return m_SysMemInfo; };

	private:
		SystemMemoryInfo UpdateSystemMemoryInfo();
	};

}