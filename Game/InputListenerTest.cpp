#include "pch.h"
#include "InputListenerTest.h"
#include <iostream>

void InputListenerTest::update(DX::StepTimer const& _timer)
{
}

void InputListenerTest::onEvent(const Event& event)
{
	if (event.type == EventType::ACTIVATES_OMNIBULGE_LOVEDOME_ZONNIG)
	{
		std::cout << "activate lovedome stuff" << std::endl;
	}
	if (event.type == EventType::GREEN_ZONING)
	{
		std::cout << "activate green stuff" << std::endl;
	}
}
