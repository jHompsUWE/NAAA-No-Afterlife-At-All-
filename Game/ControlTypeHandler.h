#pragma once

#include "GameManager.h"
#include "GameData.h"
#include "DeviceHandler.h"
#include "InputBindingData.h"
#include "Debug.h"


class ControlTypeHandler
{
public:
    virtual ~ControlTypeHandler() = default;
    virtual void check(DeviceHandler& _device_handler, DeviceHandler& _mod_device_handler,
                       ActionBinding& _action_binding, const GameData& _data) = 0;
};

class ButtonControlTypeHandler : public ControlTypeHandler
{
public:
    void check(DeviceHandler& _device_handler, DeviceHandler& _mod_device_handler, ActionBinding& _action_binding,
               const GameData& _data) override;
};

class AxisControlTypeHandler : public ControlTypeHandler
{
public:
    void check(DeviceHandler& _device_handler, DeviceHandler& _mod_device_handler, ActionBinding& _action_binding,
               const GameData& _data) override;
};

class Vector2ControlTypeHandler : public ControlTypeHandler
{
public:
    void check(DeviceHandler& _device_handler, DeviceHandler& _mod_device_handler, ActionBinding& _action_binding,
               const GameData& _data) override;
};

class Vector2_4ControlTypeHandler : public ControlTypeHandler
{
public:
    void check(DeviceHandler& _device_handler, DeviceHandler& _mod_device_handler, ActionBinding& _action_binding,
               const GameData& _data) override;
};


static void createButtonEvent( ActionBinding& _action_binding, bool _mod_active, bool _down, LastButtonState _state)
{
    _action_binding.last_state.button_state = _state;
    
    Event event{};
    event.priority = 1;
    event.type = _action_binding.event_type;
    event.payload.input_button_data.down = _down;
    event.payload.input_button_data.mod_active = _mod_active;
    GameManager::get()->getEventManager()->triggerEvent(std::make_shared<Event>(event));
}

static void createAxisEvent(ActionBinding& _action_binding, bool _mod_active, float _value)
{
    _action_binding.last_state.axis_state.value = _value;
    
    Event event{};
    event.priority = 1;
    event.type = _action_binding.event_type;
    event.payload.input_axis_data.value = _value;
    event.payload.input_axis_data.mod_active = _mod_active;
    GameManager::get()->getEventManager()->triggerEvent(std::make_shared<Event>(event));
}

static void createVector2Event(ActionBinding& _action_binding, bool _mod_active,  float _x, float _y)
{
    _action_binding.last_state.vector2_state.x = _x;
    _action_binding.last_state.vector2_state.y = _y;
    
    Event event{};
    event.priority = 1;
    event.type = _action_binding.event_type;
    event.payload.input_vector2_data.x = _x;
    event.payload.input_vector2_data.y = _y;
    event.payload.input_vector2_data.mod_active = _mod_active;
    GameManager::get()->getEventManager()->triggerEvent(std::make_shared<Event>(event));
}
