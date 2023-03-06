#pragma once
#include <vector>
#include <memory>
#include "SimpleMath.h"

enum ComponentType
{
    TRANSFORM = 0,
    GRIDLOCATION = 1
};

class Component
{
   void update();
};

class Transform : public Component
{
public:
    Transform();
    DirectX::SimpleMath::Vector3 position{0,0,0};
    DirectX::SimpleMath::Vector3 rotation{0,0,0};
    DirectX::SimpleMath::Vector3 scale{1,1,1};
    
    void update();

    std::shared_ptr<Transform> parent;
    std::vector<std::shared_ptr<Component>> children;
};



