#pragma once
#include "GameObject2D.h"
#include "Button.h"
#include "ButtonToggleWindow.h"
#include "ButtonOpenBW.h"
#include <array>
#include "Window.h"
#include "TextGO2D.h"
#include "Listener.h"
#include <unordered_map>

static const std::unordered_map<std::string, EventType> string_to_event =
{
	{"GREEN_ZONING", EventType::GREEN_ZONING},
	{"YELLOW_ZONING", EventType::YELLOW_ZONING},
	{"ORANGE_ZONING", EventType::ORANGE_ZONING},
	{"BROWN_ZONING", EventType::BROWN_ZONING},
	{"PURPLE_ZONING", EventType::PURPLE_ZONING},
	{"RED_ZONING", EventType::RED_ZONING},
	{"BLUE_ZONING", EventType::BLUE_ZONING},
	{"GENERIC_ZONING", EventType::GENERIC_ZONING},
	{"GATES", EventType::GATES},
	{"ROADS", EventType::ROADS},
	{"ACTIVATES_KARMA_STATION_ZONING", EventType::ACTIVATES_KARMA_STATION_ZONING},
	{"KARMA_TRACK", EventType::KARMA_TRACK},
	{"TOPIAS", EventType::TOPIAS},
	{"TRAINING_CENTRE", EventType::TRAINING_CENTRE},
	{"PORTS", EventType::PORTS},
	{"SIPHONS_BANKS", EventType::SIPHONS_BANKS},
	{"SPECIAL_BUILDINGS", EventType::SPECIAL_BUILDINGS},
	{"ACTIVATES_OMNIBULGE_LOVEDOME_ZONNIG", EventType::ACTIVATES_OMNIBULGE_LOVEDOME_ZONNIG},
	{"ACTIVATES_LIMBO_ZONING", EventType::ACTIVATES_LIMBO_ZONING},
	{"NUKE_BUTTON", EventType::NUKE_BUTTON},
	{"ROTATE_REALMS_UP", EventType::ROTATE_REALMS_UP},
	{"ROTATE_REALMS_LEFT", EventType::ROTATE_REALMS_LEFT},
	{"ROTATE_REALMS_DOWN", EventType::ROTATE_REALMS_DOWN},
	{"ROTATE_REALMS_RIGHT", EventType::ROTATE_REALMS_RIGHT},
	{"ZOOM_IN", EventType::ZOOM_IN},
	{"ZOOM_OUT", EventType::ZOOM_OUT},
	{"TOGGLE_PLANET_VIEW", EventType::TOGGLE_PLANET_VIEW},
	{"GRAPHVIEW", EventType::GRAPHVIEW},
	{"SOUL_VIEW", EventType::SOUL_VIEW},
	{"TOGGLE_MACROMANAGER", EventType::TOGGLE_MACROMANAGER},
	{"TOGGLE_MAPVIEW", EventType::TOGGLE_MAPVIEW},
	{"TOGGLE_HELPERS", EventType::TOGGLE_HELPERS},
	{"MICROVIEW", EventType::MICROVIEW},
	{"FLATTEN_HELL", EventType::FLATTEN_HELL},
	{"FLATTEN_HEAVEN", EventType::FLATTEN_HEAVEN},
	{"FLATTEN_KARMA", EventType::FLATTEN_KARMA},
	{"FLATTEN_GRID", EventType::FLATTEN_GRID}
};

class UIRemote :public GameObject2D, public Listener
{
public:

	UIRemote(ID3D11Device* _GD);
	virtual ~UIRemote();

	void SetButtonBounds();

	void SetButtonToggle(int i, Window* toggle);
	void SetButtonToggle(int i, BuildingWindow* toggle);

	void onEvent(const Event& event) override;

	void setString(int stringNum, std::string _text);

	virtual void Tick(GameData* _GD);
	virtual void Draw(DrawData2D* _DD);

	bool renderable = true;

	std::array<Button*, 21> buttonsSwitch;
	std::array<ButtonOpenBW*, 9> buttonsBuilding;
	std::array<ButtonToggleWindow*, 7> buttonsWindow;

	std::array<TextGO2D*, 8> text;
	int money = 999999999;
	//int year = 0;

	bool buildingWindowOpen = false;
	bool dragged = false;

protected:

	ID3D11ShaderResourceView* m_pTextureRV;
	Rectangle bounds;

	float differenceX = 0.0f;
	float differenceY = 0.0f;
};
