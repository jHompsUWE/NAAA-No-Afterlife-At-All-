#include "pch.h"
#include "OptionBarButton.h"
#include "DDSTextureLoader.h"
#include "DrawData2D.h"
#include "GameData.h"

OptionBarButton::OptionBarButton(ID3D11Device* _GD, float xi, string text)
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

	SetPos(Vector2(60 * xi,5));

	buttonText = new TextGO2D(text);
	buttonText->SetScale(Vector2(0.5, 0.5));
	
	bounds = { (long)m_origin.x,(long)m_origin.y,(long)(Desc.Width * m_scale.x), (long)(Desc.Height * m_scale.y) };
	
	buttonText->SetPos(GetPos().x - bounds.width/2, GetPos().y - bounds.height/4);
	buttonText->SetColour(Colors::Black);
}

OptionBarButton::~OptionBarButton()
{

}

void OptionBarButton::Tick(GameData* _GD)
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
			pressed = true;
		}
	}

	if (bounds.Contains(Vector2{ (float)_GD->m_MS.x,(float)_GD->m_MS.y }) && hover == false)
	{
		SetHover(true);
	}

	if (hover && !(bounds.Contains(Vector2{ (float)_GD->m_MS.x,(float)_GD->m_MS.y })))
	{
		SetHover(false);
	}
}

void OptionBarButton::Draw(DrawData2D* _DD)
{
	_DD->m_Sprites->Draw(m_pTextureRV, m_pos, nullptr, m_colour, m_rotation, m_origin, m_scale, SpriteEffects_None);
	buttonText->Draw(_DD);
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

void OptionBarButton::setToggle(Window* _toggle)
{
	toggle = _toggle;
}

void OptionBarButton::Toggle()
{
	toggle->renderable = !toggle->renderable;
}


