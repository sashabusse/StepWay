#include "Core.h"
#include "IResourceBundle.h"

#include <string>
#include <map>


namespace StepWay
{

	//represents Resource Locatrion inside ResourceGroupManager
	struct ResourceLocator
	{
		std::string path;
		IResourceBundle* pBundle;
	};

	class ResourceGroupManager
	{
		//SINGLETON functions
	public:
		static bool Init();
		static void Destroy();
		static ResourceGroupManager* GetInstancePtr() { return m_pInstance; };
		static ResourceGroupManager& GetInstanceRef() { return *m_pInstance; };
	private:
		static ResourceGroupManager* m_pInstance;
		//-------------------
	public:
		~ResourceGroupManager() {};

		//bundle management functions 
		//refactor later to use handles or something else to manage acces to bundles
		IResourceBundle* AddResBundle(const std::string& path, BundleType type);
		bool RemoveResBundle(const std::string& path);
		void ClearResBundles();
		int GetResBundleCount()const;
		IResourceBundle* GetResBundle(const std::string& path) const;

		//loading functions
		


	private:
		ResourceGroupManager() {};

		std::map<std::string, IResourceBundle*> m_Bundles;
	};


}