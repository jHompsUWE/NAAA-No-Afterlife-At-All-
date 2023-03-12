#include "pch.h"
#include "GamePaused.h"



bool GamePaused::init(HWND _window, int _width, int _height)
{
	return true;
}

void GamePaused::reset()
{

}

State GamePaused::update(DX::StepTimer const& _timer)
{
	return GameStateBase::update(_timer);
}

State GamePaused::lateUpdate(DX::StepTimer const& _timer)
{
	return GameStateBase::lateUpdate(_timer);
}

void GamePaused::render3D()
{
	GameStateBase::render3D();
}

void GamePaused::render2D()
{
	GameStateBase::render2D();
}