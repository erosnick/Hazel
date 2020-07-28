/*
* This is an independent project of an individual developer. Dear PVS-Studio, please check it.
* PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
*/
#include "HazelPCH.h"
#include "Application.h"
#include "Log.h"

namespace Hazel
{
#define BIND_EVENT_FUNCTION(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
		window = std::unique_ptr<Window>(Window::Create());

		window->SetEventCallback(BIND_EVENT_FUNCTION(OnEvent));
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (running)
		{
			window->OnUpdate();

			for (auto layer : layerStack)
			{
				layer->OnUpdate();
			}
		}
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);

		switch (event.GetEventType())
		{
		case EventType::WindowClose:
			dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNCTION(OnWindowClose));
			break;

		case EventType::KeyPressed:
			dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FUNCTION(OnMouseKeyPressed));
			break;

		case EventType::WindowLostFocus:

		default:
			break;
		}

		HAZEL_CORE_TRACE("{0}", event.ToString());

		for (auto iterator = layerStack.end(); iterator != layerStack.begin();)
		{
			(*--iterator)->OnEvent(event);
			if (event.handled)
			{
				break;
			}
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		layerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		layerStack.PushOverlay(layer);
	}

	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		running = false;

		return true;
	}

	bool Application::OnMouseKeyPressed(KeyPressedEvent& event)
	{
		return true;
	}
}