#pragma once

#include "DrawData.h"
#include "StepTimer.h"
#include "GameData.h"


class Manager
{
public:
	Manager() = default;
	~Manager() = default;

	////////////////////////////////////////////////////////////
	/// \brief Is called when the program initializes.
	////////////////////////////////////////////////////////////
	virtual void awake() {};

	////////////////////////////////////////////////////////////
	/// \brief Called every cycle of the game loop.
	///	\param _timer DeltaTime.
	////////////////////////////////////////////////////////////
	virtual void update(DX::StepTimer const& _timer) = 0;

	////////////////////////////////////////////////////////////
	/// \brief Called every cycle of the game loop, but after update.
	///	\param _timer DeltaTime.
	////////////////////////////////////////////////////////////
	virtual void lateUpdate(DX::StepTimer const& _timer) {};

	virtual void render(DrawData* m_DD) {};
};
