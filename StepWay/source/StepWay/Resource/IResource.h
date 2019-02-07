#pragma once
#include <string>




namespace StepWay
{

	//types of Resouces should be return in GetResourceType 
	enum class ResourceType : int
	{
		INVALID = 0,
		TEXT_FILE,
		IMAGE, TEXTURE
	};


	//this should be super class for all resource types (e.g. Texture Image Mesh)
	//Responsibilities:
	//	1. provides data structure for other system/


#define SW_DECLARE_RESOURCE_TYPE(type)\
	static ResourceType GetStaticResourceType(){return type;}\
	virtual ResourceType GetResourceType() const override { return GetStaticResourceType(); }\
	virtual std::string GetResourceTypeString() const override {return #type;}



	class IResource
	{
	public:
		IResource() {};
		virtual~IResource() {};

		virtual ResourceType GetResourceType() const = 0;
		virtual std::string GetResourceTypeString() const = 0;

	};


}
