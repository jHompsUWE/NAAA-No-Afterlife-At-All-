#pragma once

#include "Manager.h"
#include "Listener.h"

class InputListenerTest: public Manager, public Listener
{
	void update(DX::StepTimer const& _timer) override;
	void onEvent(const Event& event) override;
};

