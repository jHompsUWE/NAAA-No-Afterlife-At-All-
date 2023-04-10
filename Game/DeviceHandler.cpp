#include "pch.h"
#include "DeviceHandler.h"

bool KeyboardDeviceHandler::checkPressed(const BindingType& _binding_type, const GameData& _data)
{
    return _data.m_KBS_tracker.IsKeyPressed(_binding_type.key);
}

bool KeyboardDeviceHandler::checkReleased(const BindingType& _binding_type, const GameData& _data)
{
    return _data.m_KBS_tracker.IsKeyReleased(_binding_type.key);
}

bool KeyboardDeviceHandler::checkHeld(const BindingType& _binding_type, const GameData& _data)
{
    return _data.m_KBS.IsKeyDown(_binding_type.key);
}

bool MouseDeviceHandler::checkPressed(const BindingType& _binding_type, const GameData& _data)
{
    switch (_binding_type.mouse_input)
    {
        case MouseInput::LEFT_BUTTON:
            {
                return _data.m_mouseButtons.leftButton == Mouse::ButtonStateTracker::PRESSED ? true : false;
            }
        case MouseInput::MIDDLE_BUTTON: 
            {
                return _data.m_mouseButtons.middleButton == Mouse::ButtonStateTracker::PRESSED ? true : false;
            }
        case MouseInput::RIGHT_BUTTON: 
            {
                return _data.m_mouseButtons.rightButton == Mouse::ButtonStateTracker::PRESSED ? true : false;
            }

    default: ;
    }
}

bool MouseDeviceHandler::checkReleased(const BindingType& _binding_type, const GameData& _data)
{
    switch (_binding_type.mouse_input)
    {
    case MouseInput::LEFT_BUTTON:
        {
            return _data.m_mouseButtons.leftButton == Mouse::ButtonStateTracker::RELEASED ? true : false;
        }
    case MouseInput::MIDDLE_BUTTON: 
        {
            return _data.m_mouseButtons.middleButton == Mouse::ButtonStateTracker::RELEASED ? true : false;
        }
    case MouseInput::RIGHT_BUTTON: 
        {
            return _data.m_mouseButtons.rightButton == Mouse::ButtonStateTracker::RELEASED ? true : false;
        }

    default: ;
    }
}

bool MouseDeviceHandler::checkHeld(const BindingType& _binding_type, const GameData& _data)
{
    switch (_binding_type.mouse_input)
    {
    case MouseInput::LEFT_BUTTON:
        {
            return _data.m_mouseButtons.leftButton == Mouse::ButtonStateTracker::HELD ? true : false;
        }
    case MouseInput::MIDDLE_BUTTON: 
        {
            return _data.m_mouseButtons.middleButton == Mouse::ButtonStateTracker::HELD ? true : false;
        }
    case MouseInput::RIGHT_BUTTON: 
        {
            return _data.m_mouseButtons.rightButton == Mouse::ButtonStateTracker::HELD ? true : false;
        }

    default: ;
    }
}

float MouseDeviceHandler::getAxis(const BindingType& _binding_type, const GameData& _data)
{
    switch (_binding_type.mouse_input)
    {
        case MouseInput::SCROLL: 
        {
            float value = (float)_data.m_MS.scrollWheelValue;
            Mouse::Get().ResetScrollWheelValue();
            return value;
        }
        default: ;
    }
}

bool ControllerDeviceHandler::checkPressed(const BindingType& _binding_type, const GameData& _data)
{
    switch (_binding_type.controller_input)
    {
        case ControllerInput::A:
            {
                return _data.m_GP_state.IsAPressed();
            }
        case ControllerInput::B: 
            {
                return _data.m_GP_state.IsBackPressed();
            }
        case ControllerInput::X: 
            {
                return _data.m_GP_state.IsXPressed();
            }
        case ControllerInput::Y: 
            {
                return _data.m_GP_state.IsYPressed();
            }
        case ControllerInput::LEFT_STICK: 
            {
                return _data.m_GP_state.IsLeftStickPressed();
            }
        case ControllerInput::RIGHT_STICK: 
            {
                return _data.m_GP_state.IsRightStickPressed();
            }
        case ControllerInput::BACK: 
            {
                return _data.m_GP_state.IsBackPressed();
            }
        case ControllerInput::START: 
            {
                return _data.m_GP_state.IsStartPressed();
            }
        case ControllerInput::D_UP: 
            {
                return _data.m_GP_state.IsDPadUpPressed();
            }
        case ControllerInput::D_DOWN: 
            {
                return _data.m_GP_state.IsDPadDownPressed();
            }
        case ControllerInput::D_RIGHT: 
            {
                return _data.m_GP_state.IsDPadRightPressed();
            }
        case ControllerInput::D_LEFT: 
            {
                return _data.m_GP_state.IsDPadLeftPressed();
            }
        
        default: ;
    }
}

bool ControllerDeviceHandler::checkReleased(const BindingType& _binding_type, const GameData& _data)
{
    
}

bool ControllerDeviceHandler::checkHeld(const BindingType& _binding_type, const GameData& _data)
{
    
}

std::pair<float, float> ControllerDeviceHandler::getVector2(const BindingType& _binding_type, const GameData& _data)
{
    
}
