#include "pch.h"
#include "GameTutorial.h"



bool GameTutorial::init(HWND _window, int _width, int _height, GameData* _game_data)
{
	return true;
}

void GameTutorial::reset()
{

}

State GameTutorial::update(GameData& _game_data)
{
	return GameStateBase::update(_game_data);
}

State GameTutorial::lateUpdate(GameData& _game_data)
{
	return GameStateBase::lateUpdate(_game_data);
}

void GameTutorial::render3D()
{
	GameStateBase::render3D();
}

void GameTutorial::render2D()
{
	GameStateBase::render2D();
}

