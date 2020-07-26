#pragma once

#include "Event.h"

#include <sstream>

namespace Hazel
{
	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(uint32_t width, uint32_t height)
			: width(width), height(height)
		{}

		inline uint32_t GetWidth() const { return width; }
		inline uint32_t GetHeight() const { return height; }

		std::string ToString() const override
		{
			std::stringstream stringStream;
			stringStream << "WindowResizeEvent: " << width << ", " << height;
			return stringStream.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:
		uint32_t width;
		uint32_t height;
	};

	class HAZEL_API WindowCloseEvent : public Event
	{
	public:

		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class HAZEL_API ApplicationTickEvent : public Event
	{
	public:

		ApplicationTickEvent() {}

		EVENT_CLASS_TYPE(ApplicationTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class HAZEL_API ApplicationUpdateEvent : public Event
	{
	public:

		ApplicationUpdateEvent() {}

		EVENT_CLASS_TYPE(ApplicationUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class HAZEL_API ApplicationRenderEvent : public Event
	{
	public:

		ApplicationRenderEvent() {}

		EVENT_CLASS_TYPE(ApplicationRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}