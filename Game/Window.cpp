#include "pch.h"
#include "Window.h"
#include "DDSTextureLoader.h"
#include "DrawData2D.h"
#include "GameData.h"
#include "helper.h"
#include <iostream>
#include "Mouse.h"

Window::Window()
{
	windowname = new TextGO2D("Hi");
	windowname->SetColour(Colors::White);
	windowname->SetScale(0.7);

	renderable = false;
	is_sprite = true;
}

Window::Window(ID3D11Device* _GD)
{
}

Window::Window(XMVECTORF32 _colour, string _windowName, bool render,  ID3D11Device* _GD) :m_pTextureRV(nullptr)
{
	sprite = new ImageGO2D("", _GD);
	sprite->SetColour(_colour);
	sprite->SetScale(Vector2(39, 20));


	windowname = new TextGO2D(_windowName);
	windowname->SetColour(Colors::Black);
	windowname->SetScale(0.7);

	renderable = render;
}

Window::Window(string _fileName, string _windowName, bool render, ID3D11Device* _GD)
{
	sprite = new ImageGO2D(_fileName, _GD);

	windowname = new TextGO2D(_windowName);
	windowname->SetColour(Colors::Black);
	windowname->SetScale(0.7);

	renderable = render;
}

Window::~Window()
{
	
	if (sprite != nullptr)
	{
		delete sprite;
	}
}

void Window::SetTextPos()
{
	windowname->SetPos(m_pos.x - (bounds.width/2), m_pos.y - (bounds.height/2));

	windowname->differenceX = windowname->GetPos().x - m_pos.x;
	windowname->differenceY = windowname->GetPos().y - m_pos.y;
}

void Window::SetSpriteReference(ImageGO2D asprite)
{
	sprite = &asprite;
}

void Window::Drag(GameData* _GD)
{

	bounds = sprite->GetCurrentBounds(this->m_pos, is_sprite);
	

	int mouseX = _GD->m_MS.x;
	int mouseY = _GD->m_MS.y;
	Vector2 mousepos{ (float)mouseX,(float)mouseY };

	if (renderable && bounds.Contains(Vector2{ (float)_GD->m_MS.x,(float)_GD->m_MS.y }) && _GD->m_mouseButtons.leftButton == Mouse::ButtonStateTracker::PRESSED)
	{
		differenceX = m_pos.x - _GD->m_MS.x;
		differenceY = m_pos.y - _GD->m_MS.y;

		dragged = true;
	}

	if (dragged == true && _GD->m_MS.leftButton == 1)
	{
		m_pos.x = _GD->m_MS.x + differenceX;
		m_pos.y = _GD->m_MS.y + differenceY;

		windowname->SetPos(m_pos.x + windowname->differenceX, m_pos.y + windowname->differenceY);
	}

	if (dragged == true && _GD->m_mouseButtons.leftButton == Mouse::ButtonStateTracker::RELEASED)
	{
		dragged = false;
	}
	sprite->SetPos(Vector2(windowname->GetPos().x + bounds.width / 2, windowname->GetPos().y + bounds.height / 2));
}



void Window::Tick(GameData* _GD)
{
	Drag(_GD);
}



void Window::Draw(DrawData2D* _DD)
{
	//nullptr can be changed to a RECT* to define what area of this image to grab
	//you can also add an extra value at the end to define layer depth
	//right click and "Go to Defintion/Declaration" to see other version of this in DXTK

	if (renderable)
	{
		sprite->Draw(_DD);
		windowname->Draw(_DD);
	}

}