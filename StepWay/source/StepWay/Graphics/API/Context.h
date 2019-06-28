#pragma once
#include "Core.h"
#include <string>
#include "Window.h"



namespace StepWay
{	namespace Graphics
	{	namespace API
		{

	enum class SW_API GAPI_TYPE : int
	{
		NONE = 0,
		OPENGL,
		D3D11
	};

#define SW_DECLARE_GAPI_TYPE(type)\
	static Graphics::API::GAPI_TYPE GetStaticGAPI_TYPE(){return type;}\
	virtual Graphics::API::GAPI_TYPE GetGAPI_TYPE()const override {return GetStaticGAPI_TYPE();}\
	virtual std::string GetGAPIString()const override {return #type;}\
	virtual std::wstring GetGAPIWString()const override {return L#type;}


	class SW_API GraphicsContext
	{
	public:
		static GraphicsContext* Create(GAPI_TYPE type, Window* window);
		static GraphicsContext* CreateGLContext(Window* window);
		//add other APIS later
		static void Destroy(GraphicsContext* context);
		static bool IsAPISupportedByOS(GAPI_TYPE type);

		virtual ~GraphicsContext() {};

		//define in children
		virtual void SetUp() = 0;
		virtual void ShutDown() = 0;
		virtual void SwapBuffers() = 0;
		virtual void MakeCurrent() = 0;

		//declare in child by macros SW_DECLARE_GAPI_TYPE
		virtual GAPI_TYPE GetGAPI_TYPE()const = 0;
		virtual std::string GetGAPIString()const = 0;
		virtual std::wstring GetGAPIWString()const = 0;
	protected:
		GraphicsContext() {};
	private:
	};


}}}
