#include "pch.h"
#include "Button.h"
#include "DDSTextureLoader.h"
#include "DrawData2D.h"
#include "GameData.h"
#include "helper.h"
#include "Mouse.h"
#include <iostream>

Button::Button(string _fileName, ID3D11Device* _GD, ImageGO2D* parent) :m_pTextureRV(nullptr)
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
		SetScale(10.0f);
		m_colour = Colors::Lavender;
	}

	bounds = { (long)m_origin.x,(long)m_origin.y,(long)(Desc.Width * m_scale.x), (long)(Desc.Height * m_scale.y) };


	parentWindow = parent;
}

Button::~Button()
{
	if (m_pTextureRV)
	{
		m_pTextureRV->Release();
		m_pTextureRV = nullptr;
	}
}

void Button::Tick(GameData* _GD)
{
	bounds.x = m_pos.x - (bounds.width / 2);
	bounds.y = m_pos.y - (bounds.height / 2);


	int mouseX = _GD->m_MS.x;
	int mouseY = _GD->m_MS.y;
	Vector2 mousepos{ (float)mouseX,(float)mouseY };

	if (_GD->m_mouseButtons.leftButton == Mouse::ButtonStateTracker::PRESSED)
	{
		if (bounds.Contains(Vector2{ (float)_GD->m_MS.x,(float)_GD->m_MS.y }))
		{
			std::cout << "Clck";
			parentWindow->renderable = !parentWindow->renderable;
		}
		
	}

	if (_GD->m_MS.leftButton == 1)
	{
		m_pos.x = parentWindow->GetPos().x;
		m_pos.y = parentWindow->GetPos().y + 30;
	}

	//if (bounds.Contains(Vector2{ (float)_GD->m_MS.x,(float)_GD->m_MS.y }) && _GD->m_MS.leftButton == 1)
	//{
	//	std::cout << "Pushed";
	//	////MOUSE CONTROL SCHEME HERE
	//	//m_pos.x = _GD->m_MS.x;
	//	//m_pos.y = _GD->m_MS.y;
	//}
}



void Button::Draw(DrawData2D* _DD)
{
	//nullptr can be changed to a RECT* to define what area of this image to grab
	//you can also add an extra value at the end to define layer depth
	//right click and "Go to Defintion/Declaration" to see other version of this in DXTK
	_DD->m_Sprites->Draw(m_pTextureRV, m_pos, nullptr, m_colour, m_rotation, m_origin, m_scale, SpriteEffects_None);
}