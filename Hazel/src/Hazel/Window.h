#pragma once

#include "HazelPCH.h"

#include "Hazel/Core.h"
#include "Events/Event.h"

namespace Hazel
{
	struct WindowProps
	{
		WindowProps(const std::string& title = "Hazel Engine", uint32_t width = 1280, uint32_t height = 720)
			: title(title), width(width), height(height)
		{}

		std::string title;
		uint32_t width;
		uint32_t height;
	};

	// Interface representing a desktop system based window
	class HAZEL_API Window
	{
	public:
		using EventCallback = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;
		virtual void OnClear(float r, float g, float b, float) = 0;
		virtual void OnRender() = 0;
		
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallback& eventCallback) = 0;
		virtual void SetVSync(bool enable) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProps& windowProps = WindowProps());

	private:

	};
}