#include "StepWayPCH.h"
#include "IResourceBundle.h"
#include "Memory/Memory.h"


//This factory method is not written yet
StepWay::IResourceBundle * StepWay::IResourceBundle::CreateResourceBank(const std::string & path, BundleType type)
{
	SW_ASSERT(type != BundleType::INVALID, "Invalid BankType");
	switch (type)
	{
	case BundleType::DEBUG:
		return SW_NEW DebugResourceBundle(path);
		break;
	default:
		SW_ASSERT(false,"wrong BankType, no one of existing matches")
		break;
	}
	return nullptr;
}
