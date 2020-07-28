/*
* This is an independent project of an individual developer. Dear PVS-Studio, please check it.
* PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
*/
#include "HazelPCH.h"
#include "Win32Window.h"
#include "Hazel/Log.h"
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Events/ApplicationEvent.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Hazel
{
	static bool g_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		HAZEL_CORE_ERROR("GLFW Error: {0} : {1}", error, description);
	}

	Window* Window::Create(const WindowProps& windowProps)
	{
		return new Win32Window(windowProps);
	}

	Win32Window::Win32Window(const WindowProps& windowProps)
	{
		Init(windowProps);
	}

	Win32Window::~Win32Window()
	{
		Shutdown();
	}

	void Win32Window::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	void Win32Window::SetVSync(bool enable)
	{
		if (enable)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}

		data.vsync = enable;
	}

	bool Win32Window::IsVSync() const
	{
		return data.vsync;
	}

	void Win32Window::Init(const WindowProps& windowProps)
	{
		data.title = windowProps.title;
		data.width = windowProps.width;
		data.height = windowProps.height;

		HAZEL_CORE_INFO("Creating window {0}, ({1}, {2}", windowProps.title, windowProps.width, windowProps.height);

		if (!g_GLFWInitialized)
		{
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			HAZEL_CORE_ASSERT(success, "Could not initialize GLFW!");

			g_GLFWInitialized = true;
		}

		window = glfwCreateWindow((int)windowProps.width, (int)data.height, data.title.c_str(), nullptr, nullptr);

		glfwSetErrorCallback(GLFWErrorCallback);

		glfwMakeContextCurrent(window);
		glfwSetWindowUserPointer(window, &data);
		SetVSync(true);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		HAZEL_ASSERT(status, "Failed to initialize Glad!");

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
		{
			auto windowData = (WindowData*)glfwGetWindowUserPointer(window);

			windowData->width = width;
			windowData->height = height;

			WindowResizeEvent reszeEvent(width, height);

			windowData->eventCallback(reszeEvent);
		});

		glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
		{
			auto windowData = (WindowData*)glfwGetWindowUserPointer(window);

			WindowCloseEvent closeEvent;

			windowData->eventCallback(closeEvent);
		});

		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mode)
		{
			auto windowData = (WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
			{
				KeyPressedEvent event(key, 0);
				windowData->eventCallback(event);
				break;
			}

			case GLFW_RELEASE:
			{
				KeyReleasedEvent event(key);
				windowData->eventCallback(event);
				break;
			}

			case GLFW_REPEAT:
			{
				KeyPressedEvent event(key, 1);
				windowData->eventCallback(event);
				break;
			}
			default:
				break;
			}
		});
	
		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
		{
			auto windowData = (WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent event(button);
				windowData->eventCallback(event);
				break;
			}

			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent event(button);
				windowData->eventCallback(event);
				break;
			}

			default:
				break;
			}
		});

		glfwSetScrollCallback(window, [](GLFWwindow* window, double offsetX, double offsetY)
		{
			auto windowData = (WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)offsetX, (float)offsetY);
			windowData->eventCallback(event);
		});

		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double positionX, double positionY)
		{
			auto windowData = (WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)positionX, (float)positionY);
			windowData->eventCallback(event);
		});
	}

	void Win32Window::Shutdown()
	{
		glfwDestroyWindow(window);
	}
}