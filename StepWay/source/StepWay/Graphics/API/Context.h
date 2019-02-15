#pragma once


namespace StepWay
{
	namespace graphics
	{
		namespace API
		{


			enum class GraphicsAPIType : int
			{
				NONE = 0,
				OPENGL,
				DIRECTX11
			};

#define SW_DEFAULT_GR_API	::StepWay::graphics::GraphicsAPI::OPENGL


			class Context
			{
			public:
				explicit Context(GraphicsAPIType type);

				//factory method
				static Context* Create(GraphicsAPIType type);

				virtual bool SetUp() = 0;
				virtual void ShutDown() = 0;

				GraphicsAPIType GetType() const;

				virtual ~Context() {};


			private:

				GraphicsAPIType m_type;

			};


			class ContextBinding
			{
			public:
				explicit ContextBinding(GraphicsAPIType type);

				virtual void Present() = 0;
				virtual void MakeCurrent() = 0;

				virtual ~ContextBinding() {};
			private:
				GraphicsAPIType m_type;
			};



		}
	}
}