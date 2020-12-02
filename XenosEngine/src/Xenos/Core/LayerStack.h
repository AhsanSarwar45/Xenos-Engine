#pragma once

#include "Core.h"
#include "Layer.h"

#include <vector>

namespace Xenos
{
	class XENOS_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	private:
		//Stores all the layers and overlays
		std::vector<Layer*> m_Layers;
		/*
		Acts as the barrier between layers and overlays. Layers are atored in the first half
		before the insert), while overlays are stored after the insert.
		New layers are added at the current insert position while overlays are added at the end 
		of the list.
		*/
		unsigned int m_LayerInsertIndex = 0;
	};
}