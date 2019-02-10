#pragma once
#include <vector>
#include "Layer.h"

namespace StepWay
{
	namespace graphics
	{

		class SW_API LayerStack
		{
		public:
			void PushLayer(Layer* layer);
			void PopLayer(Layer* layer);

			typedef std::vector<Layer*>::iterator		Iterator;
			typedef std::vector<Layer*>::const_iterator ConstIterator;

			Iterator begin();
			ConstIterator begin() const;
			Iterator end();
			ConstIterator end() const;

		private:
			std::vector<Layer*> m_Layers;
		};

	}
}
