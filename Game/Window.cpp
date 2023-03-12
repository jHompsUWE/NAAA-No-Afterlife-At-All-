#include "pch.h"
#include "Window.h"
#include "DDSTextureLoader.h"
#include "DrawData2D.h"
#include "GameData.h"
#include "helper.h"
#include <iostream>
#include "Mouse.h"

Window::Window(string _fileName, ID3D11Device* _GD) :m_pTextureRV(nullptr)
{
	string fullfilename = "../Assets/" + _fileName + ".dds";
	HRESULT hr = CreateDDSTextureFromFile(_GD, Helper::charToWChar(fullfilename.c_str()), nullptr, &m_pTextureRV);
	if (hr != S_OK)
	{
		CreateDDSTextureFromFile(_GD, L"../Assets/white.dds", nullptr, &m_pTextureRV);
		cout << "Missing Texture : " << _fileName << endl;
	}

	//this nasty thing is required to find out the size of this image!
	ID3D11Resource* pResource;
	D3D11_TEXTURE2D_DESC Desc;
	m_pTextureRV->GetResource(&pResource);
	((ID3D11Texture2D*)pResource)->GetDesc(&Desc);

	m_origin = 0.5f * Vector2((float)Desc.Width, (float)Desc.Height);//around which rotation and scaing is done



	if (hr != S_OK)
	{
		SetScale(20.0f);
		m_colour = Colors::HotPink;
	}

	bounds = { (long)m_origin.x,(long)m_origin.y,(long)(Desc.Width * m_scale.x), (long)(Desc.Height * m_scale.y) };
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
	bounds.x = m_pos.x - (bounds.width / 2);
	bounds.y = m_pos.y - (bounds.height / 2);



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
	}

	if (dragged == true && _GD->m_mouseButtons.leftButton == Mouse::ButtonStateTracker::RELEASED)
	{
		dragged = false;
	}
}



void Window::Draw(DrawData2D* _DD)
{
	//nullptr can be changed to a RECT* to define what area of this image to grab
	//you can also add an extra value at the end to define layer depth
	//right click and "Go to Defintion/Declaration" to see other version of this in DXTK

	if (renderable)
	{
		_DD->m_Sprites->Draw(m_pTextureRV, m_pos, nullptr, m_colour, m_rotation, m_origin, m_scale, SpriteEffects_None);
	}

}