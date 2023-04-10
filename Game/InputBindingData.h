#pragma once

#include "Event.h"

enum class InteractionType
{
    BUTTON_PRESSED,
    BUTTON_RELEASED,
    BUTTON_HELD,
    BUTTON_PRESSED_RELEASED,
    AXIS, // such as scroll wheel and controller triggers. 
    VECTOR2 // such as joystick and mouse position/delta.
};

enum class ModifierType
{
    NONE,
    HELD
};

enum class ControlType
{
    BUTTON,
    AXIS,
    VECTOR2,
    VECTOR2_4
};

enum class Device
{
    KEYBOARD,
    MOUSE,
    CONTROLLER
};

enum class MouseInput
{
    LEFT_BUTTON,
    MIDDLE_BUTTON,
    RIGHT_BUTTON,
    MOVE,
    SCROLL
};

enum class ControllerInput
{
    A,
    B,
    X,
    Y,

    LEFT_STICK,
    RIGHT_STICK,
    LEFT_SHOULDER,
    RIGHT_SHOULDER,

    BACK,
    START,

    D_UP,
    D_DOWN,
    D_RIGHT,
    D_LEFT,

    LEFT_STICK_VECT,
    RIGHT_STICK_VECT,

    LEFT_TRIGGER,
    RIGHT_TRIGGER
};

enum class LastButtonState
{
    PRESSED,
    RELEASED,
    DOWN,
    UP
};

struct LastAxisState
{
    float value = NULL;
};

struct LastVector2State
{
    float x = NULL;
    float y = NULL;
};

union LastState
{
    LastButtonState button_state = LastButtonState::UP;
    LastAxisState axis_state;
    LastVector2State vector2_state;
};

union BindingType
{
    Keyboard::Keys key;
    MouseInput mouse_input;
    ControllerInput controller_input;
};

struct Vector2_4Control
{
    BindingType x;
    BindingType neg_x;
    BindingType y;
    BindingType neg_y;
};

struct Vector2Control
{
    BindingType x;
};

struct AxisControl
{
    BindingType x;
    BindingType neg_x;
};

struct ButtonControl
{
    BindingType x;
};

union Control
{
    Vector2_4Control vector2_4;
    Vector2Control vector2;
    AxisControl axis;
    ButtonControl button;
};

struct ActionBinding
{
    EventType event_type;
    InteractionType interaction_type;
    ModifierType mod_type = ModifierType::NONE;
    
    ButtonControl mod;
    Control control;

    LastState last_state;
};

