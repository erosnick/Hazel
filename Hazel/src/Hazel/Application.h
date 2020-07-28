#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "LayerStack.h"

namespace Hazel
{
	// C4251 workaround
	template class HAZEL_API std::unique_ptr<Window>;
	template struct HAZEL_API std::default_delete<Window>;
	template class HAZEL_API std::_Compressed_pair<std::default_delete<Window>, Hazel::Window*, true>;

	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

	private:

		bool OnWindowClose(WindowCloseEvent& event);

		bool OnMouseKeyPressed(KeyPressedEvent& event);
	
	private:
		std::unique_ptr<Window> window;
		bool running = true;
		LayerStack layerStack;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}