#include "pch.h"
#include "UIRemote.h"
#include "DDSTextureLoader.h"
#include "DrawData2D.h"
#include "GameData.h"
#include "helper.h"
#include <iostream>
#include "Mouse.h"
#include "SoulManager.h"

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


	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			buttons[y * 4 + x] = new Button{_GD, this};
			buttons[y * 4 + x]->SetPos(x * 28, y * yDistancing + yOffset);
		}
	}

	// Camera view buttons
	buttons[20] = new Button{_GD, this};
	buttons[20]->SetScale(Vector2(6, 3));
	buttons[20]->SetPos(17, 4.8 * yDistancing + yOffset);
	buttons[20]->SetBounds();

	buttons[21] = new Button{_GD, this};
	buttons[21]->SetScale(Vector2(3.5, 6));
	buttons[21]->SetPos(-5, 5.6 * yDistancing + yOffset);
	buttons[21]->SetBounds();

	buttons[22] = new Button{_GD, this};
	buttons[22]->SetScale(Vector2(6, 3));
	buttons[22]->SetPos(17, 6.38 * yDistancing + yOffset);
	buttons[22]->SetBounds();

	buttons[23] = new Button{_GD, this};
	buttons[23]->SetScale(Vector2(3.5, 6));
	buttons[23]->SetPos(39, 5.6 * yDistancing + yOffset);
	buttons[23]->SetBounds();

	buttons[24] = new Button{_GD, this};
	buttons[24]->SetScale(Vector2(3.5, 8));
	buttons[24]->SetPos(60, 5.3 * yDistancing + yOffset);
	buttons[24]->SetBounds();

	buttons[25] = new Button{_GD, this};
	buttons[25]->SetScale(Vector2(3.5, 8));
	buttons[25]->SetPos(80, 5.9 * yDistancing + yOffset);
	buttons[25]->SetBounds();

	// Toggle planet view button
	buttons[26] = new Button{_GD, this};
	buttons[26]->SetPos(17, 5.6 * yDistancing + yOffset);

	// View toggle buttons
	for (int x = 0; x < 4; x++)
	{
		buttons[x + 27] = new Button{_GD, this};
		buttons[x + 27]->SetPos(x * 28, 7.2 * yDistancing + yOffset);
	}

	// Helpers and Microview buttons
	buttons[31] = new Button{_GD, this};
	buttons[31]->SetScale(Vector2(18,12));
	buttons[31]->SetPos(17, 8.6 * yDistancing + yOffset);
	buttons[31]->SetBounds();

	buttons[32] = new Button{_GD, this};
	buttons[32]->SetScale(Vector2(12, 12));
	buttons[32]->SetPos(79, 8.6 * yDistancing + yOffset);
	buttons[32]->SetBounds();

	// Flatten structures buttons
	for (int x = 0; x < 4; x++)
	{
		buttons[x + 33] = new Button{_GD, this};
		buttons[x + 33]->SetPos(x * 28, 10 * yDistancing + yOffset);
	}


	// Setting buttons names and colours
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

	InitButtonNames();

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

void UIRemote::InitButtonNames()
{
	// Zones
	buttons[0]->SetName("Envy/Content");
	buttons[0]->SetType(EventType::GREEN_ZONING);
	buttons[1]->SetName("Avarice/Charity");
	buttons[1]->SetType(EventType::YELLOW_ZONING);
	buttons[2]->SetName("Glut/Tempered");
	buttons[2]->SetType(EventType::ORANGE_ZONING);
	buttons[3]->SetName("Sloth/Diligence");
	buttons[3]->SetType(EventType::BROWN_ZONING);
	buttons[4]->SetName("Lust/Chastity");
	buttons[4]->SetType(EventType::PURPLE_ZONING);
	buttons[5]->SetName("Wrath/Peace");
	buttons[5]->SetType(EventType::RED_ZONING);
	buttons[6]->SetName("Pride/Humility");
	buttons[6]->SetType(EventType::BLUE_ZONING);
	buttons[7]->SetName("Generic Zone");
	buttons[7]->SetType(EventType::GENERIC_ZONING);

	// Buildings and roads
	buttons[8]->SetName("Gates");
	buttons[8]->SetType(EventType::GATES);
	buttons[8]->SetOpenBuildWindow(true);
	buttons[9]->SetName("Roads");
	buttons[9]->SetType(EventType::ROADS);
	buttons[10]->SetName("Karma Stations");
	buttons[10]->SetType(EventType::ACTIVATES_KARMA_STATION_ZONING);
	buttons[10]->SetOpenBuildWindow(true);
	buttons[11]->SetName("Karma Track");
	buttons[11]->SetType(EventType::KARMA_TRACK);
	buttons[12]->SetName("Topias");
	buttons[12]->SetType(EventType::TOPIAS);
	buttons[12]->SetOpenBuildWindow(true);
	buttons[13]->SetName("Training Centre");
	buttons[13]->SetType(EventType::TRAINING_CENTRE);
	buttons[13]->SetOpenBuildWindow(true);
	buttons[14]->SetName("Ports");
	buttons[14]->SetType(EventType::PORTS);
	buttons[14]->SetOpenBuildWindow(true);
	buttons[15]->SetName("Siphons/Banks");
	buttons[15]->SetType(EventType::SIPHONS_BANKS);
	buttons[15]->SetOpenBuildWindow(true);
	buttons[16]->SetName("Special");
	buttons[16]->SetType(EventType::SPECIAL_BUILDINGS);
	buttons[16]->SetOpenBuildWindow(true);
	buttons[17]->SetName("Omnibolges");
	buttons[17]->SetType(EventType::ACTIVATES_OMNIBULGE_LOVEDOME_ZONNIG);
	buttons[17]->SetOpenBuildWindow(true);
	buttons[18]->SetName("Limbo Buildings");
	buttons[18]->SetType(EventType::ACTIVATES_LIMBO_ZONING);
	buttons[18]->SetOpenBuildWindow(true);
	buttons[19]->SetName("Zap");
	buttons[19]->SetType(EventType::NUKE_BUTTON);

	// Camera view
	buttons[20]->SetName("View Up");
	buttons[20]->SetType(EventType::ROTATE_REALMS_UP);
	buttons[21]->SetName("View Left");
	buttons[21]->SetType(EventType::ROTATE_REALMS_LEFT);
	buttons[22]->SetName("View Down");
	buttons[22]->SetType(EventType::ROTATE_REALMS_DOWN);
	buttons[23]->SetName("View Right");
	buttons[23]->SetType(EventType::ROTATE_REALMS_RIGHT);
	buttons[24]->SetName("Zoom In");
	buttons[24]->SetType(EventType::ZOOM_IN);
	buttons[25]->SetName("Zoom Out");
	buttons[25]->SetType(EventType::ZOOM_OUT);

	// Window toggles
	buttons[26]->SetName("Planet View");
	buttons[26]->SetType(EventType::TOGGLE_PLANET_VIEW);
	buttons[27]->SetName("Graphview");
	buttons[27]->SetType(EventType::GRAPHVIEW);
	buttons[28]->SetName("Soulview");
	buttons[28]->SetType(EventType::SOUL_VIEW);
	buttons[29]->SetName("Macro Manager");
	buttons[29]->SetType(EventType::TOGGLE_MACROMANAGER);
	buttons[30]->SetName("Mapview");
	buttons[30]->SetType(EventType::TOGGLE_MAPVIEW);
	buttons[31]->SetName("Advisors");
	buttons[31]->SetType(EventType::TOGGLE_HELPERS);
	buttons[32]->SetName("Microview");
	buttons[32]->SetType(EventType::MICROVIEW);

	// Flatten views
	buttons[33]->SetName("Flatten Hell");
	buttons[33]->SetType(EventType::FLATTEN_HELL);
	buttons[34]->SetName("Flatten Heaven");
	buttons[34]->SetType(EventType::FLATTEN_HEAVEN);
	buttons[35]->SetName("Flatten Karma");
	buttons[35]->SetType(EventType::FLATTEN_KARMA);
	buttons[36]->SetName("Flatten Grid");
	buttons[36]->SetType(EventType::FLATTEN_GRID);
}

void UIRemote::SetButtonBounds()
{
	for (int i = 0; i < 37; i++)
	{
		if (buttons[i] != nullptr)
		{
			buttons[i]->SetPos(buttons[i]->GetPos().x + m_pos.x - (bounds.width / 3.3), buttons[i]->GetPos().y + m_pos.y - (bounds.height / 3));
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

void UIRemote::SetButtonToggle(int i, BuildingWindow* toggle)
{
	buttons[i]->SetToggle(toggle);
}

void UIRemote::onEvent(const Event& event)
{
	for (int i = 0; i < 37; i++)
	{
		if (buttons[i]->event_type == event.type)
		{
			text[2]->SetString(buttons[i]->buttonName);

			if (!buttons[i]->openBuildingWindow)
			{
				buttons[i]->toggle();
			}
			
			break;
		}
	}

	switch (event.type)
	{
		case EventType::SOUL_UPDATE:
		{
			text[4]->SetString("SOULs: " + std::to_string(event.payload.soul_update.count));
			break;
		}
		case EventType::TOGGLE_REMOTE_CONTROL:
		{
			renderable = !renderable;
			break;
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

	if (dragged == true && _GD->m_mouseButtons.leftButton == Mouse::ButtonStateTracker::RELEASED)
	{
		dragged = false;
	}

	if (renderable)
	{
		for (int i = 0; i < 37; i++)
		{
			if (buttons[i] != nullptr)
			{
				buttons[i]->Tick(_GD);

				if (buttons[i]->pressed)
				{
					buttons[i]->toggle();
					text[2]->SetString(buttons[i]->buttonName);
					
					if (!buttons[i]->openBuildingWindow)
					{

						Event event{};
						event.type = buttons[i]->event_type;

						GameManager::get()->getEventManager()->triggerEvent(std::make_shared<Event>(event));

						buttons[i]->pressed = false;
					}
					else
					{
						for (int j = 0; j < buttons[i]->toggleBuildWindow->buttons.size(); j++)
						{
							buttons[i]->toggleBuildWindow->buttons[j]->SetText(true, buttons[i]->buttonName);
							buttons[i]->toggleBuildWindow->buttons[j]->SetType(buttons[i]->event_type);
						}

						buttons[i]->pressed = false;
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
	}

	text[0]->SetString("Year: " + to_string(_GD->Year += 1));
	text[1]->SetString(to_string(money -= 1) + "$");
}



void UIRemote::Draw(DrawData2D* _DD)
{
	//nullptr can be changed to a RECT* to define what area of this image to grab
	//you can also add an extra value at the end to define layer depth
	//right click and "Go to Defintion/Declaration" to see other version of this in DXTK

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