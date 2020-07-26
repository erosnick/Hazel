/*
* This is an independent project of an individual developer. Dear PVS-Studio, please check it.
* PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
*/
#include "HazelPCH.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace Hazel
{
	Application::Application()
	{
		window = std::unique_ptr<Window>(Window::Create());

		window->SetEventCallback([](Event& event) {

		});
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (running)
		{
			window->OnUpdate();
		}
	}
}