#pragma once
#include "xenospch.h"
#include "Xenos/Core/Core.h"


namespace Xenos
{
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	/*
	Used for filtering events. For example, if we want to check for any mouse event,
	we don't have to go through all the mouse-related EventTypes. We can just check if 
	caegory is mouse.
	BIT(): This is a bitfield and is used to allow an event to be a member of multiple
	categories. For example, BIT(0) will be 00001, BIT(1) will be 00010, BIT(4) will be 10000.
	So an event like RIGHT_MOUSE_BUTTON will be in three categories: EventCategoryInput,
	EventCategoryMouse and EventCategoryMouseButton. Its bitfield will be 110010. We can now use
	bitasking to check the categories it belongs to.
	*/

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

	//Macro for implementing the following functions in derived classes
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
							   virtual EventType GetEventType() const override { return GetStaticType(); }\
							   virtual const char* GetName() const override { return #type; }

	//Macro for implementing the GetCategoryFlags() function in derived classes
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category;}

	//Current event system is blocking, i.e. it is dipatched as soon as it is recieved.
	//TODO: Buffered event system

	class XENOS_API Event
	{
		friend class EventDispatcher;

	public:
		//Helps us conrol how deep down the even will be propagated.
		//If set to true, the layer underneath will not get notified of the event.
		bool Handled = false;
		//Equalling a virtual function to 0 makes it a pure vitual function.
		//A pure virtual function MUST be implmented
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;	//Is only intended to be used for debugging
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }	//Get a string with the name of the event

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	};
	/*
	Allows us to dispatch events based on their type. In our OnEvent function, we will recieve
	events as Event pointers. We do not know the category the Event belongs to. 	
	*/
	class EventDispatcher
	{

	public:
		EventDispatcher(Event& event)
			:m_Event(event){}

		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled = func(static_cast<T&>(m_Event));
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
