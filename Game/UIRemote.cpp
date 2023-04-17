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

	// Zones, buildings and roads buttons
	int yDistancing = 27;
	int yOffset = 10;

	auto dataList = GameManager::get()->getFileManagerV2()->GetJson("remote_buttons");

	for (int i = 0; i < 37; i++)
	{
		buttons[i] = new Button(_GD, this);

		string name = string((*dataList)["name"][i]);
		buttons[i]->SetName(name);

		float scaleX = std::stof((*dataList)["scaleX"][i].get<std::string>());
		float scaleY = std::stof((*dataList)["scaleY"][i].get<std::string>());
		buttons[i]->SetScale(Vector2(scaleX,scaleY));

		float posX = std::stof((*dataList)["posX"][i].get<std::string>());
		float posY = std::stof((*dataList)["posY"][i].get<std::string>());
		buttons[i]->SetPos(Vector2(posX,posY));
	}

	// Setting buttons colours
	// Zone buttons
	buttons[0]->SetColour(Colors::Green);
	buttons[1]->SetColour(Colors::Yellow);
	buttons[2]->SetColour(Colors::Orange);
	buttons[3]->SetColour(Colors::SaddleBrown);
	buttons[4]->SetColour(Colors::Magenta);
	buttons[5]->SetColour(Colors::Red);
	buttons[6]->SetColour(Colors::MediumPurple);

	// Camera buttons
	buttons[20]->SetColour(Colors::DarkRed);
	buttons[21]->SetColour(Colors::DarkRed);
	buttons[22]->SetColour(Colors::DarkRed);
	buttons[23]->SetColour(Colors::DarkRed);
	buttons[26]->SetColour(Colors::Purple);

	InitButtonEvents();

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
/// Sets the names and event types of all buttons
/// </summary>
void UIRemote::InitButtonEvents()
{
	// Zones
	buttons[0]->SetType(EventType::GREEN_ZONING);
	buttons[1]->SetType(EventType::YELLOW_ZONING);
	buttons[2]->SetType(EventType::ORANGE_ZONING);
	buttons[3]->SetType(EventType::BROWN_ZONING);
	buttons[4]->SetType(EventType::PURPLE_ZONING);
	buttons[5]->SetType(EventType::RED_ZONING);
	buttons[6]->SetType(EventType::BLUE_ZONING);
	buttons[7]->SetType(EventType::GENERIC_ZONING);

	// Buildings and roads
	buttons[8]->SetType(EventType::GATES);
	buttons[9]->SetType(EventType::ROADS);
	buttons[10]->SetType(EventType::ACTIVATES_KARMA_STATION_ZONING);
	buttons[11]->SetType(EventType::KARMA_TRACK);
	buttons[12]->SetType(EventType::TOPIAS);
	buttons[13]->SetType(EventType::TRAINING_CENTRE);
	buttons[14]->SetType(EventType::PORTS);
	buttons[15]->SetType(EventType::SIPHONS_BANKS);
	buttons[16]->SetType(EventType::SPECIAL_BUILDINGS);
	buttons[17]->SetType(EventType::ACTIVATES_OMNIBULGE_LOVEDOME_ZONNIG);
	buttons[18]->SetType(EventType::ACTIVATES_LIMBO_ZONING);
	buttons[19]->SetType(EventType::NUKE_BUTTON);

	// Camera view
	buttons[20]->SetType(EventType::ROTATE_REALMS_UP);
	buttons[21]->SetType(EventType::ROTATE_REALMS_LEFT);
	buttons[22]->SetType(EventType::ROTATE_REALMS_DOWN);
	buttons[23]->SetType(EventType::ROTATE_REALMS_RIGHT);
	buttons[24]->SetType(EventType::ZOOM_IN);
	buttons[25]->SetType(EventType::ZOOM_OUT);

	// Window toggles
	buttons[26]->SetType(EventType::TOGGLE_PLANET_VIEW);
	buttons[27]->SetType(EventType::GRAPHVIEW);
	buttons[28]->SetType(EventType::SOUL_VIEW);
	buttons[29]->SetType(EventType::TOGGLE_MACROMANAGER);
	buttons[30]->SetType(EventType::TOGGLE_MAPVIEW);
	buttons[31]->SetType(EventType::TOGGLE_HELPERS);
	buttons[32]->SetType(EventType::MICROVIEW);

	// Flatten views
	buttons[33]->SetType(EventType::FLATTEN_HELL);
	buttons[34]->SetType(EventType::FLATTEN_HEAVEN);
	buttons[35]->SetType(EventType::FLATTEN_KARMA);
	buttons[36]->SetType(EventType::FLATTEN_GRID);
}


/// <summary>
/// Sets the position of buttons and text relative to the overall remote, and the difference to the remote's position. 
/// Needed for these elements to be dragged with the remote and stay at the same relative position, and for the buttons to be clickable
/// </summary>
void UIRemote::SetButtonBounds()
{
	for (int i = 0; i < 37; i++)
	{
		if (buttons[i] != nullptr)
		{
			buttons[i]->differenceX = buttons[i]->GetPos().x - m_pos.x;
			buttons[i]->differenceY = buttons[i]->GetPos().y - m_pos.y;
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

void UIRemote::SetButtonToggle(int i, GameObject2D* toggle)
{
	buttons[i]->SetToggle(toggle);
}


/// <summary>
/// Activates on event
/// </summary>
/// <param name="event"></param>
void UIRemote::onEvent(const Event& event)
{
	//Checks to see if event is the same as button type, if so, sets current selection string to event name
	for (int i = 0; i < 37; i++)
	{
		if (buttons[i]->event_type == event.type)
		{
			text[2]->SetString(buttons[i]->buttonName);
			buttons[i]->toggle();
			
			
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
	//Checks the object bounds and the cursor postion
	bounds.x = m_pos.x - (bounds.width / 2);
	bounds.y = m_pos.y - (bounds.height / 2);

	int mouseX = _GD->m_MS.x;
	int mouseY = _GD->m_MS.y;

	Vector2 mousepos{ (float)mouseX,(float)mouseY };

	//If mouse clicked while in object bounds - get difference between object and cursor position and start to drag
	if (renderable && bounds.Contains(Vector2{ (float)_GD->m_MS.x,(float)_GD->m_MS.y }) && _GD->m_mouseButtons.leftButton == Mouse::ButtonStateTracker::PRESSED)
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

		for (int i = 0; i < 37; i++)
		{
			if (buttons[i] != nullptr)
			{
				buttons[i]->SetPos(m_pos.x + buttons[i]->differenceX, m_pos.y + buttons[i]->differenceY);
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
	if (renderable)
	{
		for (int i = 0; i < 37; i++)
		{
			if (buttons[i] != nullptr)
			{
				buttons[i]->Tick(_GD);

				if (buttons[i]->pressed)
				{
					//Toggle the button window, and set the remote selection string to buton name
					text[2]->SetString(buttons[i]->buttonName);
					
					//Fire event of button event type, then set button's pressed value to false
					
					Event event{};
						event.type = buttons[i]->event_type;

						GameManager::get()->getEventManager()->triggerEvent(std::make_shared<Event>(event));

						buttons[i]->pressed = false;
					
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
	}

	//Change year and money strings for demonstrative purposes
	text[0]->SetString("Year: " + to_string(_GD->Year += 1));
	text[1]->SetString(to_string(money -= 1) + "$");
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


		for (int i = 0; i < 37; i++)
		{
			if (buttons[i] != nullptr)
			{
				buttons[i]->Draw(_DD);
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