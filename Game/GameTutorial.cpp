#include "pch.h"
#include "GameTutorial.h"



bool GameTutorial::init(HWND _window, int _width, int _height)
{
	return true;
}

void GameTutorial::reset()
{

}

State GameTutorial::update(DX::StepTimer const& _timer)
{
	return GameStateBase::update(_timer);
}

State GameTutorial::lateUpdate(DX::StepTimer const& _timer)
{
	return GameStateBase::lateUpdate(_timer);
}

void GameTutorial::render3D()
{
	GameStateBase::render3D();
}

void GameTutorial::render2D()
{
	GameStateBase::render2D();
}

