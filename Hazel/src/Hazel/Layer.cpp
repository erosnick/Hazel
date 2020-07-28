/*
* This is an independent project of an individual developer. Dear PVS-Studio, please check it.
* PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
*/
#include "HazelPCH.h"
#include "Layer.h"

namespace Hazel
{
	Hazel::Layer::Layer(const std::string& name)
		: debugName(name)
	{
	}
	
	Hazel::Layer::~Layer()
	{
	}
}
