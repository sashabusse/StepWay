#pragma once
#include "Core.h"


namespace StepWay
{	namespace graphics
	{	namespace API
		{

			
			enum class SW_API GraphicsAPIType : int
			{
				NONE = 0,
				OPENGL,
				DIRECTX11
			};

			//let premake do it
#define SW_DEFAULT_GR_API	::StepWay::graphics::GraphicsAPI::OPENGL



			//overrides type functions(only 1 for now
#define SW_DECLARE_CONTEXT_TYPE(type)\
	::StepWay::graphics::API::GraphicsAPIType GetType() const final\
	{ return type; }


			//Interface for Rendering Context
			//Realization Incapsulates Context needed to rendering
			//For example on realization check Platform/Win32/OpenGL/GLContext.h/cpp
			class SW_API Context
			{
			public:
				explicit Context();

				//factory method
				static Context* Create(GraphicsAPIType type);//add default

				virtual bool SetUp() = 0;
				virtual void ShutDown() = 0;

				virtual GraphicsAPIType GetType() const = 0;

				virtual ~Context() {};
			private:

			};



			//overrides type functions(only 1 for now
#define SW_DECLARE_CONTEXT_BINDING_TYPE(type)\
	::StepWay::graphics::API::GraphicsAPIType GetType() const final\
	{ return type; }


			//Interface for binding to context
			//Incapsulates information to share context among diffrent windows(Render Targets later)
			class ContextBinding
			{
			public:
				explicit ContextBinding();

				virtual void Present() = 0;
				virtual void MakeCurrent() = 0;

				virtual GraphicsAPIType GetType() const = 0;

				virtual ~ContextBinding() {};
			private:
			};



		}
	}
}