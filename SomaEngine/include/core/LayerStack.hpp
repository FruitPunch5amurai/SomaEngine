#pragma once

#include "Layer.hpp"
#include "common.hpp"
#include "dataStructures/array.hpp"

namespace SOMA_ENGINE {
	class  LayerStack {
	public:
		LayerStack();
		~LayerStack();


		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		SOMA_Array<Layer*>::iterator begin() { return m_layers.begin(); }
		SOMA_Array<Layer*>::iterator end() { return m_layers.end(); }
	private:
		SOMA_Array<Layer*> m_layers;
		unsigned int m_layerInsertIndex = 0;
	};
}