#include "pch.h"
#include "BaseAnimateWindow.h"

#include "DDSTextureLoader.h"
#include "DrawData2D.h"
#include "GameData.h"
#include "helper.h"
#include <iostream>
#include "Mouse.h"


BaseAnimateWindow::BaseAnimateWindow()
{

}

BaseAnimateWindow::BaseAnimateWindow(string _fileName, ID3D11Device* _GD, string _windowName, bool render, XMVECTORF32 _colour) : m_pTextureRV(nullptr)
{
	string fullfilename = "../Assets/" + _fileName + ".dds";
	HRESULT hr = CreateDDSTextureFromFile(_GD, Helper::charToWChar(fullfilename.c_str()), nullptr, &m_pTextureRV);
	if (hr != S_OK)
	{
		CreateDDSTextureFromFile(_GD, L"../Assets/white.dds", nullptr, &m_pTextureRV);
	}

	//this nasty thing is required to find out the size of this image!
	ID3D11Resource* pResource;
	D3D11_TEXTURE2D_DESC Desc;
	m_pTextureRV->GetResource(&pResource);
	((ID3D11Texture2D*)pResource)->GetDesc(&Desc);

	m_origin = 0.5f * Vector2((float)Desc.Width, (float)Desc.Height);//around which rotation and scaing is done


	if (hr != S_OK)
	{
		m_scale = Vector2{ 39,20 };
		m_colour = _colour;
	}

	bounds = { (long)m_origin.x,(long)m_origin.y,(long)(Desc.Width * m_scale.x), (long)(Desc.Height * m_scale.y) };

	windowname = std::make_shared<TextGO2D>(_windowName);
	windowname->SetColour(Colors::Black);
	windowname->SetScale(0.7);

	renderable = render;


	Init(_GD);
}

BaseAnimateWindow::~BaseAnimateWindow()
{
	if (m_pTextureRV)
	{
		m_pTextureRV->Release();
		m_pTextureRV = nullptr;
	}
}

void BaseAnimateWindow::Init(ID3D11Device* _GD)
{
	close_button_sprite = std::make_shared<ImageGO2D>("close-button", _GD);
	close_button_sprite->SetOrigin(Vector2(close_button_sprite->GetImageSize().x, 0));



}

void BaseAnimateWindow::SetTextPos()
{
	windowname->SetPos(m_pos.x - (bounds.width / 2), m_pos.y - (bounds.height / 2));

	windowname->differenceX = windowname->GetPos().x - m_pos.x;
	windowname->differenceY = windowname->GetPos().y - m_pos.y;
}

void BaseAnimateWindow::DragBounds(GameData* _GD)
{
	bounds.x = m_pos.x - (bounds.width / 2);
	bounds.y = m_pos.y - (bounds.height / 2);


	Vector2 mousepos{ (float)_GD->m_MS.x,(float)_GD->m_MS.y };

	if (renderable && bounds.Contains(mousepos) && _GD->m_mouseButtons.leftButton == Mouse::ButtonStateTracker::PRESSED)
	{
		differenceX = m_pos.x - _GD->m_MS.x;
		differenceY = m_pos.y - _GD->m_MS.y;

		dragged = true;
	}

	if (dragged == true)
	{
		m_pos.x = _GD->m_MS.x + differenceX;
		m_pos.y = _GD->m_MS.y + differenceY;
	}

	if (dragged == true && _GD->m_mouseButtons.leftButton == Mouse::ButtonStateTracker::RELEASED)
	{
		dragged = false;
	}
}

void BaseAnimateWindow::SetBounds(float width, float height)
{
	bounds.width = width;
	bounds.height = height;
}

void BaseAnimateWindow::SetBounds(Vector2 new_bounds)
{
	bounds.width = new_bounds.x;
	bounds.height = new_bounds.y;
}

void BaseAnimateWindow::UpdateCloseButton()
{

	if (w_components.size() > 0)
	{
		GameObject2D& close_button_ref = *w_components[w_components.size()];
		close_button_ref.SetOffset(20000, 0);
	}
}



void BaseAnimateWindow::Tick(GameData* _GD)
{
	//bounds.x = m_pos.x - (bounds.width / 2);
	//bounds.y = m_pos.y - (bounds.height / 2);

	//int mouseX = _GD->m_MS.x;
	//int mouseY = _GD->m_MS.y;
	//Vector2 mousepos{ (float)mouseX,(float)mouseY };

	//if (renderable && bounds.Contains(Vector2{ (float)_GD->m_MS.x,(float)_GD->m_MS.y }) && _GD->m_mouseButtons.leftButton == Mouse::ButtonStateTracker::PRESSED)
	//{
	//	differenceX = m_pos.x - _GD->m_MS.x;
	//	differenceY = m_pos.y - _GD->m_MS.y;

	//	dragged = true;
	//}

	//if (dragged == true && _GD->m_MS.leftButton == 1)
	//{
	//	m_pos.x = _GD->m_MS.x + differenceX;
	//	m_pos.y = _GD->m_MS.y + differenceY;

	//	windowname->SetPos(m_pos.x + windowname->differenceX, m_pos.y + windowname->differenceY);
	//}

	//if (dragged == true && _GD->m_mouseButtons.leftButton == Mouse::ButtonStateTracker::RELEASED)
	//{
	//	dragged = false;
	//}

	//UpdateCloseButton();
}





void BaseAnimateWindow::Draw(DrawData2D* _DD)
{
	if (renderable)
	{
		_DD->m_Sprites->Draw(m_pTextureRV, m_pos, nullptr, m_colour, m_rotation, m_origin, m_scale, SpriteEffects_None);
	}


}