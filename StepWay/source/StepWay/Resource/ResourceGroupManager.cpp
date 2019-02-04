#include "StepWayPCH.h"
#include "ResourceGroupManager.h"
#include "Memory/Memory.h"


StepWay::ResourceGroupManager* StepWay::ResourceGroupManager::m_instance = nullptr;


StepWay::ResourceGroup::ResourceGroup(const std::string& name):
	m_name(name)
{
}



StepWay::ResourceGroup::~ResourceGroup()
{
	Clear();
}



StepWay::IResourceBank * StepWay::ResourceGroup::GetBankByResourceName(std::string resName)
{
	auto it = m_NameToBank.find(resName);
	if (it != m_NameToBank.end())
		return it->second;
	return nullptr;
}




bool StepWay::ResourceGroup::AddBank(const std::string & path, BankType type)
{
	if (m_ResourceBanks.find(path) != m_ResourceBanks.end())
	{
		SW_CORE_WARNING("attemp to add bank that already added");
		return false;
	}

	typedef std::pair<std::string, IResourceBank*> MapElement;
	IResourceBank* newBank = IResourceBank::CreateResourceBank(path, type);

	SW_ASSERT(newBank != nullptr, "Failed to create Bank");
	
	m_ResourceBanks.insert(MapElement(path,newBank));

	std::vector<std::string> names = newBank->GetFileNames();
	for (auto it = names.begin(); it != names.end(); ++it)
	{
		m_NameToBank.emplace(*it, newBank);
	}
	return true;
}

bool StepWay::ResourceGroup::DeclareResource(const std::string & filename)
{
	auto it = m_NameToBank.find(filename);
	if (it == m_NameToBank.end())
		return false;

	m_declaredResources.push_back(*it);
	return true;
}





void StepWay::ResourceGroup::Clear()
{
	m_NameToBank.clear();
	for (IResourceBank* bank : m_ResourceBanks)
		SW_DELETE bank;
	m_ResourceBanks.clear();
}





bool StepWay::ResourceGroupManager::Init()
{
	SW_ASSERT(m_instance == nullptr, "resourceGroupManager has already been initialized");
	m_instance = SW_NEW ResourceGroupManager;
	return true;
}





void StepWay::ResourceGroupManager::Destroy()
{
	m_instance->RemoveAllGroups();
	SW_DELETE m_instance;
}

StepWay::ResourceGroupManager * StepWay::ResourceGroupManager::GetInstacePtr()
{
	SW_ASSERT(m_instance != nullptr, "ResourceGroupManager has not been initialized yet");
	return m_instance;
}

StepWay::ResourceGroupManager & StepWay::ResourceGroupManager::GetInstance()
{
	SW_ASSERT(m_instance != nullptr, "ResourceGroupManager has not been initialized yet");
	return *m_instance;
}





void StepWay::ResourceGroupManager::AddGroup(const std::string & groupname)
{
	if (!FindGroup(groupname).GetPtr())
		_CreateGroup(groupname);
}





void StepWay::ResourceGroupManager::RemoveGroup(const std::string & groupname)
{
	auto it = m_groups.find(groupname);
	if (it == m_groups.end())
	{
		SW_WARNING("call to delete resource group that doesnt exist");
		return;
	}
	SW_DELETE it->second;
	m_groups.erase(it);
}





void StepWay::ResourceGroupManager::RemoveAllGroups()
{
	for (auto it = m_groups.begin(); it != m_groups.end(); ++it)
	{
		SW_DELETE it->second;
	}
	m_groups.clear();
}




bool StepWay::ResourceGroupManager::AddResourceBank(const std::string& path, BankType type,const std::string& groupname)
{
	ResGroupHandle group = FindGroup(groupname);
	if (group.GetPtr() == nullptr)
		group = _CreateGroup(groupname);
	
	return group.GetPtr()->AddBank(path, type);
}





StepWay::ResourceGroupManager::~ResourceGroupManager()
{
}




StepWay::ResGroupHandle StepWay::ResourceGroupManager::FindGroup(const std::string & groupname) const
{
	auto it = m_groups.find(groupname);
	if (it != m_groups.end())
		return ResGroupHandle(it->second);
	return ResGroupHandle(nullptr);
}




StepWay::ResGroupHandle StepWay::ResourceGroupManager::_CreateGroup(const std::string& groupname)
{
	ResGroupHandle ret(SW_NEW ResourceGroup(groupname));
	m_groups.emplace(groupname, ret.GetPtr());
	return ret;
}
