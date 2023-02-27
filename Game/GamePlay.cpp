#include "pch.h"
#include "GamePlay.h"

GamePlay::GamePlay(State _state, GameData* _GD, DrawData* _DD, DrawData2D* _DD2D) : GameStateBase(_state, _GD, _DD, _DD2D)
{

}

bool GamePlay::init()
{
	return true;
}

void GamePlay::reset()
{

}

State GamePlay::update()
{
	return m_state;
}

void GamePlay::render()
{

}