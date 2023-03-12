#pragma once
#include "GameStateBase.h"
class GameTutorial :
    public GameStateBase
{
public:
    GameTutorial(State _state, GameData* _GD, DrawData* _DD, DrawData2D* _DD2D, DirectX::IEffectFactory* _fxFactory,
        const Microsoft::WRL::ComPtr<ID3D11Device1>& m_d3dDevice)
        : GameStateBase(_state, _GD, _DD, _DD2D, _fxFactory, m_d3dDevice)
    {
        
    }
    bool init(HWND _window, int _width, int _height) override;
    void reset() override;
    State update(DX::StepTimer const& _timer) override;
    State lateUpdate(DX::StepTimer const& _timer) override;
    void render3D() override;
    void render2D() override;

private:
};

