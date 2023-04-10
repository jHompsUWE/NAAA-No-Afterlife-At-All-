#pragma once

#include "GameData.h"
#include "InputBindingData.h"

class DeviceHandler
{
public:
    virtual ~DeviceHandler() = default;
    virtual bool checkPressed(const BindingType& _binding_type, const GameData& _data) = 0;
    virtual bool checkReleased(const BindingType& _binding_type, const GameData& _data) = 0;
    virtual bool checkHeld(const BindingType& _binding_type, const GameData& _data) = 0;
    virtual float getAxis(const BindingType& _binding_type, const GameData& _data) {return 0.0f;};
    virtual std::pair<float, float> getVector2(const BindingType& _binding_type, const GameData& _data) {return {0,0};};
};

class KeyboardDeviceHandler : public DeviceHandler
{
public:
    bool checkPressed(const BindingType& _binding_type, const GameData& _data) override;
    bool checkReleased(const BindingType& _binding_type, const GameData& _data) override;
    bool checkHeld(const BindingType& _binding_type, const GameData& _data) override;
};

class MouseDeviceHandler : public DeviceHandler
{
public:
    bool checkPressed(const BindingType& _binding_type, const GameData& _data) override;
    bool checkReleased(const BindingType& _binding_type, const GameData& _data) override;
    bool checkHeld(const BindingType& _binding_type, const GameData& _data) override;
    float getAxis(const BindingType& _binding_type, const GameData& _data) override;
};

class ControllerDeviceHandler : public DeviceHandler
{
public:
    bool checkPressed(const BindingType& _binding_type, const GameData& _data) override;
    bool checkReleased(const BindingType& _binding_type, const GameData& _data) override;
    bool checkHeld(const BindingType& _binding_type, const GameData& _data) override;
    float getAxis(const BindingType& _binding_type, const GameData& _data) override;
    std::pair<float, float> getVector2(const BindingType& _binding_type, const GameData& _data) override;
};
