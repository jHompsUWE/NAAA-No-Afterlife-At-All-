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

std::pair<float, float> MouseDeviceHandler::getVector2(const BindingType& _binding_type, const GameData& _data)
{
    switch (_binding_type.mouse_input)
    {
        case MouseInput::MOVE: 
        {
            return std::pair<float, float >{_data.m_MS.x - _data.m_MS_last.x, _data.m_MS.y - _data.m_MS_last.y};
        }
        default: std::pair<float, float>{0,0};
    }
}

bool ControllerDeviceHandler::checkPressed(const BindingType& _binding_type, const GameData& _data)
{
switch (_binding_type.controller_input)
    {
    case ControllerInput::A:
        {
            return _data.m_GP_buttons.a == GamePad::ButtonStateTracker::PRESSED;
        }
    case ControllerInput::B: 
        {
            return _data.m_GP_buttons.b == GamePad::ButtonStateTracker::PRESSED;
        }
    case ControllerInput::X: 
        {
            return _data.m_GP_buttons.x == GamePad::ButtonStateTracker::PRESSED;
        }
    case ControllerInput::Y: 
        {
            return _data.m_GP_buttons.y == GamePad::ButtonStateTracker::PRESSED;
        }
    case ControllerInput::LEFT_STICK: 
        {
            return _data.m_GP_buttons.leftStick == GamePad::ButtonStateTracker::PRESSED;
        }
    case ControllerInput::RIGHT_STICK: 
        {
            return _data.m_GP_buttons.rightStick == GamePad::ButtonStateTracker::PRESSED;
        }
    case ControllerInput::LEFT_SHOULDER: 
        {
            return _data.m_GP_buttons.leftShoulder == GamePad::ButtonStateTracker::PRESSED;
        }
    case ControllerInput::RIGHT_SHOULDER: 
        {
            return _data.m_GP_buttons.rightShoulder == GamePad::ButtonStateTracker::PRESSED;
        }
    case ControllerInput::BACK: 
        {
            return _data.m_GP_buttons.back == GamePad::ButtonStateTracker::PRESSED;
        }
    case ControllerInput::START: 
        {
            return _data.m_GP_buttons.start == GamePad::ButtonStateTracker::PRESSED;
        }
    case ControllerInput::D_UP: 
        {
            return _data.m_GP_buttons.dpadUp == GamePad::ButtonStateTracker::PRESSED;
        }
    case ControllerInput::D_DOWN: 
        {
            return _data.m_GP_buttons.dpadDown == GamePad::ButtonStateTracker::PRESSED;
        }
    case ControllerInput::D_RIGHT: 
        {
            return _data.m_GP_buttons.dpadRight == GamePad::ButtonStateTracker::PRESSED;
        }
    case ControllerInput::D_LEFT: 
        {
            return _data.m_GP_buttons.dpadLeft == GamePad::ButtonStateTracker::PRESSED;
        }
        
    default: return false;
    }
}

bool ControllerDeviceHandler::checkReleased(const BindingType& _binding_type, const GameData& _data)
{
    switch (_binding_type.controller_input)
    {
    case ControllerInput::A:
        {
            return _data.m_GP_buttons.a == GamePad::ButtonStateTracker::RELEASED;
        }
    case ControllerInput::B: 
        {
            return _data.m_GP_buttons.b == GamePad::ButtonStateTracker::RELEASED;
        }
    case ControllerInput::X: 
        {
            return _data.m_GP_buttons.x == GamePad::ButtonStateTracker::RELEASED;
        }
    case ControllerInput::Y: 
        {
            return _data.m_GP_buttons.y == GamePad::ButtonStateTracker::RELEASED;
        }
    case ControllerInput::LEFT_STICK: 
        {
            return _data.m_GP_buttons.leftStick == GamePad::ButtonStateTracker::RELEASED;
        }
    case ControllerInput::RIGHT_STICK: 
        {
            return _data.m_GP_buttons.rightStick == GamePad::ButtonStateTracker::RELEASED;
        }
    case ControllerInput::LEFT_SHOULDER: 
        {
            return _data.m_GP_buttons.leftShoulder == GamePad::ButtonStateTracker::RELEASED;
        }
    case ControllerInput::RIGHT_SHOULDER: 
        {
            return _data.m_GP_buttons.rightShoulder == GamePad::ButtonStateTracker::RELEASED;
        }
    case ControllerInput::BACK: 
        {
            return _data.m_GP_buttons.back == GamePad::ButtonStateTracker::RELEASED;
        }
    case ControllerInput::START: 
        {
            return _data.m_GP_buttons.start == GamePad::ButtonStateTracker::RELEASED;
        }
    case ControllerInput::D_UP: 
        {
            return _data.m_GP_buttons.dpadUp == GamePad::ButtonStateTracker::RELEASED;
        }
    case ControllerInput::D_DOWN: 
        {
            return _data.m_GP_buttons.dpadDown == GamePad::ButtonStateTracker::RELEASED;
        }
    case ControllerInput::D_RIGHT: 
        {
            return _data.m_GP_buttons.dpadRight == GamePad::ButtonStateTracker::RELEASED;
        }
    case ControllerInput::D_LEFT: 
        {
            return _data.m_GP_buttons.dpadLeft == GamePad::ButtonStateTracker::RELEASED;
        }
        
    default: return false;
    }
}

bool ControllerDeviceHandler::checkHeld(const BindingType& _binding_type, const GameData& _data)
{
        switch (_binding_type.controller_input)
    {
    case ControllerInput::A:
        {
            return _data.m_GP_buttons.a == GamePad::ButtonStateTracker::HELD;
        }
    case ControllerInput::B: 
        {
            return _data.m_GP_buttons.b == GamePad::ButtonStateTracker::HELD;
        }
    case ControllerInput::X: 
        {
            return _data.m_GP_buttons.x == GamePad::ButtonStateTracker::HELD;
        }
    case ControllerInput::Y: 
        {
            return _data.m_GP_buttons.y == GamePad::ButtonStateTracker::HELD;
        }
    case ControllerInput::LEFT_STICK: 
        {
            return _data.m_GP_buttons.leftStick == GamePad::ButtonStateTracker::HELD;
        }
    case ControllerInput::RIGHT_STICK: 
        {
            return _data.m_GP_buttons.rightStick == GamePad::ButtonStateTracker::HELD;
        }
    case ControllerInput::LEFT_SHOULDER: 
        {
            return _data.m_GP_buttons.leftShoulder == GamePad::ButtonStateTracker::HELD;
        }
    case ControllerInput::RIGHT_SHOULDER: 
        {
            return _data.m_GP_buttons.rightShoulder == GamePad::ButtonStateTracker::HELD;
        }
    case ControllerInput::BACK: 
        {
            return _data.m_GP_buttons.back == GamePad::ButtonStateTracker::HELD;
        }
    case ControllerInput::START: 
        {
            return _data.m_GP_buttons.start == GamePad::ButtonStateTracker::HELD;
        }
    case ControllerInput::D_UP: 
        {
            return _data.m_GP_buttons.dpadUp == GamePad::ButtonStateTracker::HELD;
        }
    case ControllerInput::D_DOWN: 
        {
            return _data.m_GP_buttons.dpadDown == GamePad::ButtonStateTracker::HELD;
        }
    case ControllerInput::D_RIGHT: 
        {
            return _data.m_GP_buttons.dpadRight == GamePad::ButtonStateTracker::HELD;
        }
    case ControllerInput::D_LEFT: 
        {
            return _data.m_GP_buttons.dpadLeft == GamePad::ButtonStateTracker::HELD;
        }
        
    default: return false;
    }
}

float ControllerDeviceHandler::getAxis(const BindingType& _binding_type, const GameData& _data)
{
    switch (_binding_type.controller_input)
    {
        case ControllerInput::LEFT_TRIGGER:
            {
                return _data.m_GP_state.triggers.left;
            }
        case ControllerInput::RIGHT_TRIGGER: 
            {
                return _data.m_GP_state.triggers.right;
            }
        
        default: return 0.0f;
    }
}

std::pair<float, float> ControllerDeviceHandler::getVector2(const BindingType& _binding_type, const GameData& _data)
{
    switch (_binding_type.controller_input)
    {
        case ControllerInput::LEFT_STICK_VECT:
            {
                return std::pair<float, float>{_data.m_GP_state.thumbSticks.leftX, _data.m_GP_state.thumbSticks.leftY};
            }
        case ControllerInput::RIGHT_STICK_VECT: 
            {
                return std::pair<float, float>{_data.m_GP_state.thumbSticks.rightX, _data.m_GP_state.thumbSticks.rightY};
            }

    default: std::pair<float, float>{0,0};
    }
}
