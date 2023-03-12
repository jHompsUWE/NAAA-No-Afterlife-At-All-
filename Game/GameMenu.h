#pragma once
#include "GameStateBase.h"
#include "Button.h"
#include "TextGO2D.h"
#include <array>

class GameMenu :
    public GameStateBase
{
public:
    GameMenu(State _state, GameData* _GD, DrawData* _DD, DrawData2D* _DD2D, DirectX::IEffectFactory* _fxFactory,
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
    Button* newGame;
    
    //Non functional buttons
    std::array<Button*, 3> NFButtons;
    std::array<TextGO2D*, 4>ButtonsText;
};

