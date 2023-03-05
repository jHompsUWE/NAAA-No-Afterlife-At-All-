#pragma once

#include "EventDispatcher.h"
#include "EventTypeEnum.h"
#include <functional>

// https://www.youtube.com/watch?v=xnopUoZbMEk&list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT&index=9

#define BIT(x) (1 << x)
// ^^^^ Creates a macro that shifts 1 to the left x places.

// For filtering events.
// Uses a bit field.
enum class EventCategory
{
	NONE = 0,
	EVENT_CATEGORY_INPUT = BIT(0),
	EVENT_CATEGORY_KEYBOARD = BIT(1),
	EVENT_CATEGORY_MOUSE = BIT(2),
	EVENT_CATEGORY_MOUSE_BUTTON = BIT(3)
};

#define EVENT_CLASS_TYPE(type) static EventType getStaticType() { return EventType::##type; }\
								virtual EventType getEventType() const override { return getStaticType(); }\
								virtual const char* getName() const override { return #type; };
// ## = token-pasting operator - joins separate tokens into a single token.
// # = number-sign converts macro parameter to string literal.
// Have virtual

#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override { return category; }
// ^^^^ Macros for returning EventType specific information. Made to avoid having to copy & paste these function within each Event derived class.


// Doesn't buffer events and stash them for an event part of an tick.
// Blocking function - will handle event then move on with tick.

class Event
{
//	// Friend class can access protected & private fields of members.
//	friend class EventDispatcher;

public:
	virtual EventType getEventType() const = 0;
	virtual int getCategoryFlags() const = 0;

	////////////////////////////////////////////////////////////
	///@author jade
	/// @brief Check for whether or not event is in the passed in category - 
	/// events can be in multiple categories.
	///	@return bool
	///////////////////////////////////////////////////////////////
	inline bool isInCategory(EventCategory category)
	{
		return getCategoryFlags() & int(category);
	}

	////////////////////////////////////////////////////////////
	/// \brief Override and set to return char array of event name - again for debugging purposes. 
	///////////////////////////////////////////////////////////////
	virtual const char* getName() const = 0;
	////////////////////////////////////////////////////////////
	/// \brief Returns event name for debugging purposes. 
	///////////////////////////////////////////////////////////////
	virtual std::string toString() const { return getName(); }

	////////////////////////////////////////////////////////////
	/// \brief Override and use to return event specific debug info for debugging.
	///////////////////////////////////////////////////////////////
	virtual std::string getDebugInfo() {} 

protected:
	////////////////////////////////////////////////////////////
	/// \brief Handled state of event. 
	///////////////////////////////////////////////////////////////
	bool handled = false;
};

