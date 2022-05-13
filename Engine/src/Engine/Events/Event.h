#pragma once

#include "pch.h"
#include "Engine/Core.h"

namespace Engine {

	// Events are currently blocking, meaning when an event occurs it
	// immediately gets dispatched and must be dealt with right then an there.
	// For the future, a better strategy might be to buffer events in an event
	// bus and process them during the "event" part of the update stage.

	enum class EventType
	{
		None = 0,
		// ApplicationEvent.h
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		// KeyEvent.h
		KeyPressed, KeyReleased,
		// MouseEvent.h
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	// We may want to filter certain events. 
	// E.g we want only mouse events.
	// Also multiple categories can be applied to a single event type
	// (mouse and keyboard events are input events, ...)
	// Event will be seted to multiple categories 
	// 11010 - MouseButton, Mouse, Input 
	// and then it can be masked (by IsInCategory method)
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4)
	};

// static - we don't need an instance of event to know that this event is event))
// see @@@ comment below.
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class ENGINE_API Event
	{
		friend class EventDispatcher;	// EventDispatcher can access to private members of Event
	public:
		virtual EventType GetEventType() const = 0;		// const - we can't modify class members variables.
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }		// to be overwritten where needed	why GetName???

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	protected:
		bool m_Handled = false;
	};

	// ???
	// To dispatch events based on their type.
	// We can receive any type of event. 
	class EventDispatcher
	{
		template<typename T>
		// returns bool, takes in T reference.
		// T - any event type.
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		template<typename T>
		// func is implemented somewhere in engine (usually where event is handled)
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())	// @@@
			{
				// function is called with passed event
				m_Event.m_Handled = func(*(T*)&m_Event);		// ???
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	// for logs
	// ???
	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}
