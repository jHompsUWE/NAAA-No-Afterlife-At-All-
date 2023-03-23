#include "pch.h"
#include "InputManager.h"
#include "json.hpp"

void InputManager::awake(GameData& _game_data)
{
	mouse_button_to_button_state = {{MouseButton::right, _game_data.m_mouseButtons.rightButton},
										{MouseButton::left, _game_data.m_mouseButtons.leftButton},
										{MouseButton::middle, _game_data.m_mouseButtons.middleButton}};
	
	loadInInputActionsMaps(action_maps_filepath + default_bindings_file_name);

	current_key_action_map = &game_key_action_map; // in future, will rely on the finite state machine to determine current action map.
	current_mouse_action_map = &game_mouse_action_map;
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
					_game_data.m_KBS.IsKeyDown(action.modifier))
				{
					Event event{};
					event.type = action.command;
					GameManager::get()->getEventManager()->triggerEvent(std::make_shared<Event>(event));
				}
				break;
			}
			default:
			{
				break;
			}
		}		
	}

	for (auto action : *current_mouse_action_map)
	{
		switch (action.type)
		{
		case InputType::mouse_clicked: 
			{
				if (mouse_button_to_button_state.at(action.button) == Mouse::ButtonStateTracker::PRESSED)
				{
					triggerMouseButtonEvent(action, EventType::MOUSE_CLICK, _game_data, true);
				}					
			}
			case InputType::mouse_released:
			{
					if (mouse_button_to_button_state.at(action.button) == Mouse::ButtonStateTracker::RELEASED)
					{
						triggerMouseButtonEvent(action, EventType::MOUSE_RELEASE, _game_data, false);
					}	
				break;
			}
			case InputType::mouse_clicked_released:
			{
				if (mouse_button_to_button_state.at(action.button) == Mouse::ButtonStateTracker::PRESSED)
				{
					triggerMouseButtonEvent(action, EventType::MOUSE_CLICK, _game_data, true);
				}
				
				else if (mouse_button_to_button_state.at(action.button) == Mouse::ButtonStateTracker::RELEASED)
				{
					triggerMouseButtonEvent(action, EventType::MOUSE_RELEASE, _game_data, false);
				}	
				break;
			}
			case InputType::mouse_clicked_with_mod:
			{
				if (mouse_button_to_button_state.at(action.button) == Mouse::ButtonStateTracker::PRESSED
					&& _game_data.m_KBS.IsKeyDown(action.modifier))
				{
					triggerMouseButtonEvent(action, EventType::MOUSE_CLICK, _game_data, false);
				}
				break;
			}
			case InputType::mouse_scrolled: 
			{
				if (_game_data.m_MS.scrollWheelValue != 0)
				{
					Mouse::Get().ResetScrollWheelValue();
				}
				break;
			}
			case InputType::mouse_scrolled_with_mod: 
			{
				if (_game_data.m_MS.scrollWheelValue != 0
					&& _game_data.m_KBS.IsKeyDown(action.modifier))
				{
					Mouse::Get().ResetScrollWheelValue();
				}
				break;
			}
			case InputType::mouse_moved:
			{
				if (_game_data.m_MS.x != std::get<0>(last_mouse_pos) || _game_data.m_MS.y != std::get<1>(last_mouse_pos))
				{
					std::get<0>(last_mouse_pos) = _game_data.m_MS.x;
					std::get<1>(last_mouse_pos) = _game_data.m_MS.y;

					Event event{};
					event.type = EventType::MOUSE_CLICK;
					event.payload.mouse_move_event.x_mouse_pos = std::get<0>(last_mouse_pos);
					event.payload.mouse_move_event.y_mouse_pos = std::get<1>(last_mouse_pos);

					GameManager::get()->getEventManager()->triggerEvent(std::make_shared<Event>(event));
				}
				break;
			}
		
			default: ;
		}
	}
}

void InputManager::triggerMouseButtonEvent(MouseAction& _action, EventType _default_mouse_event, GameData& _game_data, bool _pressed) const
{
	Event event{};
    	
	event.type = !_game_data.mouse_over_UI ? event.type = _action.command : event.type = _default_mouse_event;
	event.payload.mouse_button_event.button = _action.button;
	event.payload.mouse_button_event.x_mouse_pos = _game_data.m_MS.x;
	event.payload.mouse_button_event.y_mouse_pos = _game_data.m_MS.y;
	event.payload.mouse_button_event.pressed = _pressed;
    
	GameManager::get()->getEventManager()->triggerEvent(std::make_shared<Event>(event));
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
			current_mouse_action_map = &game_mouse_action_map;
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
	Json input_json;

	if (file.good())
	{
		input_json = Json::parse(file);
	}
	file.close();

	if (!input_json.empty())
	{
		for (JsonElement json_action : input_json["game_state"]["keyboard_inputs"])
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

KeyboardAction InputManager::loadKeyboardAction(JsonElement& element)
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

MouseAction InputManager::loadMouseAction(JsonElement& element)
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
