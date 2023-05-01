#ifndef _GAME_DATA_H_
#define _GAME_DATA_H_

//=================================================================
//Data to be passed by game to all Game Objects via Tick
//=================================================================

#include "GameState.h"
#include "GameStateBase.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "GamePad.h"

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
	Mouse::State m_MS_last;
	GamePad::ButtonStateTracker m_GP_buttons;
	GamePad::State m_GP_state;
	bool mouse_over_UI = false;
	
	int Year = 0;
	bool game_paused = false;
};
#endif
