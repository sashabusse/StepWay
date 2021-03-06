#pragma once
#include "Core.h"
#include <string>
#include "Window.h"
#include "Events/WindowEvent.h"



namespace StepWay
{	
	namespace Graphics
	{	
		namespace API
		{

			enum class GAPI_TYPE : int
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


			class GraphicsContext
			{
			public:
				static GraphicsContext* Create(GAPI_TYPE type, Window* window);
				static GraphicsContext* CreateGLContext(Window* window);
				//add other APIS later
				static void Destroy(GraphicsContext* context);
				static bool IsAPISupportedByOS(GAPI_TYPE type);

				virtual ~GraphicsContext() {};
				
				void OnWindowResize(WindowResizeEvent& e) { ResizeViewport(0, 0, e.GetWidth(), e.GetHeight()); };
				virtual void ResizeViewport(int x, int y, int width, int height) = 0;

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


		}
	}
}
