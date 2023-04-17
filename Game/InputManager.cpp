#include "pch.h"
#include "InputManager.h"

void InputManager::awake(GameData& _game_data)
{
	keyboard_handler = std::make_shared<KeyboardDeviceHandler>();
	mouse_handler = std::make_shared<MouseDeviceHandler>();
	controller_handler = std::make_shared<ControllerDeviceHandler>();

	button_control_handler = std::make_shared<ButtonControlTypeHandler>();
	axis_control_handler  = std::make_shared<AxisControlTypeHandler>();
	vector2_control_handler  = std::make_shared<Vector2ControlTypeHandler>();
	vector2_4_control_handler = std::make_shared<Vector2_4ControlTypeHandler>();
	
	loadInInputActionsMaps(action_maps_filepath + default_bindings_file_name);

	current_action_maps = &game_action_maps; // in future, will rely on the finite state machine to determine current action map.
	active_device = Device::KEYBOARD;
}

void InputManager::update(GameData& _game_data)
{
	
	for (auto action : (*current_action_maps)[(int)active_device])
	{
		action.check(_game_data);
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
		std::vector<InputAction> temp;

		for (JsonElement json_action : input_json["game_state"]["KEYBOARD"])
		{
			temp.emplace_back(loadKeyboardAction(json_action));
		}

		game_action_maps.emplace(game_action_maps.begin() + (int)Device::KEYBOARD, std::move(temp));
		temp.clear();
		
		for (auto json_action : input_json["game_state"]["MOUSE"])
		{
			temp.emplace_back(loadMouseAction(json_action));
		}

		game_action_maps.emplace(game_action_maps.begin() + (int)Device::MOUSE, std::move(temp));
		temp.clear();

		for (auto json_action : input_json["game_state"]["CONTROLLER"])
		{
			temp.emplace_back(loadControllerAction(json_action));
		}

		game_action_maps.emplace(game_action_maps.begin() + (int)Device::CONTROLLER, std::move(temp));
		temp.clear();
	}
	else
	{
		std::cout << "file is empty";
	}
}

InputAction InputManager::loadKeyboardAction(JsonElement& element)
{
	EventType event_type = string_to_event_type.at(std::string(element["Action"]));
	InteractionType interaction_type = string_to_interaction_type.at(std::string(element["Type"]));
	ControlType control_type = string_to_control_type.at(std::string(element["Control"]));
	
	std::shared_ptr<ControlTypeHandler> control_type_handler = nullptr;

	Control control;
	switch (control_type)
	{
		case ControlType::BUTTON:
			{
				control.button.x.key = (Keyboard::Keys)static_cast<unsigned char>(std::stoi(std::string(element["Key"]), nullptr, 16));
				control_type_handler = button_control_handler;
				break;
			}
		case ControlType::AXIS:
			{
				control.axis.x.key = (Keyboard::Keys)static_cast<unsigned char>(std::stoi(std::string(element["Key"]["X"]), nullptr, 16));
				control.axis.neg_x.key = (Keyboard::Keys)static_cast<unsigned char>(std::stoi(std::string(element["Key"]["-X"]), nullptr, 16));
				control_type_handler = axis_control_handler;
				break;
			}
		case ControlType::VECTOR2_4:
			{
				control.vector2_4.x.key = (Keyboard::Keys)static_cast<unsigned char>(std::stoi(std::string(element["Key"]["X"]), nullptr, 16));
				control.vector2_4.neg_x.key = (Keyboard::Keys)static_cast<unsigned char>(std::stoi(std::string(element["Key"]["-X"]), nullptr, 16));

				control.vector2_4.y.key = (Keyboard::Keys)static_cast<unsigned char>(std::stoi(std::string(element["Key"]["-Y"]), nullptr, 16));
				control.vector2_4.neg_y.key = (Keyboard::Keys)static_cast<unsigned char>(std::stoi(std::string(element["Key"]["Y"]), nullptr, 16));
				control_type_handler = vector2_4_control_handler;
				break;
			}
		default:
			{
				std::cerr << "ControlType is invalid for Keybinding - " << std::string(element["Action"]);
			};
	}
	
	ButtonControl modifier;
	modifier.x.key = Keyboard::Help;
	ModifierType mod_type = string_to_mod_type.at(std::string(element["ModType"]));
	std::shared_ptr<DeviceHandler> mod_device_handler = nullptr;
	
	if (mod_type != ModifierType::NONE)
	{
		Device mod_device = string_to_device.at(std::string(element["ModDevice"]));
		switch (mod_device)
		{
			case Device::KEYBOARD:
				{
					modifier.x.key = (Keyboard::Keys)static_cast<unsigned char>(std::stoi(std::string(element["Modifier"]), nullptr, 16));
					mod_device_handler = keyboard_handler;
					break;
				}
			case Device::MOUSE: 
				{
					modifier.x.mouse_input = string_to_mouse_input.at(std::string(element["Modifier"]));
					mod_device_handler = mouse_handler;
					break;
				}
			case Device::CONTROLLER: 
				{
					modifier.x.controller_input = string_to_controller_input.at(std::string(element["Modifier"]));
					mod_device_handler = controller_handler;
					break;
				}
			
			default: ;
		}
	}

	InputAction input_action(event_type, interaction_type, mod_type, modifier, control);
	
	input_action.setDeviceHandler(keyboard_handler);
	input_action.setControlTypeHandler(control_type_handler);

	if (mod_device_handler != nullptr)
	{
		input_action.setModDeviceHandler(mod_device_handler);
	}
	
	return input_action;
}

InputAction InputManager::loadMouseAction(JsonElement& element)
{
	EventType event_type = string_to_event_type.at(std::string(element["Action"]));
	InteractionType interaction_type = string_to_interaction_type.at(std::string(element["Type"]));
	ControlType control_type = string_to_control_type.at(std::string(element["Control"]));
	
	std::shared_ptr<ControlTypeHandler> control_type_handler = nullptr;

	Control control;
	switch (control_type)
	{
		case ControlType::BUTTON:
			{
				control.button.x.mouse_input = string_to_mouse_input.at(std::string(element["Key"]));
				control_type_handler = button_control_handler;
				break;
			}
		case ControlType::AXIS:
			{
				control.axis.x.mouse_input = string_to_mouse_input.at(std::string(element["Key"]["X"]));
				control.axis.neg_x.mouse_input = string_to_mouse_input.at(std::string(element["Key"]["-X"]));
				control_type_handler = axis_control_handler;
				break;
			}
	case ControlType::VECTOR2:
			{
				control.vector2.x.mouse_input = string_to_mouse_input.at(std::string(element["Key"]["X"]));
				control_type_handler = vector2_control_handler;
				break;
			}
		case ControlType::VECTOR2_4:
			{
				control.vector2_4.x.mouse_input = string_to_mouse_input.at(std::string(element["Key"]["X"]));
				control.vector2_4.neg_x.mouse_input = string_to_mouse_input.at(std::string(element["Key"]["-X"]));
			
				control.vector2_4.y.mouse_input = string_to_mouse_input.at(std::string(element["Key"]["Y"]));
				control.vector2_4.neg_y.mouse_input = string_to_mouse_input.at(std::string(element["Key"]["-Y"]));
				control_type_handler = vector2_4_control_handler;
				break;
			}
		default:;
	}
	
	ButtonControl modifier;
	modifier.x.key = Keyboard::Help;
	ModifierType mod_type = string_to_mod_type.at(std::string(element["ModType"]));
	std::shared_ptr<DeviceHandler> mod_device_handler = nullptr;
	
	if (mod_type != ModifierType::NONE)
	{
		Device mod_device = string_to_device.at(std::string(element["ModDevice"]));
		switch (mod_device)
		{
		case Device::KEYBOARD:
			{
				modifier.x.key = (Keyboard::Keys)static_cast<unsigned char>(std::stoi(std::string(element["Modifier"]), nullptr, 16));
				mod_device_handler = keyboard_handler;
				break;
			}
		case Device::MOUSE: 
			{
				modifier.x.mouse_input = string_to_mouse_input.at(std::string(element["Modifier"]));
				mod_device_handler = mouse_handler;
				break;
			}
		case Device::CONTROLLER: 
			{
				modifier.x.controller_input = string_to_controller_input.at(std::string(element["Modifier"]));
				mod_device_handler = controller_handler;
				break;
			}
			
		default: ;
		}
	}
	
	InputAction input_action(event_type, interaction_type, mod_type, modifier, control);
	
	input_action.setDeviceHandler(mouse_handler);
	input_action.setControlTypeHandler(control_type_handler);

	if (mod_device_handler != nullptr)
	{
		input_action.setModDeviceHandler(mod_device_handler);
	}
	
	return input_action;
}

InputAction InputManager::loadControllerAction(JsonElement& element)
{
	EventType event_type = string_to_event_type.at(std::string(element["Action"]));
	InteractionType interaction_type = string_to_interaction_type.at(std::string(element["Type"]));
	ControlType control_type = string_to_control_type.at(std::string(element["Control"]));
	
	std::shared_ptr<ControlTypeHandler> control_type_handler = nullptr;

	Control control;
	switch (control_type)
	{
	case ControlType::BUTTON:
		{
			control.button.x.controller_input = string_to_controller_input.at(std::string(element["Key"]));
			control_type_handler = button_control_handler;
			break;
		}
	case ControlType::AXIS:
		{
			control.axis.x.controller_input = string_to_controller_input.at(std::string(element["Key"]["X"]));
			control.axis.neg_x.controller_input = string_to_controller_input.at(std::string(element["Key"]["-X"]));
			control_type_handler = axis_control_handler;
			break;
		}
	case ControlType::VECTOR2:
		{
			control.vector2.x.controller_input = string_to_controller_input.at(std::string(element["Key"]["X"]));
			control_type_handler = vector2_control_handler;
			break;
		}
	case ControlType::VECTOR2_4:
		{
			control.vector2_4.x.controller_input = string_to_controller_input.at(std::string(element["Key"]["X"]));
			control.vector2_4.neg_x.controller_input = string_to_controller_input.at(std::string(element["Key"]["-X"]));
			
			control.vector2_4.y.controller_input = string_to_controller_input.at(std::string(element["Key"]["Y"]));
			control.vector2_4.neg_y.controller_input = string_to_controller_input.at(std::string(element["Key"]["-Y"]));
			control_type_handler = vector2_4_control_handler;
			break;
		}
	default:;
	}
	
	ButtonControl modifier;
	modifier.x.key = Keyboard::Help;
	ModifierType mod_type = string_to_mod_type.at(std::string(element["ModType"]));
	std::shared_ptr<DeviceHandler> mod_device_handler = nullptr;
	
	if (mod_type != ModifierType::NONE)
	{
		Device mod_device = string_to_device.at(std::string(element["ModDevice"]));
		switch (mod_device)
		{
		case Device::KEYBOARD:
			{
				modifier.x.key = (Keyboard::Keys)static_cast<unsigned char>(std::stoi(std::string(element["Modifier"]), nullptr, 16));
				mod_device_handler = keyboard_handler;
				break;
			}
		case Device::MOUSE: 
			{
				modifier.x.mouse_input = string_to_mouse_input.at(std::string(element["Modifier"]));
				mod_device_handler = mouse_handler;
				break;
			}
		case Device::CONTROLLER: 
			{
				modifier.x.controller_input = string_to_controller_input.at(std::string(element["Modifier"]));
				mod_device_handler = controller_handler;
				break;
			}
			
		default: ;
		}
	}
	
	InputAction input_action(event_type, interaction_type, mod_type, modifier, control);
	
	input_action.setDeviceHandler(mouse_handler);
	input_action.setControlTypeHandler(control_type_handler);

	if (mod_device_handler != nullptr)
	{
		input_action.setModDeviceHandler(mod_device_handler);
	}
	
	return input_action;}


void InputManager::saveInputActionMapChanges(std::string _filepath)
{
	// TODO: Functionality for changing keybinds.
}

void InputManager::resetInputActionMaps()
{
	// TODO: Functionality for resetting keybinds to default.
}
