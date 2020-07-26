/*
* This is an independent project of an individual developer. Dear PVS-Studio, please check it.
* PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
*/
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace Hazel
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent windowResizeEvent(1280, 720);

		HAZEL_TRACE(windowResizeEvent);
	}
}