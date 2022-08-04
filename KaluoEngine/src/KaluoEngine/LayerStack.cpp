#include "Kaluopch.h"
#include "LayerStack.h"

namespace KaluoEngine {
	LayerStack::LayerStack() 
	{
		m_LayerInsert = m_Layers.begin();
	}

	LayerStack::~LayerStack()
	{
		for (Layer* EachLayer : m_Layers)
			delete EachLayer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		KALUO_CORE_INFO("pushing layer before the overlay...");
		m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
	}

	void LayerStack::PushOverlay(Layer* OverLay)
	{
		KALUO_CORE_INFO("pushing layer to the end of layer stack"); 
		m_Layers.emplace_back(OverLay);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_LayerInsert--;
		}
		else 
		{
			KALUO_CORE_WARN("poping the end of the layer!");
		}
	}

	void LayerStack::PopOverLay(Layer* overlay)
	{
		//over lap always render it the last
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
		}
	}
}