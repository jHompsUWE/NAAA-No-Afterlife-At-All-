#pragma once
#include "GameStateBase.h"
#include "EventManager.h"
#include "FileManager.h"
#include "EconomyManager.h"
#include "TileGO.h"
#include "WorldManager.h"
#include "VBQuad.h"

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
    GamePlay(State _state, GameData* _GD, DrawData* _DD, DrawData2D* _DD2D, DirectX::IEffectFactory* _fxFactory,
        const Microsoft::WRL::ComPtr<ID3D11Device1>& m_d3dDevice)
        : GameStateBase(_state, _GD, _DD, _DD2D, _fxFactory, m_d3dDevice)
    {
        
    }


    bool init(HWND _window, int _width, int _height, GameData* _game_data) override;
    void reset() override;
    State update(GameData& _game_data) override;
    State lateUpdate(GameData& _game_data) override;
    void render3D() override;
    void render2D() override;

private:
    //Basic 3D renderers
    //Camera* m_cam = NULL; //principle camera
    TPSCamera* m_TPScam = NULL;//TPS cam
    Light* m_light = NULL; //base light
    
    std::shared_ptr<EventManager> event_manager;
    std::shared_ptr<EconomyManager> economy_manager_;
    std::shared_ptr<FileManager> file_manager_;
    std::shared_ptr<WorldManager> world_manager;

    
};
