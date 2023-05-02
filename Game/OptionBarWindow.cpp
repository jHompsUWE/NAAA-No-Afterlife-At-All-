#include "pch.h"
#include "OptionBarWindow.h"
#include "DDSTextureLoader.h"
#include "DrawData2D.h"
#include "GameData.h"
#include "GameManager.h"


OptionBarWindow::OptionBarWindow(ID3D11Device* _GD, int buttonNum, Vector2 pos)
{
	CreateDDSTextureFromFile(_GD, L"../Assets/white.dds", nullptr, &m_pTextureRV);


	//this nasty thing is required to find out the size of this image!
	ID3D11Resource* pResource;
	D3D11_TEXTURE2D_DESC Desc;
	m_pTextureRV->GetResource(&pResource);
	((ID3D11Texture2D*)pResource)->GetDesc(&Desc);

	m_origin = 0.5f * Vector2((float)Desc.Width, (float)Desc.Height);//around which rotation and scaing is done

	m_scale = (Vector2(20,10*buttonNum));
	m_colour = Colors::LightGoldenrodYellow;

	bounds = { (long)m_origin.x,(long)m_origin.y,(long)(Desc.Width * m_scale.x), (long)(Desc.Height * m_scale.y) };

	SetPos(pos);

	for (int i = 0; i < buttonNum; i++)
	{
		buttons.emplace_back(new OptionBarButton(_GD, Vector2(GetPos().x, 50 + (20 * (i+1))), "Text"));
		buttons.back()->SetScale(Vector2(20, 5));
		//buttons.back()->SetPos(Vector2(GetPos().x - bounds.width / 2, GetPos().y - bounds.height / 2));
		buttons.back()->buttonText->SetScale(Vector2(0.4,0.4));
		buttons.back()->buttonText->SetPos(buttons.back()->GetPos().x - bounds.width / 2, buttons.back()->GetPos().y - bounds.height / (20 + i+1));
		buttons.back()->buttonText->SetColour(Colors::Black);
		buttons.back()->setToggle(this);
	}

	renderable = false;
}

OptionBarWindow::~OptionBarWindow()
{
	if (m_pTextureRV)
	{
		m_pTextureRV->Release();
		m_pTextureRV = nullptr;
	}
}

void OptionBarWindow::SetButtonText(int button, string text)
{
	buttons[button]->setText(text);
}

/// <summary>
/// Sets the size and position of buttons, then sets their bounds 
/// to check if clicked, and save their relative position to the window
/// </summary>
void OptionBarWindow::SetButtonBounds()
{

}


/// <summary>
/// Checks for mouse position to see which button is hovered over, and if mouse is pressed- 
/// send off event and hide window
/// </summary>
/// <param name="_GD"></param>
void OptionBarWindow::Tick(GameData* _GD)
{
	bounds.x = m_pos.x - (bounds.width / 2);
	bounds.y = m_pos.y - (bounds.height / 2);

	int mouseX = _GD->m_MS.x;
	int mouseY = _GD->m_MS.y;
	Vector2 mousepos{ (float)mouseX,(float)mouseY };

	if (renderable)
	{
		if (hovered != nullptr && hovered->pressed)
		{
			/*Event event{};
			event.type = hovered->event_type;*/

			hovered->Toggle(false);
			hovered->pressed = false;

			//GameManager::get()->getEventManager()->triggerEvent(std::make_shared<Event>(event));
		}

		for (int i = 0; i < buttons.size(); i++)
		{
			buttons[i]->Tick(_GD);

			if (buttons[i]->hover)
			{
				if (hovered != buttons[i] && hovered != nullptr)
				{
					hovered->SetHover(false);
				}

				hovered = buttons[i];
			}
		}
	}
}

/// <summary>
/// Renders window and buttons
/// </summary>
/// <param name="_DD"></param>
void OptionBarWindow::Draw(DrawData2D* _DD)
{
	//nullptr can be changed to a RECT* to define what area of this image to grab
	//you can also add an extra value at the end to define layer depth
	//right click and "Go to Defintion/Declaration" to see other version of this in DXTK
	if (renderable)
	{
		_DD->m_Sprites->Draw(m_pTextureRV, m_pos, nullptr, m_colour, m_rotation, m_origin, m_scale, SpriteEffects_None);

		for (int i = 0; i < buttons.size(); i++)
		{
			buttons[i]->Draw(_DD);
		}
	}

}

void OptionBarWindow::onEvent(const Event& event)
{
	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i]->onEvent(event);
	}
}

