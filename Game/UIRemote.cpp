#include "pch.h"
#include "UIRemote.h"
#include "DDSTextureLoader.h"
#include "DrawData2D.h"
#include "GameData.h"
#include "helper.h"
#include <iostream>
#include "Mouse.h"
#include "SoulManager.h"
#include "GameManager.h"

UIRemote::UIRemote(ID3D11Device* _GD) :m_pTextureRV(nullptr)
{
	CreateDDSTextureFromFile(_GD, L"../Assets/white.dds", nullptr, &m_pTextureRV);

	//this nasty thing is required to find out the size of this image!
	ID3D11Resource* pResource;
	D3D11_TEXTURE2D_DESC Desc;
	m_pTextureRV->GetResource(&pResource);
	((ID3D11Texture2D*)pResource)->GetDesc(&Desc);

	m_origin = 0.5f * Vector2((float)Desc.Width, (float)Desc.Height);//around which rotation and scaing is done

	SetScale(Vector2{35,110});
	m_colour = Colors::DarkGoldenrod;

	bounds = { (long)m_origin.x,(long)m_origin.y,(long)(Desc.Width * m_scale.x), (long)(Desc.Height * m_scale.y) };

	//////////////
	//INIT BUTTONS
	//////////////

	auto dataList = GameManager::get()->getFileManagerV2()->GetJson("remote_buttons");

	int i = 0;
	for (auto json_buttons : (*dataList)["Buttons"])
	{
		string name = string(json_buttons["Name"]);
		Vector2 scale = Vector2((json_buttons["Scale"]["X"]), (json_buttons["Scale"]["Y"]));
		Vector2 pos = Vector2((json_buttons["Position"]["X"]), (json_buttons["Position"]["Y"] + 40));
		EventType eventT = string_to_event.at(string(json_buttons["Event"]));

		Direction direction = Direction::NONE;
		{
			if (eventT == EventType::SCROLL_VIEW)
			{
				string_to_direction.at(string(json_buttons["Direction"]));
			}
		}
		
		buttonsSwitch[i] = new Button(_GD, this, name, scale, pos, eventT, direction);

		i += 1;
	}

	int j = 0;
	for (auto json_buttons : (*dataList)["BuildingButtons"])
	{
		string name = string(json_buttons["Name"]);
		Vector2 scale = Vector2((json_buttons["Scale"]["X"]), (json_buttons["Scale"]["Y"]));
		Vector2 pos = Vector2((json_buttons["Position"]["X"]), (json_buttons["Position"]["Y"] + 40));
		EventType eventT = string_to_event.at(string(json_buttons["Event"]));

		buttonsBuilding[j] = new ButtonOpenBW(_GD, this, name, scale, pos, eventT);

		j += 1;
	}

	int k = 0;
	for (auto json_buttons : (*dataList)["WindowButtons"])
	{
		string name = string(json_buttons["Name"]);
		Vector2 scale = Vector2((json_buttons["Scale"]["X"]), (json_buttons["Scale"]["Y"]));
		Vector2 pos = Vector2((json_buttons["Position"]["X"]), (json_buttons["Position"]["Y"] + 40));
		EventType eventT = string_to_event.at(string(json_buttons["Event"]));

		buttonsWindow[k] = new ButtonToggleWindow(_GD, this, name, scale, pos, eventT);

		k += 1;
	}


	// Setting buttons colours
	// Zone buttons
	/*buttons[0]->SetColour(Colors::Green);
	buttons[1]->SetColour(Colors::Yellow);
	buttons[2]->SetColour(Colors::Orange);
	buttons[3]->SetColour(Colors::SaddleBrown);
	buttons[4]->SetColour(Colors::Magenta);
	buttons[5]->SetColour(Colors::Red);
	buttons[6]->SetColour(Colors::MediumPurple);*/

	// Camera buttons
	/*buttons[20]->SetColour(Colors::DarkRed);
	buttons[21]->SetColour(Colors::DarkRed);
	buttons[22]->SetColour(Colors::DarkRed);
	buttons[23]->SetColour(Colors::DarkRed);
	buttons[26]->SetColour(Colors::Purple);*/

	//InitButtonEvents();

	////////////
	// INIT TEXT
	////////////

	for (int y = 0; y < 4; y++)
	{
		text[y] = new TextGO2D("0");
		text[y]->SetScale(0.43f);
		text[y]->SetPos(-20, (y * 16) - 75);
	}

	text[0]->SetString("Year: 0");
	text[1]->SetString("999,999,999$");
	text[2]->SetString("Selection: ");
	text[3]->SetString("Cost: 0 $");

	for (int y = 4; y < 8; y++)
	{
		text[y] = new TextGO2D("0");
		text[y]->SetScale(0.43f);
		text[y]->SetPos(-20, (y * 16) + 228);
	}

	text[4]->SetString("SOULs: 0");
	text[5]->SetString("Lost: 0");
	text[6]->SetString("EMBOs: 5000");
	text[7]->SetString("0.10$ per SOUL");
}

UIRemote::~UIRemote()
{
	if (m_pTextureRV)
	{
		m_pTextureRV->Release();
		m_pTextureRV = nullptr;
	}
}

/// <summary>
/// Sets the position of buttons and text relative to the overall remote, and the difference to the remote's position. 
/// Needed for these elements to be dragged with the remote and stay at the same relative position, and for the buttons to be clickable
/// </summary>
void UIRemote::SetButtonBounds()
{
	for (int i = 0; i < buttonsSwitch.size(); i++)
	{
		if (buttonsSwitch[i] != nullptr)
		{
			buttonsSwitch[i]->differenceX = buttonsSwitch[i]->GetPos().x - m_pos.x;
			buttonsSwitch[i]->differenceY = buttonsSwitch[i]->GetPos().y - m_pos.y;
		}
	}

	for (int i = 0; i < buttonsBuilding.size(); i++)
	{
		if (buttonsBuilding[i] != nullptr)
		{
			buttonsBuilding[i]->differenceX = buttonsBuilding[i]->GetPos().x - m_pos.x;
			buttonsBuilding[i]->differenceY = buttonsBuilding[i]->GetPos().y - m_pos.y;
		}
	}

	for (int i = 0; i < buttonsWindow.size(); i++)
	{
		if (buttonsWindow[i] != nullptr)
		{
			buttonsWindow[i]->differenceX = buttonsWindow[i]->GetPos().x - m_pos.x;
			buttonsWindow[i]->differenceY = buttonsWindow[i]->GetPos().y - m_pos.y;
		}
	}

	for (int i = 0; i < 8; i++)
	{
		if (text[i] != nullptr)
		{
			text[i]->SetPos(text[i]->GetPos().x + m_pos.x - (bounds.width / 3.3), text[i]->GetPos().y + m_pos.y - (bounds.height / 3));
			text[i]->differenceX = text[i]->GetPos().x - m_pos.x;
			text[i]->differenceY = text[i]->GetPos().y - m_pos.y;
		}
	}
}

void UIRemote::SetButtonToggle(int i, Window* toggle)
{
	buttonsWindow[i]->SetToggle(toggle);
}

void UIRemote::SetButtonToggle(int i, BuildingWindow* toggle)
{
	buttonsBuilding[i]->SetToggle(toggle);
}

/// <summary>
/// Activates on event
/// </summary>
/// <param name="event"></param>
void UIRemote::onEvent(const Event& event)
{
	//Checks to see if event is the same as button type, if so, sets current selection string to event name
	for (int i = 0; i < buttonsSwitch.size(); i++)
	{
		if (buttonsSwitch[i]->event_type == event.type)
		{
			text[2]->SetString(buttonsSwitch[i]->buttonName);
			break;
		}
	}

	for (int i = 0; i < buttonsWindow.size(); i++)
	{
		if (buttonsWindow[i]->event_type == event.type)
		{
			text[2]->SetString(buttonsWindow[i]->buttonName);
			buttonsWindow[i]->Toggle();
			break;
		}
	}

	//Switch case to check other events
	switch (event.type)
	{
		//Updates SOUL count string
		case EventType::SOUL_UPDATE:
		{
			text[4]->SetString("SOULs: " + std::to_string(event.payload.soul_update.count));
			break;
		}
		//Toggles the renderable value of the remote
		case EventType::TOGGLE_REMOTE_CONTROL:
		{
			renderable = !renderable;
			break;
		}
	}
}

/// <summary>
/// Checks mouse state to see if remote being dragged, or buttons being pushed
/// </summary>
/// <param name="_GD"></param>
void UIRemote::Tick(GameData* _GD)
{
	if (renderable)
	{
		if (!buildingWindowOpen)
		{
		//Checks the object bounds and the cursor postion
		bounds.x = m_pos.x - (bounds.width / 2);
		bounds.y = m_pos.y - (bounds.height / 2);

		int mouseX = _GD->m_MS.x;
		int mouseY = _GD->m_MS.y;

		Vector2 mousepos{ (float)mouseX,(float)mouseY };


		//If mouse clicked while in object bounds - get difference between object and cursor position and start to drag
		if (bounds.Contains(Vector2{ (float)_GD->m_MS.x,(float)_GD->m_MS.y }) && _GD->m_mouseButtons.leftButton == Mouse::ButtonStateTracker::PRESSED)
		{
			differenceX = m_pos.x - _GD->m_MS.x;
			differenceY = m_pos.y - _GD->m_MS.y;

			dragged = true;
		}

		//If being dragged, move with mouse using the distance value to stay relative
		if (dragged == true && _GD->m_MS.leftButton == 1)
		{
			m_pos.x = _GD->m_MS.x + differenceX;
			m_pos.y = _GD->m_MS.y + differenceY;

			for (int i = 0; i < buttonsSwitch.size(); i++)
			{
				if (buttonsSwitch[i] != nullptr)
				{
					buttonsSwitch[i]->SetPos(m_pos.x + buttonsSwitch[i]->differenceX, m_pos.y + buttonsSwitch[i]->differenceY);
				}
			}

			for (int i = 0; i < buttonsBuilding.size(); i++)
			{
				if (buttonsBuilding[i] != nullptr)
				{
					buttonsBuilding[i]->SetPos(m_pos.x + buttonsBuilding[i]->differenceX, m_pos.y + buttonsBuilding[i]->differenceY);
				}
			}

			for (int i = 0; i < buttonsWindow.size(); i++)
			{
				if (buttonsWindow[i] != nullptr)
				{
					buttonsWindow[i]->SetPos(m_pos.x + buttonsWindow[i]->differenceX, m_pos.y + buttonsWindow[i]->differenceY);
				}
			}

			for (int i = 0; i < 8; i++)
			{
				if (text[i] != nullptr)
				{
					text[i]->SetPos(m_pos.x + text[i]->differenceX, m_pos.y + text[i]->differenceY);
				}
			}
		}

		//If being dragged and button is released - stop
		if (dragged == true && _GD->m_mouseButtons.leftButton == Mouse::ButtonStateTracker::RELEASED)
		{
			dragged = false;
		}

		// Check to see if buttons are pressed

		for (int i = 0; i < buttonsSwitch.size(); i++)
		{
			if (buttonsSwitch[i] != nullptr)
			{
				buttonsSwitch[i]->Tick(_GD);

				if (buttonsSwitch[i]->pressed)
				{
					//Fire event of button event type, then set button's pressed value to false
					Event event{};
					event.type = buttonsSwitch[i]->event_type;

					GameManager::get()->getEventManager()->triggerEvent(std::make_shared<Event>(event));

					buttonsSwitch[i]->pressed = false;
				}
			}
		}

		for (int i = 0; i < buttonsBuilding.size(); i++)
		{
			if (buttonsBuilding[i] != nullptr)
			{
				buttonsBuilding[i]->Tick(_GD);

				if (buttonsBuilding[i]->pressed)
				{
					//Fire event of button event type, then set button's pressed value to false

					text[2]->SetString(buttonsBuilding[i]->buttonName);

					for (int j = 0; j < buttonsBuilding[i]->GetToggle()->buttons.size(); j++)
					{
						buttonsBuilding[i]->GetToggle()->SetPosition(buttonsBuilding[i]->GetPos());
						buttonsBuilding[i]->GetToggle()->buttons[j]->SetText(true, buttonsBuilding[i]->buttonName);
						buttonsBuilding[i]->GetToggle()->buttons[j]->SetType(buttonsBuilding[i]->event_type);
					}

					buttonsBuilding[i]->toggle();
					buttonsBuilding[i]->pressed = false;
				}
			}
		}

		for (int i = 0; i < buttonsWindow.size(); i++)
		{
			if (buttonsWindow[i] != nullptr)
			{
				buttonsWindow[i]->Tick(_GD);

				if (buttonsWindow[i]->pressed)
				{
					//Fire event of button event type, then set button's pressed value to false
					Event event{};
					event.type = buttonsWindow[i]->event_type;
					if (buttonsWindow[i]->event_type == EventType::SCROLL_VIEW)
					{
						switch (buttonsWindow[i]->direction)
						{
							case Direction::LEFT:
								{
									event.payload.input_vector2_data.x = -1;
									break;
								}
							case Direction::RIGHT: 
								{
									event.payload.input_vector2_data.x = 1;
									break;
								}
							case Direction::UP: 
								{
									event.payload.input_vector2_data.y = -1;
									break;
								}
							case Direction::DOWN: 
								{
									event.payload.input_vector2_data.y = 1;
									break;
								}
							default: ;
						}
					}

					GameManager::get()->getEventManager()->triggerEvent(std::make_shared<Event>(event));

					buttonsWindow[i]->pressed = false;
				}
			}
		}
	}


		for (int i = 0; i < 8; i++)
		{
			if (text[i] != nullptr)
			{
				text[i]->Tick(_GD);
			}
		}

		//Change year and money strings for demonstrative purposes
		text[0]->SetString("Year: " + to_string(_GD->Year += 1));
		text[1]->SetString(to_string(money -= 1) + "$");
	}
}


/// <summary>
/// Render remote and its button and text arrays
/// </summary>
/// <param name="_DD"></param>
void UIRemote::Draw(DrawData2D* _DD)
{
	if (renderable)
	{
		_DD->m_Sprites->Draw(m_pTextureRV, m_pos, nullptr, m_colour, m_rotation, m_origin, m_scale, SpriteEffects_None);


		for (int i = 0; i < buttonsSwitch.size(); i++)
		{
			if (buttonsSwitch[i] != nullptr)
			{
				buttonsSwitch[i]->Draw(_DD);
			}
		}

		for (int i = 0; i < buttonsBuilding.size(); i++)
		{
			if (buttonsBuilding[i] != nullptr)
			{
				buttonsBuilding[i]->Draw(_DD);
			}
		}

		for (int i = 0; i < buttonsWindow.size(); i++)
		{
			if (buttonsWindow[i] != nullptr)
			{
				buttonsWindow[i]->Draw(_DD);
			}
		}

		for (int i = 0; i < 8; i++)
		{
			if (text[i] != nullptr)
			{
				text[i]->Draw(_DD);
			}
		}
	}
}