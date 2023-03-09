#pragma once
#include "Event.h"

class Listener
{
public:
	virtual ~Listener() = default;

	////////////////////////////////////////////////////////////
	/// \brief Interface function for concrete listeners to override. \n Allows listener derived classes to receive events from the EventManager.
	///	\param event The event to be acted upon.
	////////////////////////////////////////////////////////////
	virtual void onEvent(const Event& event) {};

protected:
	// Constructor is protected so that it cannot be instantiated outside of an derived class.
	Listener() = default;
};
