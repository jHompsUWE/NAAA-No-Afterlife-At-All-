#include "pch.h"
#include "GameMenu.h"



bool GameMenu::init(HWND _window, int _width, int _height)
{
	return GameStateBase::init(_window, _width, _height);
}

void GameMenu::reset()
{

}

State GameMenu::update(GameData& _game_data)
{
	return GameStateBase::update(_game_data);
}

State GameMenu::lateUpdate(GameData& _game_data)
{
	return GameStateBase::lateUpdate(_game_data);
}

void GameMenu::render3D()
{
	
	GameStateBase::render3D();
}

void GameMenu::render2D()
{
	GameStateBase::render2D();
}