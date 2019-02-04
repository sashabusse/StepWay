#include "StepWayPCH.h"
#include "IResourceBank.h"
#include "Memory/Memory.h"


//This factory method is not written yet
StepWay::IResourceBank * StepWay::IResourceBank::CreateResourceBank(const std::string & path, BankType type)
{
	SW_ASSERT(type != BankType::INVALID, "Invalid BankType");
	switch (type)
	{
	case BankType::DEBUG:
		return SW_NEW DebugResourceBank(path);
		break;
	default:
		SW_ASSERT(false,"wrong BankType, no one of existing matches")
		break;
	}
	return nullptr;
}
