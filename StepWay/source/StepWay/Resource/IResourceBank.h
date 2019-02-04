#pragma once
#include <string>
#include <vector>


namespace StepWay
{

	//
	enum class BankType : int
	{
		DEBUG = -1,
		INVALID = 0,
		FILESYSTEM_FOLDER,
		ZIP_ARCHIVE
	};


#define SW_DECLARE_BANK_TYPE(type)\
	static BankType GetStaticBankType(){return type;}\
	virtual BankType GetBankType() const override {return GetStaticBankType();}\
	virtual std::string GetBankTypeString() const override {return #type;}



	//extensive use of std::string remove later
	//Interface for resource sets like fileSystemFolders and Zip archieves
	class IResourceBank
	{
	public:
		//factory method
		static IResourceBank* CreateResourceBank(const std::string& path, BankType type);

		//Use macro to ovrride this two
		virtual BankType GetBankType() const = 0;
		virtual std::string GetBankTypeString() const = 0;

		virtual std::vector<std::string> GetFileNames()const = 0;

		virtual ~IResourceBank() {};
	protected :
		IResourceBank() {};
	};



	class DebugResourceBank : public IResourceBank
	{
	public:
		SW_DECLARE_BANK_TYPE(BankType::DEBUG);

		DebugResourceBank(const std::string& path):m_path(path) {};
		virtual std::vector<std::string> GetFileNames()const override
		{
			return { std::string("debugBankFile1.example"),std::string("debugBankFile2.example") };
		}
	private:
		std::string m_path;
	};


}