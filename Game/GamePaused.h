#pragma once
#include "GameStateBase.h"
class GamePaused : 
	public GameStateBase
{
public:
	GamePaused(State _state, GameData* _GD, DrawData* _DD, DrawData2D* _DD2D, DirectX::IEffectFactory* _fxFactory,
		const Microsoft::WRL::ComPtr<ID3D11Device1>& m_d3dDevice)
		: GameStateBase(_state, _GD, _DD, _DD2D, _fxFactory, m_d3dDevice)
	{
        
	};
	bool init(HWND _window, int _width, int _height, GameData* _game_data) override;
	void reset() override;
	State update(GameData& _game_data) override;
	State lateUpdate(GameData& _game_data) override;
	void render3D() override;
	void render2D() override;

private:
};

