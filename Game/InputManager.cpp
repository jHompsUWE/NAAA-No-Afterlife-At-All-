#include "pch.h"
#include "InputManager.h"
#include "json.hpp"

void InputManager::awake()
{
	loadInInputActionsMaps(action_maps_filepath + default_bindings_file_name);

	current_key_action_map = &game_key_action_map; // in future, will rely on the finite state machine to determine current action map.
}

void InputManager::update(GameData& _game_data)
{
	for (auto const action : *current_key_action_map)
	{
		switch (action.type)
		{
			case InputType::key_pressed: 
			{
				if (_game_data.m_KBS_tracker.IsKeyPressed(action.key_button))
				{
					Event event{};
					event.type = action.command;
					GameManager::get()->getEventManager()->triggerEvent(std::make_shared<Event>(event));
				}
				break;
			}

			case InputType::key_released: 
			{
				if (_game_data.m_KBS_tracker.IsKeyReleased(action.key_button))
				{
					Event event{};
					event.type = action.command;
					GameManager::get()->getEventManager()->triggerEvent(std::make_shared<Event>(event));
				}
				break;
			}

			case InputType::key_held:
			{
				if (_game_data.m_KBS.IsKeyDown(action.key_button))
				{
					Event event{};
					event.type = action.command;

					GameManager::get()->getEventManager()->triggerEvent(std::make_shared<Event>(event));
				}
				break;
			}

			case InputType::key_pressed_with_mod: 
			{
				if (_game_data.m_KBS_tracker.IsKeyPressed(action.key_button) &&
					_game_data.m_KBS_tracker.IsKeyPressed(action.modifier))
				{
					Event event{};
					event.type = action.command;
					GameManager::get()->getEventManager()->triggerEvent(std::make_shared<Event>(event));
				}
				break;
			}

			case InputType::mouse_clicked: 
			{
				//switch (action.key_button) 
				{
					//case 
				}

				break;
			}

			case InputType::mouse_released:
			{
				break;
			}

			case InputType::mouse_clicked_with_mod: 
			{
				break;
			}

			case InputType::mouse_moved:
			{
				break;
			}

			default:
			{
				break;
			}
		}		
	}
}

void InputManager::onEvent(const Event& event)
{
	if (event.type == EventType::STATE_TRANSITION)
	{
		switch ((State)event.payload.state_transition.current)
		{
		case State::GAME_MENU:
		{
			current_key_action_map = &menu_key_action_map;
			break;
		}

		case State::GAME_PLAY:
		{
			current_key_action_map = &game_key_action_map;
			break;
		}

		case State::GAME_PAUSED:
		{
			break;
		}

		case State::GAME_TUTORIAL:
		{
			break;
		}

		case State::GAME_OVER:
		{
			break;
		}

		default:
		{
			break;
		}
		}
	}
}

void InputManager::loadInInputActionsMaps(std::string _filepath)
{
	// Should utilize FileManager to pull in the .json, so this is temp. 
	std::ifstream file(_filepath);
	json input_json;

	if (file.good())
	{
		input_json = json::parse(file);
	}
	file.close();

	if (!input_json.empty())
	{
		for (json_element json_action : input_json["game_state"]["keyboard_inputs"])
		{
			game_key_action_map.emplace_back(loadKeyboardAction(json_action));
		}
		for (auto json_action : input_json["game_state"]["mouse_inputs"])
		{
			game_mouse_action_map.emplace_back(loadMouseAction(json_action));
		}
	}
	else
	{
		std::cout << "file is empty";
	}
}

KeyboardAction InputManager::loadKeyboardAction(json_element& element)
{
	EventType command = string_to_input_action.at(std::string(element["Action"]));
	InputType type = string_to_input_type.at(std::string(element["Type"]));

	unsigned char key = static_cast<unsigned char>(std::stoi(std::string(element["Key"]), nullptr, 16));
	unsigned char modifier = NULL;

	if (!std::string(element["Modifier"]).empty())
	{
		modifier = static_cast<unsigned char>(std::stoi(std::string(element["Modifier"]), nullptr, 16));
	}

	return KeyboardAction{ command, type, (Keyboard::Keys)modifier, (Keyboard::Keys)key };
}

MouseAction InputManager::loadMouseAction(json_element& element)
{
	EventType command = string_to_input_action.at(std::string(element["Action"]));
	InputType type = string_to_input_type.at(std::string(element["Type"]));

	MouseButton key = string_to_mouse_button.at(std::string(element["Key"]));
	unsigned char modifier = NULL;

	if (!std::string(element["Modifier"]).empty())
	{
		modifier = static_cast<unsigned char>(std::stoi(std::string(element["Modifier"]), nullptr, 16));
	}
	return MouseAction{ command, type, (Keyboard::Keys)modifier, key};
}

void InputManager::saveInputActionMapChanges(std::string _filepath)
{
	// TODO: Functionality for changing keybinds.
}

void InputManager::resetInputActionMaps()
{
	// TODO: Functionality for resetting keybinds to default.
}
