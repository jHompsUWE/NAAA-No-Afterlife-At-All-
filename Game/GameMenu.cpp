#include "pch.h"
#include "GameMenu.h"



bool GameMenu::init(HWND _window, int _width, int _height)
{
	return GameStateBase::init(_window, _width, _height);
}

void GameMenu::reset()
{

}

State GameMenu::update(DX::StepTimer const& _timer)
{
	return GameStateBase::update(_timer);
}

State GameMenu::lateUpdate(DX::StepTimer const& _timer)
{
	return GameStateBase::lateUpdate(_timer);
}

void GameMenu::render3D()
{
	
	GameStateBase::render3D();
}

void GameMenu::render2D()
{
	GameStateBase::render2D();
}