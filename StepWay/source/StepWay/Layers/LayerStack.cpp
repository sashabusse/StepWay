#include "StepWayPCH.h"
#include "LayerStack.h"


namespace StepWay
{
	void LayerStack::ShutDown()
	{
		for (auto& layer : m_Layers)
		{
			layer->OnDetach();
		}
		m_Layers.clear();
	}

	void LayerStack::PushLayer(std::shared_ptr <Layer> layer)
	{
		SW_CORE_ASSERT(layer != nullptr, "invalid pointer");
		m_Layers.push_back(layer);
		layer->OnAttach();
		SW_CORE_TRACE("Layer Pushed: " + layer->ToString());
	}


	std::shared_ptr<Layer> LayerStack::PopLayer()
	{
		SW_CORE_ASSERT(size() != 0, "cant pop layer when stack is empty");
		std::shared_ptr<Layer> ret = m_Layers.back();
		m_Layers.pop_back();
		return ret;
	}

	void LayerStack::PopLayer(std::shared_ptr<Layer> layer)
	{
		SW_CORE_ASSERT(layer != nullptr, "invalid pointer");
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			layer->OnDetach();
			SW_CORE_INFO("Layer Poped: " + layer->ToString());
		}
		else
		{
			SW_CORE_WARNING("trying to Pop layer that doesnt belong to this layerStack: " + layer->ToString());
		}
	}


	LayerStack::Iterator LayerStack::begin()
	{
		return m_Layers.begin();
	}


	LayerStack::ConstIterator LayerStack::begin() const
	{
		return m_Layers.begin();
	}


	LayerStack::Iterator LayerStack::end()
	{
		return m_Layers.end();
	}


	LayerStack::ConstIterator LayerStack::end() const
	{
		return m_Layers.end();
	}
	int LayerStack::size() const
	{
		return m_Layers.size();
	}
}
