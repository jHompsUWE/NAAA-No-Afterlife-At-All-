#pragma once
#include "GameStateBase.h"
#include "EventManager.h"
#include "FileManager.h"
#include "EconomyManager.h"
#include "TileGO.h"
#include "WorldManager.h"


class GameObject;
class GameObject2D;
class Camera;
class TPSCamera;
class Light;
class Sound;


class GamePlay :
    public GameStateBase
{
public:
    GamePlay(State _state, GameData* _GD, DrawData* _DD, DrawData2D* _DD2D);

    bool init() override;
    void reset() override;
    State update() override;
    void render() override;

private:
};

