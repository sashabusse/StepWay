#pragma once
#include <string>
#include <vector>


namespace StepWay
{

	
	enum class BundleType : int
	{
		DEBUG = -1,
		INVALID = 0,
		FILESYSTEM_FOLDER,
		ZIP_ARCHIVE
	};



#define SW_DECLARE_BUNDLE_TYPE(type)\
	static BundleType GetStaticBundleType(){return type;}\
	virtual BundleType GetBundleType() const override {return GetStaticBundleType();}\
	virtual std::string GetBundleTypeString() const override {return #type;}




	//extensive use of std::string remove later
	//Interface for resource sets like fileSystemFolders and Zip archieves
	class SW_API IResourceBundle
	{
	public:
		//factory method
		static IResourceBundle* CreateResourceBundle(const std::string& path, BundleType type);

		virtual bool Init() { return true; };
		virtual void Destroy() {};

		//Use macro to ovrride this two
		virtual BundleType GetBundleType() const = 0;
		virtual std::string GetBundleTypeString() const = 0;

		
		virtual ~IResourceBundle() {};
	protected :
		IResourceBundle() {};
	};



	class SW_API DebugResourceBundle : public IResourceBundle
	{
	public:
		SW_DECLARE_BUNDLE_TYPE(BundleType::DEBUG);

		DebugResourceBundle(const std::string& path):m_path(path) {};
	private:
		std::string m_path;
	};


}