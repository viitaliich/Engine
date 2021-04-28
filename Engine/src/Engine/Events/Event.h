#pragma once

//#include "Engine/Core.h"
#include "../Core.h"		// ???

// These 2 files should be in precompiled header 
// (because this is a standard library) and/or in included in Core
#include <string>
#include <functional>		// ???

namespace Engine {

	// blocking events - ???
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

	// to "filter" events
	// BIT - how it works ??? 
	// Apply multiple categories to a single event type. 
	// MouseButton event is also Mouse event. Keyboard is also Input event.
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4)
	};

// ???
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }
// ???
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class ENGINE_API Event
	{
		friend class EventDispatcher;		// ???
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;		// ???		should be available only for DEBUG mode
		virtual int GetCategoryFlags() const = 0;		// how it works ???
		virtual std::string ToString() const { return GetName(); }		// should be available only for DEBUG mode

		// Utility function (helper function) supports the operation of the class's public member functions
		// where is it used ???
		inline bool IsInCategory(EventCategory category)
		{
			// "category" is a number, category which we want; & - bitwise AND 
			return GetCategoryFlags() & category;		// 0 - not in any category, not 0 - in one category at least
		}
	protected:
		bool m_Handled = false;		// when we clicked a mouse on a button, for example
	};

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
