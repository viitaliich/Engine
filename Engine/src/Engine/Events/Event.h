//TODO: check diffs of all files on git 

#pragma once

#include "Engine/Core.h"

// These 2 files should be in precompiled header 
// (because this is a standard library) and/or included in Core
#include <string>
#include <functional>		// ???

namespace Engine {

	// Events in Engine are currently blocking, meaning when an event occurs it
	// immediately gets dispatched and must be dealt with right then an there.
	// For the future, a better strategy might be to buffer events in an event
	// bus and process them during the "event" part of the update stage.

	enum class EventType
	{
		None = 0,
		// ApplicationEvents.h
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,		
		// KeyEvents.h
		KeyPressed, KeyReleased,
		// MouseEvents.h
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	// ???	
	// to "filter" certain events
	// BIT - how it works ??? 
	// Apply multiple categories to a single event type. 
	// MouseButton event is also Mouse event. Keyboard is also Input event.
	// why BIT macro is in Core.h, not here?
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4)
	};

// why event_CLASS_type? event_type is enough.	???
// use case of static method? ???
// why static method isn't const as the next one?
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }
// ???
// why event_CLASS_category? event_category is enough.	???
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class ENGINE_API Event
	{
		friend class EventDispatcher;		// ???	can access to private and protected fields of Event class
	public:
		virtual EventType GetEventType() const = 0;
		virtual int GetCategoryFlags() const = 0;		// how it works ???
		virtual const char* GetName() const = 0;		// ???		should be available only for DEBUG mode
		virtual std::string ToString() const { return GetName(); }		// should be available only for DEBUG mode

		// ???
		inline bool IsInCategory(EventCategory category)
		{
			// & - bitwise AND
			// GetCategoryFlags ???
			return GetCategoryFlags() & category;		// 0 - not in any category, not 0 - in one category at least
		}
	protected:
		bool m_Handled = false;		// is event handled or not. when a mouse on a button is clicked for example
	};

	// ???
	// https://www.youtube.com/watch?v=xnopUoZbMEk&list=LL&index=6&t=819s&ab_channel=TheCherno
	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}
