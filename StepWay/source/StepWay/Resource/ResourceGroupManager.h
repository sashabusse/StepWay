#pragma once
#include "IResourceBank.h"
#include <map>
#include <vector>
#include <set>

//Files scope
//TODO:
//	1. rework ResourceGroupHandler to operate on groups safely


//this classes extensively use std::string replace later
namespace StepWay
{



	//this class extensively use std::string replace later
	//invalid supposes for now
	//	1. File names in all banks totally are unique
	class ResourceGroup
	{
	public:
		ResourceGroup(const std::string& name);
		~ResourceGroup();

		//Returns Bank pointer or nullptr if there is no such a resource.
		IResourceBank* GetBankByResourceName(std::string resName);

		bool AddBank(const std::string& path, BankType type);

		bool DeclareResource(const std::string& filename);

		void Clear();

	private:
		//here is a probable problem cause probably not suitable containers used
		typedef std::map<std::string, IResourceBank*> NameToBankMap;
		NameToBankMap m_NameToBank;


		typedef std::map<std::string,IResourceBank*> ResourceBankPtrs;
		ResourceBankPtrs m_ResourceBanks;

		typedef std::vector < std::pair<std::string, IResourceBank*>> DeclaredVec;
		DeclaredVec m_declaredResources;

		std::string m_name;
	};


	class ResGroupHandle
	{
	public:
		ResGroupHandle(ResourceGroup* ptr) :
			m_ptr(ptr) {};
		~ResGroupHandle() {};

		//returns valid ptr if exist else nullptr
		//dont work properly now
		inline ResourceGroup* GetPtr() const { return m_ptr; };
	private:
		ResourceGroup* m_ptr;
	};



	//certain SINGLETON class for managing reourse groups
	//Responsibilities:
	//	1. Create and manage Resource groups
	//	2. Manage right resource loading (e.g. provide right resourceManagers for right resource types)
	//	3. Contain and prepare ResourceBanks for Loading resources from them
	class ResourceGroupManager
	{
	//SINGLETON MEMBERS--------------------------may be should be inhereted later
	public:
		static bool Init();
		static void Destroy();


		static ResourceGroupManager* GetInstacePtr();
		static ResourceGroupManager& GetInstance();
	private:
		static ResourceGroupManager* m_instance;
		ResourceGroupManager() {};//??????????????????????????????????
	//----------------------------------------------------------------------------
	public:
		~ResourceGroupManager();


		void AddGroup(const std::string& groupname);
		void RemoveGroup(const std::string& groupname);
		void RemoveAllGroups();
		
		ResGroupHandle FindGroup(const std::string& groupname) const;

		bool AddResourceBank(const std::string& path,BankType type,const std::string& groupname);
	private:

		typedef std::map<std::string, ResourceGroup*> ResourceGroupMap;
		ResourceGroupMap m_groups;

		ResGroupHandle _CreateGroup(const std::string& groupname);
	};



}