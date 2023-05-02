#pragma once

#include "GameObject2D.h"
#include "UIRemote.h"
#include "WindowDraggable.h"
#include "Button.h"
#include "Manager.h"
#include "BuildingWindow.h"
#include "OptionBar.h"

static const std::unordered_map<std::string, Direction> string_to_direction =
{
	{"left", Direction::LEFT},
	{"right", Direction::RIGHT},
	{"up", Direction::UP},
	{"down", Direction::DOWN}
};

static const std::unordered_map<std::string, EventType> string_to_event =
{
	{"PAUSE", EventType::PAUSE},
	{"LOAD_GAME", EventType::LOAD_GAME},
	{"LOAD_SCENARIO", EventType::LOAD_SCENARIO},
	{"SAVE_GAME", EventType::SAVE_GAME},
	{"QUIT", EventType::QUIT},
	{"AUDIO_MENU", EventType::AUDIO_MENU},
	{"NEW_GAME", EventType::NEW_GAME},
	{"CLOSE", EventType::CLOSE},
	{"PORTS", EventType::PORTS},
	{"TOPIAS", EventType::TOPIAS},
	{"GRAPHVIEW", EventType::GRAPHVIEW},
	{"ACTIVATE_MISC_ZONING", EventType::ACTIVATE_MISC_ZONING},
	{"TOGGLE_MAPVIEW", EventType::TOGGLE_MAPVIEW},
	{"GATES", EventType::GATES},
	{"TOGGLE_HELPERS", EventType::TOGGLE_HELPERS},
	{"SOUL_VIEW", EventType::SOUL_VIEW},
	{"ACTIVATES_KARMA_STATION_ZONING", EventType::ACTIVATES_KARMA_STATION_ZONING},
	{"ACTIVATES_LIMBO_ZONING", EventType::ACTIVATES_LIMBO_ZONING},
	{"MICROVIEW", EventType::MICROVIEW},
	{"TRAINING_CENTRE", EventType::TRAINING_CENTRE},
	{"ACTIVATES_OMNIBULGE_LOVEDOME_ZONING", EventType::ACTIVATES_OMNIBULGE_LOVEDOME_ZONING},
	{"TOGGLE_PLANET_VIEW", EventType::TOGGLE_PLANET_VIEW},
	{"ROADS", EventType::ROADS},
	{"SPECIAL_BUILDINGS", EventType::SPECIAL_BUILDINGS},
	{"KARMA_TRACK", EventType::KARMA_TRACK},
	{"TOGGLE_MACROMANAGER", EventType::TOGGLE_MACROMANAGER},
	{"NUKE_BUTTON", EventType::NUKE_BUTTON},
	{"TOGGLE_REMOTE_CONTROL", EventType::TOGGLE_REMOTE_CONTROL},
	{"TOGGLE_PREVIOUS_TEMPO_AND_DEVINE_INTERVENTION", EventType::TOGGLE_PREVIOUS_TEMPO_AND_DEVINE_INTERVENTION},
	{"ZOOM_IN", EventType::ZOOM_IN},
	{"ZOOM_OUT", EventType::ZOOM_OUT},
	{"SNAP_TO_HEAVEN", EventType::SNAP_TO_HEAVEN},
	{"SNAP_TO_HELL", EventType::SNAP_TO_HELL},
	{"SCROLL_VIEW", EventType::SCROLL_VIEW},
	{"ROTATE_REALMS", EventType::ROTATE_REALMS},
	{"GREEN_ZONING", EventType::GREEN_ZONING},
	{"YELLOW_ZONING", EventType::YELLOW_ZONING},
	{"ORANGE_ZONING", EventType::ORANGE_ZONING},
	{"BROWN_ZONING", EventType::BROWN_ZONING},
	{"PURPLE_ZONING", EventType::PURPLE_ZONING},
	{"RED_ZONING", EventType::RED_ZONING},
	{"BLUE_ZONING", EventType::BLUE_ZONING},
	{"GENERIC_ZONING", EventType::GENERIC_ZONING},
	{"CENTER_AND_ZOOM_IN", EventType::CENTER_AND_ZOOM_IN},
	{"CENTER_AND_ZOOM_OUT", EventType::CENTER_AND_ZOOM_OUT},
	{"CENTER_VIEW", EventType::CENTER_VIEW},
	{"SELECT_CURSOR", EventType::SELECT_CURSOR},
	{"MOVE_CURSOR", EventType::MOVE_CURSOR},
	{"FLATTEN_HELL", EventType::FLATTEN_HELL},
	{"FLATTEN_HEAVEN", EventType::FLATTEN_HEAVEN},
	{"FLATTEN_KARMA", EventType::FLATTEN_KARMA},
	{"FLATTEN_GRID", EventType::FLATTEN_GRID},
	{"SIPHONS_BANKS", EventType::SIPHONS_BANKS}
};

class UIManager : public Manager
{
public:
	UIManager(ID3D11Device* _ID, GameData* _GD);
	~UIManager();

	void awake(GameData& _game_data) override;
	void update(GameData& _game_data) override;
	//virtual void lateUpdate(GameData& _game_data) override;

	void Draw(DrawData2D* _DD);

	//General remote
	UIRemote* remote;
	OptionBar* optBar;

	//View windows
	std::array<WindowDraggable*, 6> viewWindows;

	std::array<BuildingWindow*, 3> buildWindows;

private:
	ID3D11Device* m_ID;
	GameData* m_GD;
};

