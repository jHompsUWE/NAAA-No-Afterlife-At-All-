#pragma once

#include <unordered_map>
#include <fstream>
#include <iostream>

#include "Manager.h"
#include "json.hpp"
#include "GameManager.h"

//can swap out for Paul's FSM enu.
enum class InputActionMap
{
    menu_state,
    game_state,
};

enum class InputType
{
	key_pressed,
    key_released,
    key_pressed_with_mod,
    mouse_clicked,
    mouse_released,
    mouse_clicked_with_mod,
    mouse_moved
};

struct KeyboardAction
{
    EventType command;
    InputType type;
    Keyboard::Keys modifier;
    Keyboard::Keys key_button;
};

static const std::unordered_map<std::string, EventType> string_to_input_action =
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
	{"ACTIVATES_OMNIBULGE_LOVEDOME_ZONNIG", EventType::ACTIVATES_OMNIBULGE_LOVEDOME_ZONNIG},
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
    {"SCROLL_UP", EventType::SCROLL_UP},
    {"SCROLL_RIGHT", EventType::SCROLL_RIGHT},
    {"SCROLL_LEFT", EventType::SCROLL_LEFT},
    {"SCROLL_DOWN", EventType::SCROLL_DOWN},
    {"ROTATE_REALMS_RIGHT", EventType::ROTATE_REALMS_RIGHT},
    {"ROTATE_REALMS_LEFT", EventType::ROTATE_REALMS_LEFT},
    {"GREEN_ZONING", EventType::GREEN_ZONING},
    {"YELLOW_ZONING", EventType::YELLOW_ZONING},
    {"ORANGE_ZONING", EventType::ORANGE_ZONING},
    {"BROWN_ZONING", EventType::BROWN_ZONING},
    {"PURPLE_ZONING", EventType::PURPLE_ZONING},
    {"RED_ZONING", EventType::RED_ZONING},
    {"BLUE_ZONING", EventType::BLUE_ZONING},
    {"GENERIC_ZONING", EventType::GENERIC_ZONING}
};

static const std::unordered_map<std::string, InputType> string_to_input_type =
{
{"key_pressed", InputType::key_pressed},
{"key_released", InputType::key_released},
{"mouse_button_pressed", InputType::mouse_clicked},
{"mouse_button_released", InputType::mouse_released},
{"mouse_moved", InputType::mouse_moved}
};


using json = nlohmann::json;

class InputManager : public Manager, public Listener
{
public:
    InputManager() = default;
    ~InputManager() = default;

    void awake() override;
    void update(DX::StepTimer const& _timer) override;
    void onEvent(const Event& event) override;


private:
    void loadInInputActionsMaps(std::string _filepath);
    void saveInputActionMapChanges(std::string _filepath);
    void resetInputActionMaps();

    std::vector<KeyboardAction> game_action_map;
    std::vector<KeyboardAction> menu_action_map;
    std::vector<KeyboardAction>* current_action_map;

    std::string action_maps_filepath = "../Data/";
    std::string default_bindings_file_name = "keybinds_default.json";
    std::string custom_bindings_file_name = "keybinds_custom.json";
};
