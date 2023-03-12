#include "pch.h"
#include "GameOver.h"


bool GameOver::init(HWND _window, int _width, int _height)
{
	return true;
}

void GameOver::reset()
{

}

State GameOver::update(DX::StepTimer const& _timer)
{
	return GameStateBase::update(_timer);
}

State GameOver::lateUpdate(DX::StepTimer const& _timer)
{
	return GameStateBase::lateUpdate(_timer);
}

void GameOver::render3D()
{
	GameStateBase::render3D();
}

void GameOver::render2D()
{
	GameStateBase::render2D();
}

