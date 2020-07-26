#pragma once

#include "Event.h"

namespace Hazel
{
	class HAZEL_API KeyEvent : public Event
	{
	public:

		inline int GetKeyCode() const { return keyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyBoard | EventCategoryInput)

	protected:

		KeyEvent(int keyCode)
			: keyCode(keyCode)
		{}

	protected:
		int keyCode;
	};

	class HAZEL_API KeyPressedEvent : public KeyEvent
	{
	public:

		KeyPressedEvent(int keyCode, int repeatCount)
			: KeyEvent(keyCode), repeatCount(repeatCount)
		{}

		inline int GetRepeatCount() const { return repeatCount; }

		std::string ToString() const override
		{
			std::stringstream stringStream;
			stringStream << "KeyPressedEvent: " << keyCode << " (" << repeatCount << " repeats)";
		}

		EVENT_CLASS_TYPE(KeyPressed)

	private:

		int repeatCount;
	};

	class HAZEL_API KeyReleasedEvent : public KeyEvent
	{
	public:

		KeyReleasedEvent(int keyCode, int repeatCount)
			: KeyEvent(keyCode)
		{}

		std::string ToString() const override
		{
			std::stringstream stringStream;
			stringStream << "KeyReleasedEvent: " << keyCode;
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}