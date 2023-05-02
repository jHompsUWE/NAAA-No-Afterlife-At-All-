#include "pch.h"
#include "GamePlay.h"
#include "GameManager.h"
#include "light.h"
#include "TextGO2D.h"
#include "UIRemote.h"
#include "Window.h"
#include "AnimatedImageGO2D.h"
#include "BuildingWindow.h"
#include "AdvisorWindow.h"



bool GamePlay::init(HWND _window, int _width, int _height, GameData* _game_data)
{
	m_light = new Light(Vector3(0.0f, 100.0f, 160.0f), Color(1.0f, 1.0f, 1.0f, 1.0f), Color(0.4f, 0.1f, 0.1f, 1.0f));
	m_GameObjects.push_back(m_light);
	

    /*BuildingWindow* threeWide = new BuildingWindow(m_d3dDevice.Get(), 3);
    threeWide->SetPos(300, 400);
    threeWide->SetTextPos();

    BuildingWindow* fourWide = new BuildingWindow(m_d3dDevice.Get(), 4);
    fourWide->SetPos(300, 400);
    fourWide->SetTextPos();

    BuildingWindow* fiveWide = new BuildingWindow(m_d3dDevice.Get(), 5);
    fiveWide->SetPos(300, 400);
    fiveWide->SetTextPos();*/

    //AdvisorWindow* advisor_window = new AdvisorWindow(m_d3dDevice.Get());
    //advisor_window->SetPos(300, 400);
    //m_GameObjects2D.push_back(advisor_window);

	return GameStateBase::init(_window, _width, _height, _game_data);
}

void GamePlay::reset()
{

}

State GamePlay::update(GameData& _game_data)
{
	return GameStateBase::update(_game_data);
}

State GamePlay::lateUpdate(GameData& _game_data)
{
	GameManager::get()->lateUpdate(_game_data);
	return GameStateBase::lateUpdate(_game_data);
}

void GamePlay::render3D()
{
	GameManager::get()->render(m_DD);
	GameStateBase::render3D();
}

void GamePlay::render2D()
{
    GameManager::get()->getUIManager()->Draw(m_DD2D);
	GameStateBase::render2D();
}

