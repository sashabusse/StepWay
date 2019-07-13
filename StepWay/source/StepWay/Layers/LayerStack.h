#pragma once
#include <vector>
#include "Layer.h"

namespace StepWay
{
	

	class LayerStack
	{
	public:
		void PushLayer(Layer* layer);
		Layer* PopLayer();
		void PopLayer(Layer* layer);

		typedef std::vector<Layer*>::iterator		Iterator;
		typedef std::vector<Layer*>::const_iterator ConstIterator;

		Iterator begin();
		ConstIterator begin() const;
		Iterator end();
		ConstIterator end() const;

		int size()const;

	private:
		std::vector<Layer*> m_Layers;
	};


}
