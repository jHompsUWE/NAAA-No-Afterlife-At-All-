#ifndef _GAME_DATA_H_
#define _GAME_DATA_H_

//=================================================================
//Data to be passed by game to all Game Objects via Tick
//=================================================================

#include "GameState.h"
#include "GameStateBase.h"
#include "Keyboard.h"
#include "Mouse.h"

using namespace DirectX;

struct GameData
{
	float m_dt;  //time step since last frame
	GameState m_GS; //global GameState
	State current_state;

	//player input
	Keyboard::State m_KBS;
	Mouse::State m_MS;
	Keyboard::KeyboardStateTracker m_KBS_tracker;
	Mouse::ButtonStateTracker m_mouseButtons;
	int Year = 0;
	bool game_paused = false;
};
#endif
