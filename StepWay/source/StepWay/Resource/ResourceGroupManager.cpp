#include "StepWayPCH.h"
#include "Memory/Memory.h"
#include "ResourceGroupManager.h"


StepWay::ResourceGroupManager* StepWay::ResourceGroupManager::m_pInstance = nullptr;

bool StepWay::ResourceGroupManager::Init()
{
	m_pInstance = SW_NEW ResourceGroupManager();
	return m_pInstance != nullptr;
}

void StepWay::ResourceGroupManager::Destroy()
{
	m_pInstance->ClearResBundles();
	SW_DELETE m_pInstance;
}


//if exist return ptr to it
//or create new and return ptr to it
StepWay::IResourceBundle* StepWay::ResourceGroupManager::AddResBundle(const std::string & path, BundleType type)
{
	auto it = m_Bundles.find(path);
	if (it != m_Bundles.end())
	{
		return it->second;
	}
	IResourceBundle* ret = IResourceBundle::CreateResourceBundle(path, type);
	if(ret!=nullptr)
		m_Bundles.emplace(path,ret);
	return ret;
}

bool StepWay::ResourceGroupManager::RemoveResBundle(const std::string & path)
{
	auto it = m_Bundles.find(path);
	if (it == m_Bundles.end())
		return false;
	it->second->Destroy();
	SW_DELETE it->second;
	m_Bundles.erase(it);
	return true;
}

void StepWay::ResourceGroupManager::ClearResBundles()
{
	for (auto it = m_Bundles.begin(); it != m_Bundles.end(); it++)
	{
		SW_DELETE it->second;
	}
	m_Bundles.clear();
}

int StepWay::ResourceGroupManager::GetResBundleCount() const
{
	return (int)m_Bundles.size();
}

StepWay::IResourceBundle * StepWay::ResourceGroupManager::GetResBundle(const std::string & path) const
{
	auto it = m_Bundles.find(path);
	if (it == m_Bundles.end())
		return nullptr;
	return it->second;
}
