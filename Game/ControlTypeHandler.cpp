#include "pch.h"
#include "ControlTypeHandler.h"

void ButtonControlTypeHandler::check(DeviceHandler& _device_handler, DeviceHandler& _mod_device_handler,
                                     ActionBinding& _action_binding, const GameData& _data)
{
    bool mod_active = false;
    if (_action_binding.mod_type == ModifierType::HELD)
    {
        mod_active = _mod_device_handler.checkHeld(_action_binding.mod.x, _data);
    }
    
    switch (_action_binding.interaction_type)
    {
        case InteractionType::BUTTON_PRESSED:
            {
                if (_device_handler.checkPressed(_action_binding.control.button.x, _data))
                {
                    createButtonEvent(_action_binding, mod_active, true, LastButtonState::PRESSED);
                }
                break;
            }
        case InteractionType::BUTTON_RELEASED: 
            {
                if (_device_handler.checkReleased(_action_binding.control.button.x, _data))
                {
                    createButtonEvent(_action_binding, mod_active, false, LastButtonState::RELEASED);
                }
                break;
            }
        case InteractionType::BUTTON_HELD: 
            {
                if (_device_handler.checkHeld(_action_binding.control.button.x, _data))
                {
                    createButtonEvent(_action_binding, mod_active, true, LastButtonState::DOWN);
                }
                break;
            }
        case InteractionType::BUTTON_PRESSED_RELEASED: 
            {
                if (_device_handler.checkPressed(_action_binding.control.button.x, _data))
                {
                    createButtonEvent(_action_binding, mod_active, true, LastButtonState::PRESSED);
                }
                else if (_device_handler.checkReleased(_action_binding.control.button.x, _data))
                {
                    createButtonEvent(_action_binding, mod_active, false, LastButtonState::RELEASED);
                }
                break;
            }

        default: ;
    }
}

void AxisControlTypeHandler::check(DeviceHandler& _device_handler, DeviceHandler& _mod_device_handler,
                                   ActionBinding& _action_binding, const GameData& _data)
{
    bool mod_active = false;
    if (_action_binding.mod_type == ModifierType::HELD)
    {
        mod_active = _mod_device_handler.checkHeld(_action_binding.mod.x, _data);
    }
    
    switch (_action_binding.interaction_type)
    {
        case InteractionType::BUTTON_PRESSED:
            {
                float value = (int)_device_handler.checkPressed(_action_binding.control.axis.x, _data) - (int)_device_handler.checkPressed(_action_binding.control.axis.neg_x, _data);
                if (value != _action_binding.last_state.axis_state.value)
                {
                    createAxisEvent(_action_binding, mod_active, value);
                }
                break;
            }
        case InteractionType::BUTTON_RELEASED: 
            {
                float value = (int)_device_handler.checkReleased(_action_binding.control.axis.x, _data) - (int)_device_handler.checkReleased(_action_binding.control.axis.neg_x, _data);

                if (value != _action_binding.last_state.axis_state.value)
                {
                    createAxisEvent(_action_binding, mod_active, value);
                }
                break;
            }
        case InteractionType::BUTTON_HELD: 
            {
                float value = (int)_device_handler.checkHeld(_action_binding.control.axis.x, _data) - (int)_device_handler.checkHeld(_action_binding.control.axis.neg_x, _data);
                if (value != 0)
                {
                    createAxisEvent(_action_binding, mod_active, value);
                }
                break;
            }
        case InteractionType::BUTTON_PRESSED_RELEASED: 
            {
                if (_device_handler.checkPressed(_action_binding.control.axis.x, _data))
                {
                    createAxisEvent(_action_binding, mod_active, 1);
                    return;
                }
                
                if (_device_handler.checkPressed(_action_binding.control.axis.neg_x, _data))
                {
                    createAxisEvent(_action_binding, mod_active, -1);
                    return;
                }
                
                if (_device_handler.checkReleased(_action_binding.control.axis.x, _data)
                    || _device_handler.checkReleased(_action_binding.control.axis.neg_x, _data))
                {
                    createAxisEvent(_action_binding, mod_active, 0);
                }
                break;
            }
        case InteractionType::AXIS:
            {
                float axis_value = _device_handler.getAxis(_action_binding.control.axis.x, _data);
                
                if (axis_value != _action_binding.last_state.axis_state.value)
                {
                    _action_binding.last_state.axis_state.value = axis_value;
                    createAxisEvent(_action_binding, mod_active, axis_value);
                }
                break;
            }
    
        default: ;
    }
}

void Vector2ControlTypeHandler::check(DeviceHandler& _device_handler, DeviceHandler& _mod_device_handler,
                                        ActionBinding& _action_binding, const GameData& _data)
{
    bool mod_active = false;
    if (_action_binding.mod_type == ModifierType::HELD)
    {
        mod_active = _mod_device_handler.checkHeld(_action_binding.mod.x, _data);
    }

    switch (_action_binding.interaction_type)
    {
        case InteractionType::VECTOR2:
            {
                std::pair<float, float> vect = _device_handler.getVector2(_action_binding.control.vector2.x, _data);

                if (vect.first != _action_binding.last_state.vector2_state.x || vect.second != _action_binding.last_state.vector2_state.y)
                {
                    createVector2Event(_action_binding, mod_active, vect.first, vect.second);
                }
                break;
            }
        
        default: ;
    }
    
}

void Vector2_4ControlTypeHandler::check(DeviceHandler& _device_handler, DeviceHandler& _mod_device_handler,
                                        ActionBinding& _action_binding, const GameData& _data)
{
    bool mod_active = _action_binding.mod_type == ModifierType::HELD
    ? _mod_device_handler.checkHeld(_action_binding.mod.x, _data)
    : false;

    switch (_action_binding.interaction_type)
    {
        case InteractionType::BUTTON_PRESSED:
            {
                std::pair<float, float> vect{0,0};

                vect.first  = _device_handler.checkPressed(_action_binding.control.vector2_4.x, _data) ? 1 : _device_handler.checkPressed(_action_binding.control.vector2_4.neg_x, _data) ? -1 : 0;
                vect.second = _device_handler.checkPressed(_action_binding.control.vector2_4.y, _data) ? 1 : _device_handler.checkPressed(_action_binding.control.vector2_4.neg_y, _data) ? -1 : 0;

                if (vect.first != _action_binding.last_state.vector2_state.x || vect.second != _action_binding.last_state.vector2_state.y)
                {
                    createVector2Event(_action_binding, mod_active, vect.first, vect.second);
                }
                break;
            }
        case InteractionType::BUTTON_RELEASED: 
            {
                std::pair<float, float> vect{0,0};

                vect.first = _device_handler.checkReleased(_action_binding.control.vector2_4.x, _data) ? 1 : _device_handler.checkReleased(_action_binding.control.vector2_4.neg_x, _data) ? -1 : 0;
                vect.second = _device_handler.checkReleased(_action_binding.control.vector2_4.y, _data) ? 1 : _device_handler.checkReleased(_action_binding.control.vector2_4.neg_y, _data) ? -1 : 0;

                if (vect.first != _action_binding.last_state.vector2_state.x || vect.second != _action_binding.last_state.vector2_state.y)
                {
                    createVector2Event(_action_binding, mod_active, vect.first, vect.second);
                }
                break;
            }
        case InteractionType::BUTTON_HELD: 
            {
                std::pair<float, float> vect{0,0};

                vect.first = _device_handler.checkHeld(_action_binding.control.vector2_4.x, _data) ? 1 : _device_handler.checkHeld(_action_binding.control.vector2_4.neg_x, _data) ? -1 : 0;
                vect.second = _device_handler.checkHeld(_action_binding.control.vector2_4.y, _data) ? 1 : _device_handler.checkHeld(_action_binding.control.vector2_4.neg_y, _data) ? -1 : 0;

                if (vect.first != 0 || vect.second != 0)
                {
                    createVector2Event(_action_binding, mod_active, vect.first, vect.second);
                }
                break;
            }
        case InteractionType::BUTTON_PRESSED_RELEASED: 
            {
                std::pair<float, float> vect{0,0};

                vect.first = _device_handler.checkPressed(_action_binding.control.vector2_4.x, _data) ? 1 : _device_handler.checkPressed(_action_binding.control.vector2_4.neg_x, _data) ? -1 : _device_handler.checkReleased(_action_binding.control.vector2_4.x, _data) || _device_handler.checkReleased(_action_binding.control.vector2_4.x, _data) ? 0 : _action_binding.last_state.vector2_state.x;
                vect.second = _device_handler.checkPressed(_action_binding.control.vector2_4.y, _data) ? 1 : _device_handler.checkPressed(_action_binding.control.vector2_4.neg_y, _data) ? -1 : _device_handler.checkReleased(_action_binding.control.vector2_4.y, _data) || _device_handler.checkReleased(_action_binding.control.vector2_4.y, _data) ? 0 : _action_binding.last_state.vector2_state.y;

                if (vect.first != _action_binding.last_state.vector2_state.x || vect.second != _action_binding.last_state.vector2_state.y)
                {
                    createVector2Event(_action_binding, mod_active, vect.first, vect.second);
                }
                
                break;
            }
        
        default: ;
    }    
}

