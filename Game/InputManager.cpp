#include "pch.h"
#include "InputManager.h"

void InputManager::awake()
{
	loadInInputActionsMaps(action_maps_filepath + default_bindings_file_name);

	current_action_map = &game_action_map; // in future, will rely on the finite state machine to determine current action map.
}

void InputManager::update(GameData& _game_data)
{
	for (auto const action : *current_action_map)
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
		switch (event.payload.state_transition.current)
		{
		case State::GAME_MENU:
		{
			current_action_map = &menu_action_map;
			break;
		}

		case State::GAME_PLAY:
		{
			current_action_map = &game_action_map;
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
		for (auto json_action : input_json["game_state"]["keyboard_inputs"])
		{
			EventType command = string_to_input_action.at(std::string(json_action["Action"]));
			InputType type = string_to_input_type.at(std::string(json_action["Type"]));

			unsigned char key = static_cast<unsigned char>(std::stoi(std::string(json_action["Key"]), nullptr, 16));
			unsigned char modifier = NULL;

			if (!std::string(json_action["Modifier"]).empty())
			{
				modifier = static_cast<unsigned char>(std::stoi(std::string(json_action["Modifier"]), nullptr, 16));
			}

			game_action_map.emplace_back(KeyboardAction{ command, type, (Keyboard::Keys)modifier, (Keyboard::Keys)key });
		}
	}
	else
	{
		std::cout << "file is empty";
	}
}

void InputManager::saveInputActionMapChanges(std::string _filepath)
{

}

void InputManager::resetInputActionMaps()
{

}
