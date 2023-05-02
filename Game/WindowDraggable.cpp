#include "pch.h"
#include "WindowDraggable.h"
#include "DDSTextureLoader.h"
#include "DrawData2D.h"
#include "GameData.h"
#include "helper.h"
#include <iostream>
#include "GameManager.h"

WindowDraggable::WindowDraggable(ID3D11Device* _GD, string _windowName, bool render, XMVECTORF32 _colour)
{
	GameManager::get()->getEventManager()->addListener(this);
	CreateDDSTextureFromFile(_GD, L"../Assets/white.dds", nullptr, &m_pTextureRV);


	//this nasty thing is required to find out the size of this image!
	ID3D11Resource* pResource;
	D3D11_TEXTURE2D_DESC Desc;
	m_pTextureRV->GetResource(&pResource);
	((ID3D11Texture2D*)pResource)->GetDesc(&Desc);

	m_origin = 0.5f * Vector2((float)Desc.Width, (float)Desc.Height);//around which rotation and scaing is done


	m_scale = Vector2{ 39,20 };
	m_colour = _colour;


	bounds = { (long)m_origin.x,(long)m_origin.y,(long)(Desc.Width * m_scale.x), (long)(Desc.Height * m_scale.y) };

	windowname = new TextGO2D(_windowName);
	windowname->SetColour(Colors::Black);
	windowname->SetScale(0.7);

	renderable = render;
}

WindowDraggable::~WindowDraggable()
{
	if (m_pTextureRV)
	{
		m_pTextureRV->Release();
		m_pTextureRV = nullptr;
	}
}

/// <summary>
/// Sets the position of text relative to the window, 
/// and notes difference between text position and window position
/// </summary>
void WindowDraggable::SetTextPos()
{
	windowname->SetPos(m_pos.x - (bounds.width / 2), m_pos.y - (bounds.height / 2));

	windowname->differenceX = windowname->GetPos().x - m_pos.x;
	windowname->differenceY = windowname->GetPos().y - m_pos.y;
}

/// <summary>
/// Checks to see if dragged
/// </summary>
/// <param name="_GD"></param>
void WindowDraggable::Tick(GameData* _GD)
{
	
}


/// <summary>
/// Renders window and its text
/// </summary>
/// <param name="_DD"></param>
void WindowDraggable::Draw(DrawData2D* _DD)
{
	//nullptr can be changed to a RECT* to define what area of this image to grab
	//you can also add an extra value at the end to define layer depth
	//right click and "Go to Defintion/Declaration" to see other version of this in DXTK

	if (renderable)
	{
		_DD->m_Sprites->Draw(m_pTextureRV, m_pos, nullptr, m_colour, m_rotation, m_origin, m_scale, SpriteEffects_None);
		windowname->Draw(_DD);
	}

}

void WindowDraggable::onEvent(const Event& event)
{
	switch (event.type)
	{
		case EventType::CURSOR_SELECTED:
			{
				bounds.x = m_pos.x - (bounds.width / 2);
				bounds.y = m_pos.y - (bounds.height / 2);

				int mouseX = event.payload.cursor_data.x;
				int mouseY = event.payload.cursor_data.y;
				Vector2 mousepos{ (float)mouseX,(float)mouseY };

				if (event.payload.cursor_data.selected && bounds.Contains(mousepos) && renderable)
				{
					differenceX = m_pos.x - event.payload.cursor_data.x;
					differenceY = m_pos.y - event.payload.cursor_data.y;
					dragged = true;
				}
				else if (dragged && !event.payload.cursor_data.selected)
				{
					dragged = false;
				}
				
				break;
			}
		case EventType::CURSOR_MOVED:
			{
				if (dragged)
				{
					m_pos.x = event.payload.cursor_data.x + differenceX;
					m_pos.y = event.payload.cursor_data.y + differenceY;
					windowname->SetPos(m_pos.x + windowname->differenceX, m_pos.y + windowname->differenceY);
				}
				break;
			}
		default: ;
	}
}
