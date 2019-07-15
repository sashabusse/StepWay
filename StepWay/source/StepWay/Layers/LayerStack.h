#pragma once
#include <vector>
#include "Layer.h"
#include <memory.h>

namespace StepWay
{
	

	class LayerStack
	{
	public:
		void SetUp() {};
		void ShutDown();

		void PushLayer(std::shared_ptr<Layer> layer);
		std::shared_ptr <Layer> PopLayer();
		void PopLayer(std::shared_ptr<Layer> layer);

		typedef std::vector< std::shared_ptr<Layer>>::iterator			Iterator;
		typedef std::vector< std::shared_ptr<Layer>>::const_iterator	ConstIterator;

		Iterator begin();
		ConstIterator begin() const;
		Iterator end();
		ConstIterator end() const;

		int size()const;

	private:
		std::vector< std::shared_ptr<Layer>> m_Layers;
	};


}
