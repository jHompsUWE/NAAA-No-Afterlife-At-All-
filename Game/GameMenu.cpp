#include "pch.h"
#include "GameMenu.h"

GameMenu::GameMenu(State _state, GameData* _GD, DrawData* _DD, DrawData2D* _DD2D) : GameStateBase(_state, _GD, _DD, _DD2D)
{

}

bool GameMenu::init()
{
	return true;
}

void GameMenu::reset()
{

}

State GameMenu::update()
{
	return m_state;
}

void GameMenu::render()
{

}