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

#include <fstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

std::string loadShader(const std::string& shaderFile)
{
	std::ifstream file(shaderFile);

	if (file.eof())
	{
		HAZEL_CORE_ERROR("Can not open Error: {0}", shaderFile);
		return "";
	}

	int length;
	file.seekg(0, std::ios::end);
	length = file.tellg();

	file.seekg(0, std::ios::beg);
	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string shader(buffer.str());
	//file.read(&shader[0], length);

	file.close();

	return shader;
}

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)_malloca(sizeof(char) * length);
		glGetShaderInfoLog(id, length, &length, message);

		HAZEL_CORE_ERROR("Failed to compile {0}.", (type == GL_VERTEX_SHADER) ? "vertex shader" : "fragment shader");
		HAZEL_CORE_ERROR("OpenGL Error: {0}", message);

		glDeleteShader(id);

		return 0;
	}

	return id;
}

static int CreateShader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
{
	std::string vertexShader = loadShader(vertexShaderFile);
	std::string fragmentShader = loadShader(fragmentShaderFile);

	if (!(vertexShader.length() > 0 && fragmentShader.size() > 0))
	{
		HAZEL_CORE_ERROR("Wrong shader size");
		return 0;
	}

	GLuint program = glCreateProgram();
	GLuint vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return 1;
}

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
	}

	void Win32Window::OnClear(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Win32Window::OnRender()
	{
		glBindVertexArray(vao[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

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

		HAZEL_CORE_INFO("Creating window {0}, ({1}, {2})", windowProps.title, windowProps.width, windowProps.height);

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

		glfwSetKeyCallback(window, [](GLFWwindow* window, int keyCode, int scancode, int action, int mode)
		{
			auto windowData = (WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
			{
				KeyPressedEvent event(keyCode, 0);
				windowData->eventCallback(event);
				break;
			}

			case GLFW_RELEASE:
			{
				KeyReleasedEvent event(keyCode);
				windowData->eventCallback(event);
				break;
			}

			case GLFW_REPEAT:
			{
				KeyPressedEvent event(keyCode, 1);
				windowData->eventCallback(event);
				break;
			}
			default:
				break;
			}
		});

		glfwSetCharCallback(window, [](GLFWwindow* window, uint32_t keyCode)
		{
			auto windowData = *(WindowData*)glfwGetWindowUserPointer(window);

			KeyTypedEvent event(keyCode);
			windowData.eventCallback(event);
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

		GLfloat vertices1[] = {
			-0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f
		};

		GLfloat vertices2[] = {
			-0.5f,  0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			 0.0f, -0.5f, 0.0f
		};

		glGenVertexArrays(2, vao);
		glBindVertexArray(vao[0]);

		glGenBuffers(2, vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 3, (void*)0);
		glEnableVertexAttribArray(0);


		glBindVertexArray(vao[1]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 3, (void*)0);
		glEnableVertexAttribArray(0);

		unsigned int shader = CreateShader("shaders/vertex.vs", "shaders/fragment.fs");
		glUseProgram(shader);
	}

	void Win32Window::Shutdown()
	{
		glfwDestroyWindow(window);
	}
}