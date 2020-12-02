#pragma once

#include "Events.h"
#include "Xenos/Input/KeyCodes.h"
#include "xenospch.h"

namespace Xenos
{
	//Contains the common key code functionality shared by all key events.
	//It is an abstract class, meaning you cannot construct it.
	class KeyEvent : public Event
	{
	public:
		inline KeyCode GetKeyCode() const { return m_KeyCode; }

		//"|" is the bitwise or operator. It is used to combine multiple flags.
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		//This protected constructor makes sure that this class cannot be created without a child
		KeyEvent(KeyCode keyCode)
			:m_KeyCode(keyCode){}

		KeyCode m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(const KeyCode keyCode, int repeatCount)
			:KeyEvent(keyCode), m_RepeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		//Overriding the ToString event to print it in the form: 
		//KeyPressedEvent: keyCode (x repeats)
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();

		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;
	};


	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(const KeyCode keyCode)
			:KeyEvent(keyCode) {}

		//Overriding the ToString event to print it in the form: 
		//KeyPressedEvent: keyCode (x repeats)
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode ;
			return ss.str();

		}

		EVENT_CLASS_TYPE(KeyTyped)
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public: 
		KeyReleasedEvent(const KeyCode keyCode)
			:KeyEvent(keyCode)	{}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent" << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}
