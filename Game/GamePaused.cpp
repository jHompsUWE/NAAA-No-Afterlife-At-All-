#include "pch.h"
#include "GamePaused.h"



bool GamePaused::init(HWND _window, int _width, int _height)
{
	return true;
}

void GamePaused::reset()
{

}

State GamePaused::update(GameData& _game_data)
{
	return GameStateBase::update(_game_data);
}

State GamePaused::lateUpdate(GameData& _game_data)
{
	return GameStateBase::lateUpdate(_game_data);
}

void GamePaused::render3D()
{
	GameStateBase::render3D();
}

void GamePaused::render2D()
{
	GameStateBase::render2D();
}