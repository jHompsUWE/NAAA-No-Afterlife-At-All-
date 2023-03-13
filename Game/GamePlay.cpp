#include "pch.h"
#include "GamePlay.h"

GamePlay::GamePlay(State _state, GameData* _GD, DrawData* _DD, DrawData2D* _DD2D) : GameStateBase(_state, _GD, _DD, _DD2D)
{

	//TextGO2D* text = new TextGO2D("Test Text");
	//text->SetPos(Vector2(100, 10));
	//text->SetColour(Color((float*)&Colors::Yellow));
	//m_GameObjects2D.push_back(text);
	
    Window* Planetview = new Window("bug_test", m_d3dDevice.Get(), "Planetview", false, Colors::LightSkyBlue);
    Planetview->SetPos(300, 100);
    m_GameObjects2D.push_back(Planetview);
    Planetview->SetTextPos();

    Window* Graphview = new Window("bug_test", m_d3dDevice.Get(), "Graphview", false, Colors::LightBlue);
    Graphview->SetPos(600, 100);
    m_GameObjects2D.push_back(Graphview);
    Graphview->SetTextPos();

    Window* Soulview = new Window("bug_test", m_d3dDevice.Get(), "Soulview", false, Colors::LightGreen);
    Soulview->SetPos(300, 200);
    m_GameObjects2D.push_back(Soulview);
    Soulview->SetTextPos();

    Window* MacroManager = new Window("bug_test", m_d3dDevice.Get(), "Macro\nManager", false, Colors::LightYellow);
    MacroManager->SetPos(600, 200);
    m_GameObjects2D.push_back(MacroManager);
    MacroManager->SetTextPos();

    Window* Mapview = new Window("bug_test", m_d3dDevice.Get(), "Mapview", false, Colors::LightPink);
    Mapview->SetPos(300, 300);
    m_GameObjects2D.push_back(Mapview);
    Mapview->SetTextPos();

    Window* Advisors = new Window("bug_test", m_d3dDevice.Get(), "Advisors", false, Colors::LightSalmon);
    Advisors->SetPos(600, 300);
    m_GameObjects2D.push_back(Advisors);
    Advisors->SetTextPos();

    Window* MicroView = new Window("bug_test", m_d3dDevice.Get(), "MicroView", false, Colors::LightCoral);
    MicroView->SetPos(300, 400);
    m_GameObjects2D.push_back(MicroView);
    MicroView->SetTextPos();

    UIRemote* remote = new UIRemote(m_d3dDevice.Get());
    remote->SetPos(100, 230);
    remote->SetButtonBounds();
    m_GameObjects2D.push_back(remote);

    remote->SetButtonToggle(26, Planetview);
    remote->SetButtonToggle(27, Graphview);
    remote->SetButtonToggle(28, Soulview);
    remote->SetButtonToggle(29, MacroManager);
    remote->SetButtonToggle(30, Mapview);
    remote->SetButtonToggle(31, Advisors);
    remote->SetButtonToggle(32, MicroView);

    AnimatedImageGO2D* animated_sprite_test = new AnimatedImageGO2D("angel-advisor-Sheet", 305, m_d3dDevice.Get());
    animated_sprite_test->NewAnimation("idle", 5, 60, Vector2(0, 0), true);
    animated_sprite_test->SetPos(1.0f * Vector2::One);
    m_GameObjects2D.push_back(animated_sprite_test);

	GameManager::get()->awake();
	return GameStateBase::init(_window, _width, _height);
}

bool GamePlay::init()
{
	return true;
}

void GamePlay::reset()
{

}

State GamePlay::update()
{
	return m_state;
}

void GamePlay::render()
{

}