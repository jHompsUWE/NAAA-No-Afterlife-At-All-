#pragma once

/*
#include "Event.h"
#include "InputBindingData.h"
#include "DeviceHandler.h"
#include "ControlTypeHandler.h"

class InputAction
{
public:
    InputAction(EventType _event_type, InteractionType _interaction_type, ModifierType _mod_type, ButtonControl _mod, Control _control) :
    action_binding{_event_type, _interaction_type, _mod_type, _mod,_control} {};

    ~InputAction() = default;

    void check(const GameData& _data)
    {
        control_type_handler->check(*control_device_handler, *mod_device_handler,
            action_binding, _data);
    }

    void setDeviceHandler(std::shared_ptr<DeviceHandler> _device_handler)
    {
        control_device_handler = _device_handler;
    }

    void setModDeviceHandler(std::shared_ptr<DeviceHandler> _device_handler)
    {
        control_device_handler = _device_handler;
    }

    void setControlTypeHandler(std::shared_ptr<ControlTypeHandler> _control_type_handler)
    {
        control_type_handler = _control_type_handler;
    }

private:
    ActionBinding action_binding{};

    std::shared_ptr<ControlTypeHandler> control_type_handler = nullptr;
    std::shared_ptr<DeviceHandler> control_device_handler = nullptr;
    std::shared_ptr<DeviceHandler> mod_device_handler = nullptr;
};

