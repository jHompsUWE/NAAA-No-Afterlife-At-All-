#include "pch.h"
#include "Window.h"
#include "DDSTextureLoader.h"
#include "DrawData2D.h"
#include "GameData.h"
#include "helper.h"
#include <iostream>
#include "Mouse.h"

Window::Window() :m_pTextureRV(nullptr)
{

}

Window::~Window()
{
	if (m_pTextureRV)
	{
		m_pTextureRV->Release();
		m_pTextureRV = nullptr;
	}
}

void Window::Tick(GameData* _GD)
{
}

void Window::Draw(DrawData2D* _DD)
{
}