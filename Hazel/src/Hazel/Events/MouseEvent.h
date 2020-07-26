#pragma once

#include "Event.h"

namespace Hazel
{
	class HAZEL_API MouseMovedEvent : public Event
	{
	public:

		MouseMovedEvent(float x, float y)
			: mouseX(x), mouseY(y)
		{}

		inline float GetX() const { return mouseX; }
		inline float GetY() const { return mouseY; }

		std::string ToString() const override
		{
			std::stringstream stringStream;
			stringStream << "MouseMoveEvent: " << mouseX << ", " << mouseY;
			return stringStream.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:

		float mouseX;
		float mouseY;
	};

	class HAZEL_API MouseScrolledEvent : public Event
	{
	public:

		MouseScrolledEvent(float x, float y)
			: offsetX(x), offSetY(y)
		{}

		inline float GetOffsetX() const { return offsetX; }
		inline float GetOffsetY() const { return offSetY; }

		std::string ToString() const override
		{
			std::stringstream stringStream;
			stringStream << "MouseScrolledEvent: " << offsetX << ", " << offSetY;
			return stringStream.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:

		float offsetX;
		float offSetY;
	};

	class HAZEL_API MouseButtonEvent : public Event
	{
	public:

		inline int GetMouseButton() const { return button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	protected:

		MouseButtonEvent(int button)
			: button(button)
		{}

		int button;
	};

	class HAZEL_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:

		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button)
		{}

		std::string ToString() const override
		{
			std::stringstream stringStream;
			stringStream << "MouseButtonPressedEvent: " << button;
			return stringStream.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class HAZEL_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:

		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button)
		{}

		std::string ToString() const override
		{
			std::stringstream stringStream;
			stringStream << "MouseButtonReleasedEvent: " << button;
			return stringStream.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}