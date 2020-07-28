/*
* This is an independent project of an individual developer. Dear PVS-Studio, please check it.
* PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
*/
#include "HazelPCH.h"
#include "Application.h"
#include "Log.h"

namespace Hazel
{
	Application* Application::instance;

	Application::Application()
	{
		if (instance == nullptr)
		{
			instance = this;

			window = std::unique_ptr<Window>(Window::Create());

			window->SetEventCallback(HAZEL_BIND_EVENT_FUNCTION(Application::OnEvent));
		}
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (running)
		{
			window->OnUpdate();
			window->OnClear(0.4f, 0.6f, 0.9f, 1.0f);

			for (auto layer : layerStack)
			{
				layer->OnUpdate();
			}

			window->OnRender();
		}
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);

		switch (event.GetEventType())
		{
		case EventType::WindowClose:
			dispatcher.Dispatch<WindowCloseEvent>(HAZEL_BIND_EVENT_FUNCTION(Application::OnWindowClose));
			break;

		case EventType::KeyPressed:
			dispatcher.Dispatch<KeyPressedEvent>(HAZEL_BIND_EVENT_FUNCTION(Application::OnMouseKeyPressed));
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