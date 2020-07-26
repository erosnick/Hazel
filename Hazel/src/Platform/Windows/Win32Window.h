#pragma once

#include "Hazel/Window.h"

struct GLFWwindow;

namespace Hazel
{
	class Win32Window : public Window
	{
	public:

		Win32Window(const WindowProps& windowProps);
		virtual ~Win32Window();

		void OnUpdate() override;

		inline uint32_t GetWidth() const override { return data.width; }
		inline uint32_t GetHeight() const override { return data.height; }

		// Window attributes
		inline void SetEventCallback(const EventCallback& eventCallback) override { data.eventCallback = eventCallback; }
		void SetVSync(bool enable) override;
		bool IsVSync() const override;

	private:
		virtual void Init(const WindowProps& windowProps);
		virtual void Shutdown();

	private:

		GLFWwindow* window;

		struct WindowData
		{
			std::string title;
			uint32_t width;
			uint32_t height;
			bool vsync;

			EventCallback eventCallback;
		};

		WindowData data;
	};
}

