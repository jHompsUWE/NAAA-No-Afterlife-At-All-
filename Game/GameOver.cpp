#include "pch.h"
#include "GameOver.h"


bool GameOver::init(HWND _window, int _width, int _height)
{
	return true;
}

void GameOver::reset()
{

}

State GameOver::update(GameData& _game_data)
{
	return GameStateBase::update(_game_data);
}

State GameOver::lateUpdate(GameData& _game_data)
{
	return GameStateBase::lateUpdate(_game_data);
}

void GameOver::render3D()
{
	GameStateBase::render3D();
}

void GameOver::render2D()
{
	GameStateBase::render2D();
}
