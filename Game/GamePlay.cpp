#include "pch.h"
#include "GamePlay.h"


#include "GameManager.h"
#include "light.h"
#include "TextGO2D.h"
#include "UIRemote.h"
#include "Window.h"


bool GamePlay::init(HWND _window, int _width, int _height)
{
	m_light = new Light(Vector3(0.0f, 100.0f, 160.0f), Color(1.0f, 1.0f, 1.0f, 1.0f), Color(0.4f, 0.1f, 0.1f, 1.0f));
	m_GameObjects.push_back(m_light);
	
	
	Window* logo = new Window("logo_small", m_d3dDevice.Get());
	logo->SetPos(200.0f * Vector2::One);
	m_GameObjects2D.push_back(logo);
	

	TextGO2D* text = new TextGO2D("Test Text");
	text->SetPos(Vector2(100, 10));
	text->SetColour(Color((float*)&Colors::Yellow));
	m_GameObjects2D.push_back(text);

	UIRemote* remote = new UIRemote(m_d3dDevice.Get(), logo);
	remote->SetPos(100,230);
	remote->SetButtonPos();
	m_GameObjects2D.push_back(remote);
	
	GameManager::get()->awake();
	return GameStateBase::init(_window, _width, _height);
}

void GamePlay::reset()
{

}

State GamePlay::update(DX::StepTimer const& _timer)
{
	GameManager::get()->update(_timer);
	
	return GameStateBase::update(_timer);
}

State GamePlay::lateUpdate(DX::StepTimer const& _timer)
{
	GameManager::get()->lateUpdate(_timer);
	return GameStateBase::lateUpdate(_timer);
}

void GamePlay::render3D()
{
	GameManager::get()->render(m_DD);
	GameStateBase::render3D();
}

void GamePlay::render2D()
{
	
	GameStateBase::render2D();
}

