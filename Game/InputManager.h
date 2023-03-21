#pragma once

#include <unordered_map>
#include <memory>
#include <fstream>
#include <iostream>

#include "Manager.h"
#include "json.hpp"
#include "GameManager.h"

enum class InputType
{
	key_pressed,
    key_released,
    key_held,
    key_pressed_with_mod,
    mouse_clicked,
    mouse_released,
	mouse_clicked_released,
    mouse_clicked_with_mod,
    mouse_moved
};

enum class MouseButton
{
	left,
	middle,
	right
};


struct KeyboardAction
{
    EventType command;
    InputType type;
    Keyboard::Keys modifier;
    Keyboard::Keys key_button;
};

struct MouseAction
{
	EventType command;
	InputType type;
	Keyboard::Keys modifier;
	MouseButton button;
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
    {"GENERIC_ZONING", EventType::GENERIC_ZONING},
	{"CENTER_AND_ZOOM_IN", EventType::CENTER_AND_ZOOM_IN},
	{"CENTER_AND_ZOOM_OUT", EventType::CENTER_AND_ZOOM_OUT},
	{"CENTER_VIEW", EventType::CENTER_VIEW},
	{"SELECT", EventType::SELECT}
};

static const std::unordered_map<std::string, InputType> string_to_input_type =
{
	{"key_pressed", InputType::key_pressed},
	{"key_released", InputType::key_released},
    {"key_held", InputType::key_held},
	{"mouse_clicked", InputType::mouse_clicked},
	{"mouse_released", InputType::mouse_released},
	{"mouse_clicked_released", InputType::mouse_clicked_released},
	{"mouse_clicked_with_mod", InputType::mouse_clicked_with_mod},
	{"mouse_moved", InputType::mouse_moved}
};

static const std::unordered_map<std::string, MouseButton> string_to_mouse_button =
{
	{"right", MouseButton::right},
	{"left", MouseButton::left},
	{"middle", MouseButton::middle}
};

using json = nlohmann::json;
using json_element = nlohmann::json_abi_v3_11_2::basic_json<std::map, std::vector, std::basic_string<char,
std::char_traits<char>, std::allocator<char> >,bool,__int64,unsigned __int64,double, std::allocator,
nlohmann::json_abi_v3_11_2::adl_serializer, std::vector<unsigned char, std::allocator<unsigned char>>>;

class InputManager : public Manager, public Listener
{
public:
    InputManager() = default;
    ~InputManager() = default;
	
	////////////////////////////////////////////////////////////
	/// \brief Is called when the program initializes.
	////////////////////////////////////////////////////////////
    void awake() override;

	////////////////////////////////////////////////////////////
	/// \brief Called every cycle of the game loop.
	///	\param _timer DeltaTime.
	////////////////////////////////////////////////////////////
    void update(GameData& _game_data) override;

	////////////////////////////////////////////////////////////
	/// \brief Interface function for concrete listeners to override. \n Allows listener derived classes to receive events from the EventManager.
	///	\param event The event to be acted upon.
	////////////////////////////////////////////////////////////
    void onEvent(const Event& event) override;

private:
    void loadInInputActionsMaps(std::string _filepath);

    ////////////////////////////////////////////////////////////
	/// \brief Incomplete - but will save any changes to the action map. 
	////////////////////////////////////////////////////////////
    void saveInputActionMapChanges(std::string _filepath);

	////////////////////////////////////////////////////////////
	/// \brief Load and return a KeyboardAction.
	////////////////////////////////////////////////////////////
	KeyboardAction loadKeyboardAction(json_element& element);

	////////////////////////////////////////////////////////////
	/// \brief Load and return a MouseAction.
	////////////////////////////////////////////////////////////
	MouseAction loadMouseAction(json_element& element);

    ////////////////////////////////////////////////////////////
	/// \brief Incomplete - but will reset the action map back to default. 
	////////////////////////////////////////////////////////////
    void resetInputActionMaps();

    ////////////////////////////////////////////////////////////
	/// \brief Key action map for the game state. 
	////////////////////////////////////////////////////////////
    std::vector<KeyboardAction> game_key_action_map;

	////////////////////////////////////////////////////////////
	/// \brief Mouse action map for the game state. 
	////////////////////////////////////////////////////////////
	std::vector<MouseAction> game_mouse_action_map;
	
    ////////////////////////////////////////////////////////////
	/// \brief Key action map for the menu state. 
	////////////////////////////////////////////////////////////
    std::vector<KeyboardAction> menu_key_action_map;

    ////////////////////////////////////////////////////////////
	/// \brief Pointer to the current keyboard action map. 
	////////////////////////////////////////////////////////////
    std::vector<KeyboardAction>* current_key_action_map;

    ////////////////////////////////////////////////////////////
	/// \brief Filepath - Path to data folder which holds the keybind jsons. 
	////////////////////////////////////////////////////////////
    std::string action_maps_filepath = "../Data/";

    ////////////////////////////////////////////////////////////
	/// \brief Default keybinds filename - Only use this one for resetting custom to default.
	////////////////////////////////////////////////////////////
    std::string default_bindings_file_name = "keybinds_default.json";

    ////////////////////////////////////////////////////////////
	/// \brief Custom keybinds filename - Load in and use this one.
	////////////////////////////////////////////////////////////
    std::string custom_bindings_file_name = "keybinds_custom.json";
};
