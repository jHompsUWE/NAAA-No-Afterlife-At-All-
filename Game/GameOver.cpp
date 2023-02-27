#include "pch.h"
#include "GameOver.h"

GameOver::GameOver(State _state, GameData* _GD, DrawData* _DD, DrawData2D* _DD2D) : GameStateBase(_state, _GD, _DD, _DD2D)
{

}

bool GameOver::init()
{
	return true;
}

void GameOver::reset()
{

}

State GameOver::update()
{
	return m_state;
}

void GameOver::render()
{

}

