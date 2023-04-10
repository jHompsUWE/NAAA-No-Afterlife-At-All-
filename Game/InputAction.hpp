#pragma once

#include "Event.h"
#include "InputBindingData.h"
#include "DeviceHandler.h"
#include "ControlTypeHandler.h"

class InputAction
{
public:
    InputAction(ActionBinding _action_binding) :
    action_binding(_action_binding) {};

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

    void setControlTypeHandler(std::shared_ptr<ControlTypeHandler> _control_type_handler)
    {
        control_type_handler = _control_type_handler;
    }

private:
    ActionBinding action_binding{};

    std::shared_ptr<ControlTypeHandler> control_type_handler;
    std::shared_ptr<DeviceHandler> control_device_handler;
    std::shared_ptr<DeviceHandler> mod_device_handler;
};

