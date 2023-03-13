#pragma once
#include <list>

#include "gameobject.h"
#include "GameObject2D.h"
#include "Sound.h"
#include "StepTimer.h"
#include "TPSCamera.h"

namespace DirectX
{
	class IEffectFactory;
}

struct GameData;
struct DrawData;
struct DrawData2D;

enum class State
{
	GAME_UNKNOWN = -1,
	GAME_EXIT = 0,
	GAME_MENU,
	GAME_PLAY,
	GAME_PAUSED,
	GAME_TUTORIAL,
	GAME_OVER
};

class GameStateBase
{
public:
	GameStateBase();
	GameStateBase(State _state);
	GameStateBase(State _state, GameData* _GD, DrawData* _DD, DrawData2D* _DD2D ,DirectX::IEffectFactory* _fxFactory , Microsoft::WRL::ComPtr<ID3D11Device1> m_d3dDevice);
	~GameStateBase();

	virtual bool init(HWND _window, int _width, int _height, GameData* _game_data);
	virtual void reset();
	virtual State update(GameData& _game_data);
	virtual State lateUpdate(GameData& _game_data);
	virtual void render3D();
	virtual void render2D();

	TPSCamera& getCam() { return  *m_TPScam; };
	
protected:
	State m_state;
	GameData* m_GD;
	DrawData* m_DD;
	DrawData2D* m_DD2D;

	TPSCamera* m_TPScam = NULL;//TPS cam
	
	DirectX::CommonStates* m_states = NULL;
	DirectX::IEffectFactory* m_fxFactory = NULL;
	Microsoft::WRL::ComPtr<ID3D11Device1> m_d3dDevice = NULL;
	
	std::list<GameObject*> m_GameObjects; //data structure to hold pointers to the 3D Game Objects
	std::list<GameObject2D*> m_GameObjects2D; //data structure to hold pointers to the 2D Game Objects
	std::list<Sound*>m_Sounds;
	
};

