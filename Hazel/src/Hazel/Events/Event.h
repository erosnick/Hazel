#pragma once

#include "Hazel/Core.h"

namespace Hazel
{
	// Events in Hazel are currently blocking, meaning when an event occurs it
	// immediately gets dispatched and must be dealt with right then and there.
	// For the future, a better strategy might be to buffer events in an events
	// bus and process them during the "event" part of the update stage.

	enum class EventType
	{
		None = 0,
		WindowClose,
		WindowResize,
		WindowForcus,
		WindowLostFocus,
		WindowMoved,
		ApplicationTick,
		ApplicationUpdate,
		ApplicationRender,
		KeyPressed,
		KeyReleased,
		KeyTyped,
		MouseButtonPressed,
		MouseButtonReleased,
		MouseMoved,
		MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput		 = BIT(1),
		EventCategoryKeyBoard	 = BIT(2),
		EventCategoryMouse		 = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class HAZEL_API Event
	{
		friend class EventDispatcher;

	public:

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}

	public:

		bool handled = false;
	};

	class HAZEL_API EventDispatcher
	{
		template<typename T>
		using EventFunction = std::function<bool(T&)>;

	public:
		EventDispatcher(Event& event)
			: event(event)
		{}

		template<typename T>
		bool Dispatch(EventFunction<T> function)
		{
			if (event.GetEventType() == T::GetStaticType())
			{
				event.handled = function(*dynamic_cast<T*>(&event));
				
				return true;
			}

			return false;
		}

	private:
		Event& event;
	};

	inline std::ostream& operator<<(std::ostream& stream, const Event& event)
	{
		return stream << event.ToString();
	}
}