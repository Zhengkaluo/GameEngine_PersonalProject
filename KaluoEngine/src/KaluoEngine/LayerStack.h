#pragma once
#include "KaluoEngine/Core.h"
#include "Layer.h"

namespace KaluoEngine {
	//we want overlay to be always the end
	//like debug grpahics we would like it to be always on top
	class KALUO_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* OverLay);
		void PopLayer(Layer* layer);
		void PopOverLay(Layer* OverLay);


		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }


	private:
		//wraper over vector of layers Essential of this class
		std::vector<Layer*> m_Layers;
		//for making sure overlay be always the last
		unsigned int m_LayerInsertIndex = 0;
	};

}
