#include "pch.h"
#include "UIRemote.h"
#include "DDSTextureLoader.h"
#include "DrawData2D.h"
#include "GameData.h"
#include "helper.h"
#include <iostream>
#include "Mouse.h"

UIRemote::UIRemote(string _fileName, ID3D11Device* _GD, Window* toggle) :m_pTextureRV(nullptr)
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
		SetScale(Vector2{35,100});
		m_colour = Colors::DarkGoldenrod;
	}

	bounds = { (long)m_origin.x,(long)m_origin.y,(long)(Desc.Width * m_scale.x), (long)(Desc.Height * m_scale.y) };

	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			buttons[y * 4 + x] = new Button{ _fileName, _GD, this, toggle };
			buttons[y * 4 + x]->SetPos(x * 28, y * 27);
		}
		
	}

	buttons[20] = new Button{ _fileName, _GD, this, toggle };
	buttons[20]->SetScale(Vector2(6, 3));
	buttons[20]->SetPos(17, 4.8 * 27);
	buttons[20]->SetBounds();

	buttons[21] = new Button{ _fileName, _GD, this, toggle };
	buttons[21]->SetScale(Vector2(3.5, 6));
	buttons[21]->SetPos(-5, 5.6 * 27);
	buttons[21]->SetBounds();

	buttons[22] = new Button{ _fileName, _GD, this, toggle };
	buttons[22]->SetScale(Vector2(6, 3));
	buttons[22]->SetPos(17, 6.38 * 27);
	buttons[22]->SetBounds();

	buttons[23] = new Button{ _fileName, _GD, this, toggle };
	buttons[23]->SetScale(Vector2(3.5, 6));
	buttons[23]->SetPos(39, 5.6 * 27);
	buttons[23]->SetBounds();

	buttons[24] = new Button{ _fileName, _GD, this, toggle };
	buttons[24]->SetScale(Vector2(3.5, 8));
	buttons[24]->SetPos(60, 5.3 * 27);
	buttons[24]->SetBounds();

	buttons[25] = new Button{ _fileName, _GD, this, toggle };
	buttons[25]->SetScale(Vector2(3.5, 8));
	buttons[25]->SetPos(80, 5.9 * 27);
	buttons[25]->SetBounds();

	buttons[26] = new Button{ _fileName, _GD, this, toggle };
	buttons[26]->SetPos(17, 5.6 * 27);

	for (int x = 0; x < 4; x++)
	{
		buttons[x + 27] = new Button{ _fileName, _GD, this, toggle };
		buttons[x + 27]->SetPos(x * 28, 7.2 * 27);
	}

	buttons[31] = new Button{ _fileName, _GD, this, toggle };
	buttons[31]->SetScale(Vector2(18,12));
	buttons[31]->SetPos(17, 8.6 * 27);
	buttons[31]->SetBounds();

	buttons[32] = new Button{ _fileName, _GD, this, toggle };
	buttons[32]->SetScale(Vector2(12, 12));
	buttons[32]->SetPos(79, 8.6 * 27);
	buttons[32]->SetBounds();

	for (int x = 0; x < 4; x++)
	{
		buttons[x + 33] = new Button{ _fileName, _GD, this, toggle };
		buttons[x + 33]->SetPos(x * 28, 10 * 27);
	}


}

UIRemote::~UIRemote()
{
	if (m_pTextureRV)
	{
		m_pTextureRV->Release();
		m_pTextureRV = nullptr;
	}
}

void UIRemote::SetButtonPos()
{
	for (int x = 0; x < 37; x++)
	{
		if (buttons[x] != nullptr)
		{
			buttons[x]->SetPos(buttons[x]->GetPos().x + m_pos.x - (bounds.width / 3.3), buttons[x]->GetPos().y + m_pos.y - (bounds.height / 3));
			buttons[x]->differenceX = buttons[x]->GetPos().x - m_pos.x;
			buttons[x]->differenceY = buttons[x]->GetPos().y - m_pos.y;
		}
	}
}

void UIRemote::Tick(GameData* _GD)
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

		for (int x = 0; x < 37; x++)
		{
			if (buttons[x] != nullptr)
			{
				buttons[x]->SetPos(m_pos.x + buttons[x]->differenceX, m_pos.y + buttons[x]->differenceY);
			}
		}
	}

	if (dragged == true && _GD->m_mouseButtons.leftButton == Mouse::ButtonStateTracker::RELEASED)
	{
		dragged = false;
	}

	for (int i = 0; i < 37; i++)
	{
		if (buttons[i] != nullptr)
		{
			buttons[i]->Tick(_GD);
		}
	}
}



void UIRemote::Draw(DrawData2D* _DD)
{
	//nullptr can be changed to a RECT* to define what area of this image to grab
	//you can also add an extra value at the end to define layer depth
	//right click and "Go to Defintion/Declaration" to see other version of this in DXTK

	if (renderable)
	{
		_DD->m_Sprites->Draw(m_pTextureRV, m_pos, nullptr, m_colour, m_rotation, m_origin, m_scale, SpriteEffects_None);
	}

	for (int i = 0; i < 37; i++)
	{
		if (buttons[i] != nullptr)
		{
			buttons[i]->Draw(_DD);
		}
	}
}