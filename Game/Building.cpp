#include "pch.h"
#include "Building.h"
#include <iostream>

Building::Building()
{

}

Building::Building(Microsoft::WRL::ComPtr<ID3D11DeviceContext1> _device, Vector3 _pos)
{
    float* params = new float[3];
    params[0] = 100.0f; params[1] = (size_t)8;
    m_shape = new GPGO(_device.Get(), GPGO_CUBE, (float*)&Colors::Green, params, _pos);

    std::cout << "Created building" << std::endl;
}

Building::~Building()
{

}

BuildingData& Building::getBuildingData()
{
    return m_building_data;
}

GPGO& Building::getShape()
{
    return *m_shape;
}

void Building::Draw(DrawData* _DD)
{
    if (m_shape)
    {
        m_shape->Draw(_DD);
    }
}