#pragma once
#include "Component.h"
#include "CommonStates.h"
#include "SimpleMath.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

class Camera;
struct ID3D11DeviceContext;
struct GameData;
struct DrawData;

class GameObject
{
public:
    GameObject(Transform transform = {});                                           // constructors to add stuff
    GameObject(Vector3 pos = {},Vector3 rotation = {},Transform* parent = nullptr); 
    GameObject(Transform* parent,Vector3 offset = {});

    virtual void fixedUpdate    (GameData* _GD); // physics
    virtual void update         (GameData* _GD); // normal
    virtual void lateUpdate     (GameData* _GD); // anything that needs update to finish

    virtual void render         (DrawData* _DD); // render call

protected:

    std::vector<std::unique_ptr<Component>> m_components; // components attached list;

};