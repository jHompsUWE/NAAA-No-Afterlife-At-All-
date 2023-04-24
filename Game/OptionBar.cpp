#include "pch.h"
#include "DDSTextureLoader.h"
#include "DrawData2D.h"
#include "GameData.h"
#include "OptionBar.h"
#include "GameManager.h"

OptionBar::OptionBar(ID3D11Device* _GD) :m_pTextureRV(nullptr)
{
	CreateDDSTextureFromFile(_GD, L"../Assets/white.dds", nullptr, &m_pTextureRV);

	//this nasty thing is required to find out the size of this image!
	ID3D11Resource* pResource;
	D3D11_TEXTURE2D_DESC Desc;
	m_pTextureRV->GetResource(&pResource);
	((ID3D11Texture2D*)pResource)->GetDesc(&Desc);

	m_origin = 0.5f * Vector2((float)Desc.Width, (float)Desc.Height);//around which rotation and scaing is done

	SetScale(Vector2(400, 10));
	m_colour = Colors::DarkGoldenrod;

	bounds = { (long)m_origin.x,(long)m_origin.y,(long)(Desc.Width * m_scale.x), (long)(Desc.Height * m_scale.y) };

	auto dataList = GameManager::get()->getFileManagerV2()->GetJson("option_buttons");

	//optionWindows.emplace_back(new OptionBarWindow(_GD, 1));

	int j = 0;
	for (auto window : (*dataList)["Windows"])
	{
		Vector2 position = Vector2(window["Position"]["X"], window["Position"]["Y"]);
		optionWindows.emplace_back(new OptionBarWindow(_GD, window["NumButtons"], position));


		int k = 0;
		for (auto button : window["ButtonText"])
		{
			optionWindows.back()->SetButtonText(k, string(button));
			k += 1;
		}


		/*for (int k = 0; k < window["NumButtons"]; k++)
		{
			optionWindows.back()->SetButtonText(k, string(window["ButtonText"][k]));
		}*/

		j += 1;
	}
	
	int i = 0;

	for (auto button : (*dataList)["Buttons"])
	{
		string name = string(button["Text"]);
		Vector2 position = Vector2(button["Position"]["X"], button["Position"]["Y"]);
		optionButtons[i] = new OptionBarButton(_GD, position, name);
		optionButtons[i]->setToggle(optionWindows[i]);
		optionButtons[i]->SetBounds();

		optionButtons[i]->centreText();

		i += 1;
	}

}

OptionBar::~OptionBar()
{

}

void OptionBar::Tick(GameData* _GD)
{
	
	for (int i = 0; i < optionButtons.size(); i++)
	{
		optionButtons[i]->Tick(_GD);

		if (optionButtons[i]->pressed)
		{
			optionButtons[i]->Toggle(true);
			optionButtons[i]->pressed = false;
		}

		if (optionButtons[i]->hover)
		{
			if (hovered != optionButtons[i] && hovered != nullptr)
			{
				hovered->SetHover(false);
			}

			hovered = optionButtons[i];
		}

		if (hovered != nullptr)
		{
			if (!hovered->hover)
			{
				hovered = nullptr;
			}
		}

		for (int i = 0; i < optionWindows.size(); i++)
		{
			optionWindows[i]->Tick(_GD);
		}
		
	}
}

void OptionBar::Draw(DrawData2D* _DD)
{
	_DD->m_Sprites->Draw(m_pTextureRV, m_pos, nullptr, m_colour, m_rotation, m_origin, m_scale, SpriteEffects_None);

	for (int i = 0; i < optionButtons.size(); i++)
	{
		optionButtons[i]->Draw(_DD);
	}

	for (int i = 0; i < optionWindows.size(); i++)
	{
		optionWindows[i]->Draw(_DD);
	}
}