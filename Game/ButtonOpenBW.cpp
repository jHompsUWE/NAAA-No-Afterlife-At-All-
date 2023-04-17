#include "pch.h"
#include "ButtonOpenBW.h"
#include "DDSTextureLoader.h"
#include "DrawData2D.h"
#include "GameData.h"
#include "helper.h"
#include "Mouse.h"
#include <iostream>

ButtonOpenBW::ButtonOpenBW(ID3D11Device* _GD, GameObject2D* _parent, BuildingWindow* _toggle) :m_pTextureRV(nullptr)
{

	CreateDDSTextureFromFile(_GD, L"../Assets/white.dds", nullptr, &m_pTextureRV);


	//this nasty thing is required to find out the size of this image!
	ID3D11Resource* pResource;
	D3D11_TEXTURE2D_DESC Desc;
	m_pTextureRV->GetResource(&pResource);
	((ID3D11Texture2D*)pResource)->GetDesc(&Desc);

	m_origin = 0.5f * Vector2((float)Desc.Width, (float)Desc.Height);//around which rotation and scaing is done



	SetScale(6.f);
	m_colour = Colors::Lavender;


	bounds = { (long)m_origin.x,(long)m_origin.y,(long)(Desc.Width * m_scale.x), (long)(Desc.Height * m_scale.y) };

	parentWindow = _parent;
	toggleWindow = _toggle;
}

ButtonOpenBW::ButtonOpenBW(ID3D11Device* _GD, GameObject2D* _parent) :m_pTextureRV(nullptr)
{

	CreateDDSTextureFromFile(_GD, L"../Assets/white.dds", nullptr, &m_pTextureRV);


	//this nasty thing is required to find out the size of this image!
	ID3D11Resource* pResource;
	D3D11_TEXTURE2D_DESC Desc;
	m_pTextureRV->GetResource(&pResource);
	((ID3D11Texture2D*)pResource)->GetDesc(&Desc);

	m_origin = 0.5f * Vector2((float)Desc.Width, (float)Desc.Height);//around which rotation and scaing is done



	SetScale(6.f);
	m_colour = Colors::Lavender;


	bounds = { (long)m_origin.x,(long)m_origin.y,(long)(Desc.Width * m_scale.x), (long)(Desc.Height * m_scale.y) };

	parentWindow = _parent;
}

ButtonOpenBW::~ButtonOpenBW()
{
	if (m_pTextureRV)
	{
		m_pTextureRV->Release();
		m_pTextureRV = nullptr;
	}
}

/// <summary>
/// Sets the bounding box of the button
/// </summary>
void ButtonOpenBW::SetBounds()
{
	ID3D11Resource* pResource;
	D3D11_TEXTURE2D_DESC Desc;
	m_pTextureRV->GetResource(&pResource);
	((ID3D11Texture2D*)pResource)->GetDesc(&Desc);

	bounds = { (long)m_origin.x,(long)m_origin.y,(long)(Desc.Width * m_scale.x), (long)(Desc.Height * m_scale.y) };
}

/// <summary>
/// Sets the button name
/// </summary>
/// <param name="_name">string value to set it to</param>
void ButtonOpenBW::SetName(string _name)
{
	buttonName = _name;
}

/// <summary>
/// Sets the button event type to fire off when clicked
/// </summary>
/// <param name="_event_type"></param>
void ButtonOpenBW::SetType(EventType _event_type)
{
	event_type = _event_type;
}

/// <summary>
/// Set the window for the button to toggle
/// </summary>
/// <param name="toggle"></param>
void ButtonOpenBW::SetToggle(BuildingWindow* toggle)
{
	toggleWindow = toggle;
}

/// <summary>
/// Checks to see if button is pressed
/// </summary>
/// <param name="_GD"></param>
void ButtonOpenBW::Tick(GameData* _GD)
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
			toggle();
			pressed = true;
		}
	}
}


/// <summary>
/// Toggle the rendering of the button's set window
/// </summary>
void ButtonOpenBW::toggle()
{
	if (toggleWindow != nullptr)
	{
		toggleWindow->renderable = !toggleWindow->renderable;
	}
}


void ButtonOpenBW::Draw(DrawData2D* _DD)
{
	//nullptr can be changed to a RECT* to define what area of this image to grab
	//you can also add an extra value at the end to define layer depth
	//right click and "Go to Defintion/Declaration" to see other version of this in DXTK
	_DD->m_Sprites->Draw(m_pTextureRV, m_pos, nullptr, m_colour, m_rotation, m_origin, m_scale, SpriteEffects_None);
}