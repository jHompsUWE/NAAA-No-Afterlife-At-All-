#include "pch.h"
#include "ButtonSelectBW.h"
#include "DDSTextureLoader.h"
#include "DrawData2D.h"
#include "GameData.h"
#include "helper.h"
#include "Mouse.h"
#include <iostream>

ButtonSelectBW::ButtonSelectBW(ID3D11Device* _GD, GameObject2D* _parent, string buttonName) :m_pTextureRV(nullptr)
{

	CreateDDSTextureFromFile(_GD, L"../Assets/white.dds", nullptr, &m_pTextureRV);


	//this nasty thing is required to find out the size of this image!
	ID3D11Resource* pResource;
	D3D11_TEXTURE2D_DESC Desc;
	m_pTextureRV->GetResource(&pResource);
	((ID3D11Texture2D*)pResource)->GetDesc(&Desc);

	m_origin = 0.5f * Vector2((float)Desc.Width, (float)Desc.Height);//around which rotation and scaing is done

	m_colour = Colors::White;


	bounds = { (long)m_origin.x,(long)m_origin.y,(long)(Desc.Width * m_scale.x), (long)(Desc.Height * m_scale.y) };

	parentWindow = _parent;

	buildName = new TextGO2D(buttonName);
	buildName->SetColour(Colors::Black);
	buildName->SetScale(0.4);

	buildCost = new TextGO2D("100,000");
	buildCost->SetColour(Colors::Black);
	buildCost->SetScale(0.3);
}

ButtonSelectBW::~ButtonSelectBW()
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
void ButtonSelectBW::SetBounds()
{
	ID3D11Resource* pResource;
	D3D11_TEXTURE2D_DESC Desc;
	m_pTextureRV->GetResource(&pResource);
	((ID3D11Texture2D*)pResource)->GetDesc(&Desc);

	bounds = { (long)m_origin.x,(long)m_origin.y,(long)(Desc.Width * m_scale.x), (long)(Desc.Height * m_scale.y) };

	setTextPos();
}

/// <summary>
/// Sets the name and cost text positions
/// </summary>
void ButtonSelectBW::setTextPos()
{
	buildName->SetPos(this->GetPos().x - (bounds.width / 4 - buildName->GetString().length()), this->GetPos().y - (bounds.height / 2));
	buildCost->SetPos(this->GetPos().x - bounds.width / 3 - (buildCost->GetString().length()), this->GetPos().y + (bounds.height / 4));
}

/// <summary>
/// Set the string of either text
/// </summary>
/// <param name="name">True- Sets name, False- Sets cost</param>
/// <param name="_name">The string value to set it to</param>
void ButtonSelectBW::SetText(bool name, string _name)
{
	if (name)
	{
		buildName->SetString(_name);
	}
	else
	{
		buildCost->SetString(_name);
	}
}

/// <summary>
/// Set the type of event the button triggers
/// </summary>
/// <param name="_event_type"></param>
void ButtonSelectBW::SetType(EventType _event_type)
{
	event_type = _event_type;
}

/// <summary>
/// Checks to see if button is hovered over
/// </summary>
/// <param name="_GD"></param>
void ButtonSelectBW::Tick(GameData* _GD)
{
	bounds.x = m_pos.x - (bounds.width / 2);
	bounds.y = m_pos.y - (bounds.height / 2);


	int mouseX = _GD->m_MS.x;
	int mouseY = _GD->m_MS.y;
	Vector2 mousepos{ (float)mouseX,(float)mouseY };

	if (bounds.Contains(Vector2{ (float)_GD->m_MS.x,(float)_GD->m_MS.y }) && hover == false)
	{
		SetHover(true);
	}

	buildName->Tick(_GD);
	buildCost->Tick(_GD);
}

/// <summary>
/// Sets if the button is hovered over or not
/// </summary>
/// <param name="_hover"></param>
void ButtonSelectBW::SetHover(bool _hover)
{
	if (_hover)
	{
		hover = true;
		SetColour(Colors::Yellow);
	}
	else
	{
		hover = false;
		SetColour(Colors::White);
	}
}

//NOT NEEDED?
void ButtonSelectBW::toggle()
{
	if (toggleWindow != nullptr)
	{
		toggleWindow->renderable = !toggleWindow->renderable;
	}
}


/// <summary>
/// Renders the button and its text
/// </summary>
/// <param name="_DD"></param>
void ButtonSelectBW::Draw(DrawData2D* _DD)
{
	//nullptr can be changed to a RECT* to define what area of this image to grab
	//you can also add an extra value at the end to define layer depth
	//right click and "Go to Defintion/Declaration" to see other version of this in DXTK
	_DD->m_Sprites->Draw(m_pTextureRV, m_pos, nullptr, m_colour, m_rotation, m_origin, m_scale, SpriteEffects_None);

	buildName->Draw(_DD);
	buildCost->Draw(_DD);
}