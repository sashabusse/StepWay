#include "StepWayPCH.h"
#include "Memory/MemoryManager.h"



StepWay::SystemMemoryInfo StepWay::MemoryManager::UpdateSystemMemoryInfo()
{
	MEMORYSTATUSEX memStat;
	memStat.dwLength = sizeof(memStat);

	GlobalMemoryStatusEx(&memStat);

	return SystemMemoryInfo(memStat.ullTotalVirtual, memStat.ullAvailVirtual, memStat.ullTotalPhys, memStat.ullAvailPhys);
}
