#include "StepWayPCH.h"
#include "LayerStack.h"

using StepWay::graphics::LayerStack;


void StepWay::graphics::LayerStack::PushLayer(Layer* layer)
{
	SW_CORE_ASSERT(layer != nullptr, "invalid pointer");
	m_Layers.push_back(layer);
	layer->OnAttach();
	SW_CORE_TRACE("Layer Pushed: " + layer->ToString());
}


void StepWay::graphics::LayerStack::PopLayer(Layer* layer)
{
	SW_CORE_ASSERT(layer != nullptr,"invalid pointer");
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

