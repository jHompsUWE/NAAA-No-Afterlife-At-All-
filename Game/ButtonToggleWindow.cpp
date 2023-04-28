#include "pch.h"
#include "ButtonToggleWindow.h"
#include "DDSTextureLoader.h"
#include "DrawData2D.h"
#include "GameData.h"
#include "helper.h"
#include "Mouse.h"
#include <iostream>

ButtonToggleWindow::ButtonToggleWindow(ID3D11Device* _GD, GameObject2D* _parent)
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

ButtonToggleWindow::ButtonToggleWindow(ID3D11Device* _GD, GameObject2D* _parent, string _name, Vector2 _scale, Vector2 _position, EventType _event)
{
	CreateDDSTextureFromFile(_GD, L"../Assets/white.dds", nullptr, &m_pTextureRV);

	//this nasty thing is required to find out the size of this image!
	ID3D11Resource* pResource;
	D3D11_TEXTURE2D_DESC Desc;
	m_pTextureRV->GetResource(&pResource);
	((ID3D11Texture2D*)pResource)->GetDesc(&Desc);

	m_origin = 0.5f * Vector2((float)Desc.Width, (float)Desc.Height);//around which rotation and scaing is done

	parentWindow = _parent;
	SetName(_name);
	SetScale(_scale);
	SetPos(_position);
	SetType(_event);
	m_colour = Colors::Lavender;

	bounds = { (long)m_origin.x,(long)m_origin.y,(long)(Desc.Width * m_scale.x), (long)(Desc.Height * m_scale.y) };
}

ButtonToggleWindow::~ButtonToggleWindow()
{
	if (m_pTextureRV)
	{
		m_pTextureRV->Release();
		m_pTextureRV = nullptr;
	}
}

/// <summary>
/// Set the window for the button to toggle
/// </summary>
/// <param name="toggle"></param>
void ButtonToggleWindow::SetToggle(Window* toggle)
{
	toggleWindow = toggle;
}

/// <summary>
/// Toggle the rendering of the button's set window
/// </summary>
void ButtonToggleWindow::Toggle()
{
	if (toggleWindow != nullptr)
	{
		toggleWindow->renderable = !toggleWindow->renderable;
	}
}
