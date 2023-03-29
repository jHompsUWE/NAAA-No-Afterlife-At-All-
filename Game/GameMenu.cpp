#include "pch.h"
#include "GameMenu.h"
#include "GameData.h"
#include "GameObject2D.h";
#include "Button.h"
#include <iostream>

#include "VBQuad.h"

bool GameMenu::init(HWND _window, int _width, int _height,GameData* gamedata)
{
	newGame = new Button(m_d3dDevice.Get(), nullptr);
	newGame->SetScale(Vector2(40, 15));
	newGame->SetPos(120, 70);
	newGame->SetBounds();
	m_GameObjects2D.push_back(newGame);

	for (int i = 0; i < 3; i++)
	{
		NFButtons[i] = new Button(m_d3dDevice.Get(), nullptr);
		NFButtons[i]->SetScale(Vector2(40, 15));
		NFButtons[i]->SetBounds();

		m_GameObjects2D.push_back(NFButtons[i]);
	}

	for (int i = 0; i < 4; i++)
	{
		ButtonsText[i] = new TextGO2D("0");
		ButtonsText[i]->SetScale(0.7);
		ButtonsText[i]->SetColour(Colors::Black);

		m_GameObjects2D.push_back(ButtonsText[i]);
	}

	ButtonsText[0]->SetString("New Game");
	ButtonsText[0]->SetPos(40, 50);

	NFButtons[0]->SetName("Load Game");
	NFButtons[0]->SetPos(400, 70);

	ButtonsText[1]->SetString("Load Game");
	ButtonsText[1]->SetPos(320, 50);

	NFButtons[1]->SetName("Load Scenario");
	NFButtons[1]->SetPos(680, 70);

	ButtonsText[2]->SetString("Scenario");
	ButtonsText[2]->SetPos(600, 50);

	NFButtons[2]->SetName("Quit Game");
	NFButtons[2]->SetPos(400, 530);

	ButtonsText[3]->SetString("Quit Game");
	ButtonsText[3]->SetPos(320, 510);
	
	return GameStateBase::init(_window, _width, _height,gamedata);
}

void GameMenu::reset()
{

}

State GameMenu::update(GameData& _game_data)
{
	if (newGame->pressed)
	{
		return State::GAME_PLAY;
	}

	for (int i = 0; i < 3; i++)
	{
		if (NFButtons[i]->pressed)
		{
			std::cout << NFButtons[i]->buttonName << "\n";
			NFButtons[i]->pressed = false;
		}
	}

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