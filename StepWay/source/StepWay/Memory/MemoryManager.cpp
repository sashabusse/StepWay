#include "StepWayPCH.h"
#include "MemoryManager.h"

StepWay::MemoryManager::MemoryManager()
{

}
StepWay::MemoryManager::~MemoryManager()
{
}



void StepWay::MemoryManager::Init()
{
	m_SysMemInfo = UpdateSystemMemoryInfo();
}

void StepWay::MemoryManager::Destroy()
{
}

StepWay::SystemMemoryInfo::SystemMemoryInfo(uint64 _VirtualMemoryTotal, uint64 _VirtualMemoryAvail, uint64 _PhysMemoryTotal, uint64 _PhysMemoryAvail) :
	VirtualMemoryTotal(_VirtualMemoryTotal),
	VirtualMemoryAvail(_VirtualMemoryAvail),
	PhysMemoryTotal(_PhysMemoryTotal),
	PhysMemoryAvail(_PhysMemoryAvail) {};
