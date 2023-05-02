#pragma once


#include <unordered_map>
#include <memory>
#include <fstream>
#include <iostream>

#include "Manager.h"
#include "json.hpp"
#include "GameManager.h"
#include "InputAction.hpp"
#include "GameStateBase.h"

static const std::unordered_map<std::string, State> string_to_state =
{
	{"GAME_EXIT", State::GAME_EXIT},
	{"GAME_MENU", State::GAME_MENU},
	{"GAME_PLAY", State::GAME_PLAY},
	{"GAME_PAUSED", State::GAME_PAUSED},
	{"GAME_TUTORIAL", State::GAME_TUTORIAL},
	{"GAME_OVER", State::GAME_OVER}
};

static const std::unordered_map<std::string, EventType> string_to_event_type =
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
	{"FLATTEN_GRID", EventType::FLATTEN_GRID}
};

static const std::unordered_map<std::string, InteractionType> string_to_interaction_type =
{
	{"BUTTON_PRESSED", InteractionType::BUTTON_PRESSED},
	{"BUTTON_RELEASED", InteractionType::BUTTON_RELEASED},
    {"BUTTON_HELD", InteractionType::BUTTON_HELD},
	{"BUTTON_PRESSED_RELEASED", InteractionType::BUTTON_PRESSED_RELEASED},
	{"AXIS", InteractionType::AXIS},
	{"VECTOR2", InteractionType::VECTOR2}
};

static const std::unordered_map<std::string, Device> string_to_device =
{
	{"KEYBOARD", Device::KEYBOARD},
	{"MOUSE", Device::MOUSE},
	{"CONTROLLER", Device::CONTROLLER},
};

static const std::unordered_map<std::string, ControlType> string_to_control_type =
{
	{"BUTTON", ControlType::BUTTON},
	{"AXIS", ControlType::AXIS},
	{"VECTOR2_2", ControlType::VECTOR2},
	{"VECTOR2_4", ControlType::VECTOR2_4},
};

static const std::unordered_map<std::string, ModifierType> string_to_mod_type =
{
	{"NONE", ModifierType::NONE},
	{"HELD", ModifierType::HELD}
};

static const std::unordered_map<std::string, MouseInput> string_to_mouse_input =
{
	{"LEFT_BUTTON", MouseInput::LEFT_BUTTON},
	{"MIDDLE_BUTTON", MouseInput::MIDDLE_BUTTON},
	{"RIGHT_BUTTON", MouseInput::RIGHT_BUTTON},
	{"MOVE", MouseInput::MOVE},
	{"SCROLL", MouseInput::SCROLL}	
};

static const std::unordered_map<std::string, ControllerInput> string_to_controller_input =
{
	{"A", ControllerInput::A},
	{"B", ControllerInput::B},
	{"X", ControllerInput::X},
	{"Y", ControllerInput::Y},
	{"LEFT_STICK", ControllerInput::LEFT_STICK},
	{"RIGHT_STICK", ControllerInput::RIGHT_STICK},
	{"LEFT_SHOULDER", ControllerInput::LEFT_SHOULDER},
	{"RIGHT_SHOULDER", ControllerInput::RIGHT_SHOULDER},
	{"BACK", ControllerInput::BACK},
	{"START", ControllerInput::START},
	{"D_UP", ControllerInput::D_UP},
	{"D_DOWN", ControllerInput::D_DOWN},
	{"D_RIGHT", ControllerInput::D_RIGHT},
	{"D_LEFT", ControllerInput::D_LEFT},
	{"LEFT_TRIGGER", ControllerInput::LEFT_TRIGGER},
	{"RIGHT_TRIGGER", ControllerInput::RIGHT_TRIGGER}
};

using Json = nlohmann::json;
using JsonElement = nlohmann::json_abi_v3_11_2::basic_json<std::map, std::vector, std::basic_string<char,
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
    void awake(GameData& _game_data) override;

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
	////////////////////////////////////////////////////////////
	/// \brief Loads in the json of action maps at a specified file path.
	/// \param _filepath The filepath of the json to load in.
	////////////////////////////////////////////////////////////
    void loadInInputActionsMaps(std::string _filepath);
	
    ////////////////////////////////////////////////////////////
	/// \brief Incomplete - but will save any changes to the action map. 
	////////////////////////////////////////////////////////////
    void saveInputActionMapChanges(std::string _filepath);

	////////////////////////////////////////////////////////////
	/// \brief Load and return a keyboard ActionBinding.
	////////////////////////////////////////////////////////////
	InputAction loadKeyboardAction(JsonElement& element);

	////////////////////////////////////////////////////////////
	/// \brief Load and return a mouse Actionbinding.
	////////////////////////////////////////////////////////////
	InputAction loadMouseAction(JsonElement& element);

	////////////////////////////////////////////////////////////
	/// \brief Load and return a controller ActionBinding.
	////////////////////////////////////////////////////////////
	InputAction loadControllerAction(JsonElement& element);

	////////////////////////////////////////////////////////////
	/// \brief Fires off the game events triggered by mouse button events.
	/// \param _action The MouseAction containing the keybind data.
	/// \param _game_data Game Data.
	/// \param _default_mouse_event The event triggered if the mouse is over UI.
	/// \param _pressed Whether the button has been pressed or released.
	////////////////////////////////////////////////////////////
	//void triggerMouseButtonEvent(std::pair<const EventType, MouseAction>& _action, EventType _default_mouse_event, GameData& _game_data, bool _pressed) const;

    ////////////////////////////////////////////////////////////
	/// \brief Incomplete - but will reset the action map back to default. 
	////////////////////////////////////////////////////////////
    void resetInputActionMaps();

	////////////////////////////////////////////////////////////
	/// \brief Action maps for the game state.
	////////////////////////////////////////////////////////////
	std::unordered_map<State, std::vector<InputAction>> action_maps;

	////////////////////////////////////////////////////////////
	/// \brief Index for the current action maps container. 
	////////////////////////////////////////////////////////////
	State current_action_map;

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
	
	////////////////////////////////////////////////////////////
	/// \brief Mouse position of the last update cycle. 
	////////////////////////////////////////////////////////////
	std::pair<int, int> last_mouse_pos;

	std::shared_ptr<KeyboardDeviceHandler> keyboard_handler;
	std::shared_ptr<MouseDeviceHandler> mouse_handler;
	std::shared_ptr<ControllerDeviceHandler> controller_handler;

	std::shared_ptr<ButtonControlTypeHandler> button_control_handler;
	std::shared_ptr<AxisControlTypeHandler> axis_control_handler;
	std::shared_ptr<Vector2ControlTypeHandler> vector2_control_handler;
	std::shared_ptr<Vector2_4ControlTypeHandler> vector2_4_control_handler;
};
