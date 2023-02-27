#include "pch.h"
#include "GameTutorial.h"

GameTutorial::GameTutorial(State _state, GameData* _GD, DrawData* _DD, DrawData2D* _DD2D) : GameStateBase(_state, _GD, _DD, _DD2D)
{

}

bool GameTutorial::init()
{
	return true;
}

void GameTutorial::reset()
{

}

State GameTutorial::update()
{
	return m_state;
}

void GameTutorial::render()
{

}

