#pragma once
#include "Kaluopch.h"
#include "KaluoEngine/Core/Core.h"


namespace KaluoEngine {
	//event in the engine will be immediately gets dispatched and must/will be dealt with right place/function?
	//future might be changed into buffer of events and process them during the update stage

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WIndowFocus, WindowFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyTyped ,KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	//filter certain events, for getting events by category easily
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class KALUO_API Event
	{
		//friend class EventDispatcher;
	public:
		bool Handled = false;


		//have to be implemented
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category) 
		{
			return GetCategoryFlags() & category;
		}
	/*protected:
		bool m_Handled = false;*/

	};

	class KALUO_API EventDispatcher
	{
		template<typename T>
		//T could be any event type
		using EventFn = std::function<bool(T&)>;
	public:
		//Event Reference, create instance of class 
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			//if the event that going to be dispatched matches the type of the function then run the function
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	//for formattable log message and debug used
	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		
		return os << e.ToString();
	}
}