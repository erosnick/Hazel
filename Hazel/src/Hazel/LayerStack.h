#pragma once

#include "Core.h"
#include "Layer.h"

#include <vector>

namespace Hazel
{
	class HAZEL_API LayerStack
	{
	public:

		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void Poplayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return layers.begin(); }
		std::vector<Layer*>::iterator end() { return layers.end(); }
	private:

		std::vector<Layer*> layers;
		std::vector<Layer*>::iterator layerInsert;
	};
}

