#pragma once

#include <string>
#include "Event.h"

class KeyEvent: public Event
{
public:
	int getKeyCode() const { return key_code; }
	void changeKeyCode(int);
	EVENT_CLASS_CATEGORY((int)EventCategory::EVENT_CATEGORY_KEYBOARD | (int)EventCategory::EVENT_CATEGORY_INPUT)

protected:
	KeyEvent(int _key_code) : key_code(_key_code) {}
	~KeyEvent() = default;

	int key_code;
};

class KeyPressedEvent : public KeyEvent
{
public:
	////////////////////////////////////////////////////////////
	/// \param _key_code Code of the key which will trigger the event. 
	///	\param _repeat_count  0 if not a repeatable event. 
	////////////////////////////////////////////////////////////
	KeyPressedEvent(int _key_code, int _repeat_count) : KeyEvent(_key_code), repeat_count(_repeat_count) {}
	inline int getRepeatCount() const { return repeat_count; }

	std::string toString() const override
	{
		std::string string;
		string = "KeyPressedEvent: " + std::to_string(key_code) + " : " + std::to_string(repeat_count) + " repeats";
		return string;
	}

	EVENT_CLASS_TYPE(KeyPressed)

private:
	int repeat_count;
};

class KeyReleasedEvent : public KeyEvent
{
public:

	KeyReleasedEvent(int _key_code) : KeyEvent(_key_code) {}

	std::string toString() const override
	{
		std::string string;
		string = "KeyReleasedEvent: " + std::to_string(key_code);
		return string;
	}

	EVENT_CLASS_TYPE(KeyReleased)
};
