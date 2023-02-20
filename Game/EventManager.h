#pragma once

#include "Manager.h"
#include <iostream>

class EventManager : public Manager
{
public:
	EventManager();
	~EventManager();

	void update() override;
};


