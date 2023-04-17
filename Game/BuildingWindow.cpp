#include "pch.h"
#include "BuildingWindow.h"
#include "DDSTextureLoader.h"
#include "DrawData2D.h"
#include "GameData.h"


BuildingWindow::BuildingWindow(ID3D11Device* _GD, int buttonNum)
{


	CreateDDSTextureFromFile(_GD, L"../Assets/white.dds", nullptr, &m_pTextureRV);


	//this nasty thing is required to find out the size of this image!
	ID3D11Resource* pResource;
	D3D11_TEXTURE2D_DESC Desc;
	m_pTextureRV->GetResource(&pResource);
	((ID3D11Texture2D*)pResource)->GetDesc(&Desc);

	m_origin = 0.5f * Vector2((float)Desc.Width, (float)Desc.Height);//around which rotation and scaing is done



	m_scale = Vector2{ 20 * float(buttonNum), 20 };
	m_colour = Colors::MediumPurple;

	bounds = { (long)m_origin.x,(long)m_origin.y,(long)(Desc.Width * m_scale.x), (long)(Desc.Height * m_scale.y) };

	renderable = false;

	/*for (int i = 0; i < buttonNum; i++)
	{
		buttons.push_back(new BuildingButton{ _GD, this, std::to_string(i) });
		buttons[i]->SetScale(Vector2(18, 18));
	}*/
}

BuildingWindow::~BuildingWindow()
{
	if (m_pTextureRV)
	{
		m_pTextureRV->Release();
		m_pTextureRV = nullptr;
	}
}


///// <summary>
///// Sets the size and position of buttons, then sets their bounds 
///// to check if clicked, and save their relative position to the window
///// </summary>
//void BuildingWindow::SetButtonBounds()
//{
//	for (int i = 0; i < buttons.size(); i++)
//	{
//		int j = 0;
//		if (buttons.size() == 3)
//		{
//			j = (this->m_pos.x - this->bounds.width / 3) + (i * 80);
//		}
//		else if (buttons.size() == 4)
//		{
//			j = (this->m_pos.x - this->bounds.width / 2.65) + (i * 80);
//		}
//		else
//		{
//			j = (this->m_pos.x - this->bounds.width / 2.5) + (i * 80);
//		}
//
//	}		buttons[i]->SetBounds();
//
//buttons[i]->bounds.height = 1000;
//	}
//}

/// <summary>
/// Checks for mouse position to see which button is hovered over, and if mouse is pressed- 
/// send off event and hide window
/// </summary>
/// <param name="_GD"></param>
//void BuildingWindow::Tick(GameData* _GD)
//{
//	bounds.x = m_pos.x - (bounds.width / 2);
//	bounds.y = m_pos.y - (bounds.height / 2);
//
//	int mouseX = _GD->m_MS.x;
//	int mouseY = _GD->m_MS.y;
//	Vector2 mousepos{ (float)mouseX,(float)mouseY };
//
//	if (renderable)
//	{
//		for (int i = 0; i < buttons.size(); i++)
//		{
//			buttons[i]->Tick(_GD);
//
//			if (buttons[i]->hover)
//			{
//				if (hovered != buttons[i] && hovered != nullptr)
//				{
//					hovered->SetHover(false);
//				}
//
//				hovered = buttons[i];
//			}
//		}
//	}
//
//	if (renderable && hovered != nullptr && _GD->m_mouseButtons.leftButton == Mouse::ButtonStateTracker::PRESSED)
//	{
//		Event event{};
//		event.type = hovered->event_type;
//
//		renderable = false;
//		hovered->SetHover(false);
//
//		GameManager::get()->getEventManager()->triggerEvent(std::make_shared<Event>(event));
//	}
//}


/// <summary>
/// Renders window and buttons
/// </summary>
/// <param name="_DD"></param>
void BuildingWindow::Draw(DrawData2D* _DD)
{
	//nullptr can be changed to a RECT* to define what area of this image to grab
	//you can also add an extra value at the end to define layer depth
	//right click and "Go to Defintion/Declaration" to see other version of this in DXTK

	if (renderable)
	{
		_DD->m_Sprites->Draw(m_pTextureRV, m_pos, nullptr, m_colour, m_rotation, m_origin, m_scale, SpriteEffects_None);

		/*for (int i = 0; i < buttons.size(); i++)
		{
			buttons[i]->Draw(_DD);
		}*/
	}

}