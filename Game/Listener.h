#pragma once
#include "Event.h"

class Listener
{
public:
	~Listener() = default;
	virtual void OnEvent(Event* event) {};

protected:
	// Constructor is protected so that it cannot be instantiated outside of an derived class.
	Listener() = default;
};

