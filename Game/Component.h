#pragma once
#include <vector>
#include <memory>
#include "SimpleMath.h"

class Component
{
   void update();
};


struct rotation
{
    float x,y,z;
};


struct Transform : Component {
    Vector3 position{};
    Vector3 rotation{};
    Vector3 scale{};
    
    std::unique_ptr<Transform> parent;
    std::vector<std::unique_ptr<Transform>> children;
};

