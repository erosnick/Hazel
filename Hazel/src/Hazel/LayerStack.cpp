/*
* This is an independent project of an individual developer. Dear PVS-Studio, please check it.
* PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
*/
#include "HazelPCH.h"
#include "LayerStack.h"
#include "Log.h"

namespace Hazel
{
	LayerStack::LayerStack()
	{
		layerInsert = layers.begin();
	}
	
	LayerStack::~LayerStack()
	{
		for (auto layer : layers)
		{
			delete layer;
		}
	}
	
	void LayerStack::PushLayer(Layer* layer)
	{
		layerInsert = layers.emplace(layerInsert, layer);
		layer->OnAttach();
	}
	
	void LayerStack::PushOverlay(Layer* overlay)
	{
		layers.emplace_back(overlay);
		overlay->OnAttach();
	}
	
	void Hazel::LayerStack::Poplayer(Layer* layer)
	{
		auto iterator = std::find(layers.begin(), layers.end(), layer);
	
		if (iterator != layers.end())
		{
			layers.erase(iterator);
			layerInsert--;
		}
	}
	
	void Hazel::LayerStack::PopOverlay(Layer* overlay)
	{
		auto iterator = std::find(layers.begin(), layers.end(), overlay);
	
		if (iterator != layers.end())
		{
			layers.erase(iterator);
		}
	}
}
