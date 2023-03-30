#include "pch.h"
#include "InputManager.h"

#include "Button.h"
#include "json.hpp"

void InputManager::awake(GameData& _game_data)
{ 
	
	loadInInputActionsMaps(action_maps_filepath + default_bindings_file_name);

	current_action_maps = &game_action_maps; // in future, will rely on the finite state machine to determine current action map.
}
/*

void InputManager::update(GameData& _game_data)
{
	for (auto const action : *current_key_action_map)
	{
		switch (action.second.type)
		{
			case InteractionType::key_pressed: 
			{
				if (_game_data.m_KBS_tracker.IsKeyPressed(action.second.key_button))
				{
					Event event{};
					event.type = action.first;
					GameManager::get()->getEventManager()->triggerEvent(std::make_shared<Event>(event));
				}
				break;
			}

			case InteractionType::key_released: 
			{
				if (_game_data.m_KBS_tracker.IsKeyReleased(action.second.key_button))
				{
					Event event{};
					event.type = action.first;
					GameManager::get()->getEventManager()->triggerEvent(std::make_shared<Event>(event));
				}
				break;
			}

			case InteractionType::key_held:
			{
				if (_game_data.m_KBS.IsKeyDown(action.second.key_button))
				{
					Event event{};
					event.type = action.first;
					GameManager::get()->getEventManager()->triggerEvent(std::make_shared<Event>(event));
				}
				break;
			}

			case InteractionType::key_pressed_with_mod: 
			{
				if (_game_data.m_KBS_tracker.IsKeyPressed(action.second.key_button) &&
					_game_data.m_KBS.IsKeyDown(action.second.modifier))
				{
					Event event{};
					event.type = action.first;
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

	for (auto action : *current_action_maps)
	{
		switch (action.second.type)
		{
		case InteractionType::mouse_clicked: 
			{
				if (mouse_button_to_button_state.at(action.second.button) == Mouse::ButtonStateTracker::PRESSED)
				{
					triggerMouseButtonEvent(action, EventType::MOUSE_CLICK, _game_data, true);
				}					
			}
			case InteractionType::mouse_released:
			{
					if (mouse_button_to_button_state.at(action.second.button) == Mouse::ButtonStateTracker::RELEASED)
					{
						triggerMouseButtonEvent(action, EventType::MOUSE_RELEASE, _game_data, false);
					}	
				break;
			}
			case InteractionType::mouse_clicked_released:
			{
				if (mouse_button_to_button_state.at(action.second.button) == Mouse::ButtonStateTracker::PRESSED)
				{
					triggerMouseButtonEvent(action, EventType::MOUSE_CLICK, _game_data, true);
				}
				
				else if (mouse_button_to_button_state.at(action.second.button) == Mouse::ButtonStateTracker::RELEASED)
				{
					triggerMouseButtonEvent(action, EventType::MOUSE_RELEASE, _game_data, false);
				}	
				break;
			}
			case InteractionType::mouse_clicked_with_mod:
			{
				if (mouse_button_to_button_state.at(action.second.button) == Mouse::ButtonStateTracker::PRESSED
					&& _game_data.m_KBS.IsKeyDown(action.second.modifier))
				{
					triggerMouseButtonEvent(action, EventType::MOUSE_CLICK, _game_data, false);
				}
				break;
			}
			case InteractionType::mouse_scrolled: 
			{
				if (_game_data.m_MS.scrollWheelValue != 0)
				{
					Mouse::Get().ResetScrollWheelValue();
				}
				break;
			}
			case InteractionType::mouse_scrolled_with_mod: 
			{
				if (_game_data.m_MS.scrollWheelValue != 0
					&& _game_data.m_KBS.IsKeyDown(action.second.modifier))
				{
					Mouse::Get().ResetScrollWheelValue();
				}
				break;
			}
			case InteractionType::mouse_moved:
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


void InputManager::triggerMouseButtonEvent(std::pair<const EventType, MouseAction>& _action, EventType _default_mouse_event, GameData& _game_data, bool _pressed) const
{
	Event event{};
    	
	event.type = !_game_data.mouse_over_UI ? event.type = _action.first : event.type = _default_mouse_event;
	event.payload.mouse_button_event.button = _action.second.button;
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
			current_key_action_map = &menu_action_maps;
			break;
		}

		case State::GAME_PLAY:
		{
			current_key_action_map = &game_key_action_map;
			current_action_maps = &game_action_maps;
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
*/

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
		std::vector<ActionBinding> temp;

		for (JsonElement json_action : input_json["game_state"]["KEYBOARD"])
		{
			temp.emplace_back(loadKeyboardAction(json_action));
		}

		game_action_maps.emplace(game_action_maps.begin() + (int)Device::KEYBOARD, std::move(temp));
		temp.clear();
		
		for (auto json_action : input_json["game_state"]["MOUSE"])
		{
			//temp.emplace_back(loadMouseAction(json_action));
		}
	}
	else
	{
		std::cout << "file is empty";
	}
}

ActionBinding InputManager::loadKeyboardAction(JsonElement& element)
{
	EventType event_type = string_to_event_type.at(std::string(element["Action"]));
	InteractionType interaction_type = string_to_interaction_type.at(std::string(element["Type"]));
	ControlType control_type = string_to_control_type.at(std::string(element["Control"]));

	Control control;
	switch (control_type)
	{
		case ControlType::BUTTON:
			{
				control.button.x.key = (Keyboard::Keys)static_cast<unsigned char>(std::stoi(std::string(element["Key"]), nullptr, 16));
				break;
			}
		case ControlType::AXIS:
			{
				control.axis.x.key = (Keyboard::Keys)static_cast<unsigned char>(std::stoi(std::string(element["Key"]["X"]), nullptr, 16));
				control.axis.neg_x.key = (Keyboard::Keys)static_cast<unsigned char>(std::stoi(std::string(element["Key"]["-X"]), nullptr, 16));
				break;
			}
		case ControlType::VECTOR2_4:
			{
				control.vector2_4.x.key = (Keyboard::Keys)static_cast<unsigned char>(std::stoi(std::string(element["Key"]["X"]), nullptr, 16));
				control.vector2_4.neg_x.key = (Keyboard::Keys)static_cast<unsigned char>(std::stoi(std::string(element["Key"]["-X"]), nullptr, 16));

				control.vector2_4.y.key = (Keyboard::Keys)static_cast<unsigned char>(std::stoi(std::string(element["Key"]["-Y"]), nullptr, 16));
				control.vector2_4.neg_y.key = (Keyboard::Keys)static_cast<unsigned char>(std::stoi(std::string(element["Key"]["Y"]), nullptr, 16));
				break;
			}
		default:
			{
				std::cout << "Control Type is unknown for binding: EventType = " << std::string(element["Action"]);
			}
	}

	ButtonControl modifier;
	modifier.x.key = Keyboard::Help;
	if (!std::string(element["Modifier"]).empty())
	{
		modifier.x.key = (Keyboard::Keys)static_cast<unsigned char>(std::stoi(std::string(element["Modifier"]), nullptr, 16));
	}

	return ActionBinding{event_type, interaction_type, Device::KEYBOARD, control_type, modifier, control};
}

/*
std::pair<EventType, MouseAction> InputManager::loadMouseAction(JsonElement& element)
{
	EventType command = string_to_event_type.at(std::string(element["Action"]));
	InteractionType type = string_to_interaction_type.at(std::string(element["Type"]));

	MouseButton key = string_to_mouse_button.at(std::string(element["Key"]));
	unsigned char modifier = NULL;

	if (!std::string(element["Modifier"]).empty())
	{
		modifier = static_cast<unsigned char>(std::stoi(std::string(element["Modifier"]), nullptr, 16));
	}
	return std::pair<EventType, MouseAction>( command, MouseAction{type, (Keyboard::Keys)modifier, key});
}
*/
void InputManager::saveInputActionMapChanges(std::string _filepath)
{
	// TODO: Functionality for changing keybinds.
}

void InputManager::resetInputActionMaps()
{
	// TODO: Functionality for resetting keybinds to default.
}
