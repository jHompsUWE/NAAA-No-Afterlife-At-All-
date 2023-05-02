#include "pch.h"
#include "OptionBarButton.h"
#include "DDSTextureLoader.h"
#include "DrawData2D.h"
#include "GameData.h"

OptionBarButton::OptionBarButton(ID3D11Device* _GD, Vector2 pos, string text)
{
	CreateDDSTextureFromFile(_GD, L"../Assets/white.dds", nullptr, &m_pTextureRV);

	//this nasty thing is required to find out the size of this image!
	ID3D11Resource* pResource;
	D3D11_TEXTURE2D_DESC Desc;
	m_pTextureRV->GetResource(&pResource);
	((ID3D11Texture2D*)pResource)->GetDesc(&Desc);

	m_origin = 0.5f * Vector2((float)Desc.Width, (float)Desc.Height);//around which rotation and scaing is done

	SetScale(Vector2(20, 10));
	m_colour = Colors::LightGoldenrodYellow;

	SetPos(Vector2(pos));

	buttonText = new TextGO2D(text);
	buttonText->SetScale(Vector2(0.5, 0.5));
	
	bounds = { (long)m_origin.x,(long)m_origin.y,(long)(Desc.Width * m_scale.x), (long)(Desc.Height * m_scale.y) };
	
	buttonText->SetPos(GetPos().x - bounds.width/2, GetPos().y);
	buttonText->SetColour(Colors::Black);
}

OptionBarButton::~OptionBarButton()
{

}

void OptionBarButton::Tick(GameData* _GD)
{
	
}

void OptionBarButton::Draw(DrawData2D* _DD)
{
	_DD->m_Sprites->Draw(m_pTextureRV, m_pos, nullptr, m_colour, m_rotation, m_origin, m_scale, SpriteEffects_None);
	buttonText->Draw(_DD);
}

void OptionBarButton::onEvent(const Event& event)
{
	switch (event.type)
	{
	case EventType::CURSOR_MOVED:
		{
			bounds.x = m_pos.x - (bounds.width / 2);
			bounds.y = m_pos.y - (bounds.height / 2);

			int mouseX = event.payload.cursor_data.x;
			int mouseY = event.payload.cursor_data.y;
			Vector2 mousepos{ (float)mouseX,(float)mouseY };

			if (bounds.Contains(mousepos))
			{
				if (!hover)
				{
					SetHover(true);
				}
			}
			if (hover && !(bounds.Contains(mousepos)))
			{
				SetHover(false);
			}
			break;
		}
	case EventType::CURSOR_SELECTED:
		{
			bounds.x = m_pos.x - (bounds.width / 2);
			bounds.y = m_pos.y - (bounds.height / 2);

			int mouseX = event.payload.cursor_data.x;
			int mouseY = event.payload.cursor_data.y;
			Vector2 mousepos{ (float)mouseX,(float)mouseY };

			if (bounds.Contains(mousepos))
			{
				if (event.payload.cursor_data.selected)
				{
					pressed = true;
				}
			}
			break;
		}
	default: ;
	}
}


void OptionBarButton::SetHover(bool hoveredOver)
{
	if (hoveredOver)
	{
		hover = true;
		SetColour(Colors::Yellow);
	}
	else
	{
		hover = false;
		SetColour(Colors::LightGoldenrodYellow);
	}
}

void OptionBarButton::setText(string _string)
{
	buttonText->SetString(_string);
}

void OptionBarButton::centreText()
{
	buttonText->SetPos(GetPos().x - bounds.width / 2, GetPos().y - bounds.height / 4);
}

void OptionBarButton::setToggle(Window* _toggle)
{
	toggle = _toggle;
}

void OptionBarButton::Toggle(bool toggleOn)
{
	if (toggleOn)
	{
		toggle->renderable = true;
	}
	else
	{
		toggle->renderable = false;
	}
}


