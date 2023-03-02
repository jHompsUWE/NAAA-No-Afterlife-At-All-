#pragma once


#include <array>
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
    GameObject(std::shared_ptr<Transform> transform = {});        // constructors to add stuff
    GameObject(Vector3 pos = {0,0,0}, Vector3 rotation = {0,0,0}, Vector3 scale = {1,1,1}, std::shared_ptr<Transform> parent = nullptr);
    GameObject(std::shared_ptr<Transform> parent,Vector3 offset = {0,0,0});

    virtual void fixedUpdate    (GameData* _GD); // physics
    virtual void update         (GameData* _GD); // normal
    virtual void lateUpdate     (GameData* _GD); // anything that needs update to finish

    virtual void render         (DrawData* _DD); // render call

protected:

    std::array<std::shared_ptr<Component>,5> m_components; // components attached list;

};