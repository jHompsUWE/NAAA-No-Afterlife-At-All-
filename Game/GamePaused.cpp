#include "pch.h"
#include "GamePaused.h"

GamePaused::GamePaused(State _state, GameData* _GD, DrawData* _DD, DrawData2D* _DD2D) : GameStateBase(_state, _GD, _DD, _DD2D)
{

}

bool GamePaused::init()
{
	return true;
}

void GamePaused::reset()
{

}

State GamePaused::update()
{
	return m_state;
}

void GamePaused::render()
{

}