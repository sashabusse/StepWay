#pragma once
#include <string>
#include <vector>


namespace StepWay
{

	//
	enum class BundleType : int
	{
		DEBUG = -1,
		INVALID = 0,
		FILESYSTEM_FOLDER,
		ZIP_ARCHIVE
	};


#define SW_DECLARE_BANK_TYPE(type)\
	static BundleType GetStaticBankType(){return type;}\
	virtual BundleType GetBankType() const override {return GetStaticBankType();}\
	virtual std::string GetBankTypeString() const override {return #type;}



	//extensive use of std::string remove later
	//Interface for resource sets like fileSystemFolders and Zip archieves
	class IResourceBundle
	{
	public:
		//factory method
		static IResourceBundle* CreateResourceBank(const std::string& path, BundleType type);

		//Use macro to ovrride this two
		virtual BundleType GetBankType() const = 0;
		virtual std::string GetBankTypeString() const = 0;

		virtual std::vector<std::string> GetFileNames()const = 0;

		virtual ~IResourceBundle() {};
	protected :
		IResourceBundle() {};
	};



	class DebugResourceBundle : public IResourceBundle
	{
	public:
		SW_DECLARE_BANK_TYPE(BundleType::DEBUG);

		DebugResourceBundle(const std::string& path):m_path(path) {};
		virtual std::vector<std::string> GetFileNames()const override
		{
			return { std::string("debugBankFile1.example"),std::string("debugBankFile2.example") };
		}
	private:
		std::string m_path;
	};


}