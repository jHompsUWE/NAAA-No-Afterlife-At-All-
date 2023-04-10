#pragma once

#include "GameManager.h"
#include "GameData.h"
#include "DeviceHandler.h"
#include "InputBindingData.h"

/*
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


static void createButtonEvent(const ActionBinding& _action_binding, bool _mod_active, bool _down)
{
    Event event{};
    event.priority = 1;
    event.type = _action_binding.event_type;
    event.payload.input_button_data.down = _down;
    GameManager::get()->getEventManager()->triggerEvent(std::make_shared<Event>(event));
}

static void createAxisEvent(const ActionBinding& _action_binding, bool _mod_active, float _value)
{
    Event event{};
    event.priority = 1;
    event.type = _action_binding.event_type;
    event.payload.input_axis_data.value = _value;
    GameManager::get()->getEventManager()->triggerEvent(std::make_shared<Event>(event));
}

static void createVector2Event(const ActionBinding& _action_binding, bool _mod_active,  float _x, float _y)
{
    Event event{};
    event.priority = 1;
    event.type = _action_binding.event_type;
    event.payload.input_vector2_data.x = _x;
    event.payload.input_vector2_data.y = _y;
    GameManager::get()->getEventManager()->triggerEvent(std::make_shared<Event>(event));
}
*/