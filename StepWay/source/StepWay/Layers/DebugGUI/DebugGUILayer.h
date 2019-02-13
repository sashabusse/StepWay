#pragma once
#include "Layers/Layer.h"
#include "Core.h"

namespace StepWay
{
	namespace graphics
	{


		class SW_API  DebugGUILayer : public Layer
		{
		public:
			~DebugGUILayer() override;

			void OnAttach() override;
			void OnDetach() override;
			void OnUpdate() override;
			void OnEvent(Event& e) override;

			std::string ToString() const override;
			std::wstring ToWString() const override;


		private:


		};




	}
}