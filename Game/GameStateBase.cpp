#include "pch.h"
#include "GameStateBase.h"
#include "GameData.h"
#include "DrawData.h"
#include "DrawData2D.h"
#include "VBGO.h"

GameStateBase::GameStateBase()
{
	m_state = State::GAME_UNKNOWN;
}

GameStateBase::GameStateBase(State _state)
{
	m_state = _state;
}

GameStateBase::GameStateBase(State _state, GameData* _GD, DrawData* _DD, DrawData2D* _DD2D,
                             DirectX::IEffectFactory* _fxFactory, Microsoft::WRL::ComPtr<ID3D11Device1> _d3dDevice)
{
	m_state = _state;
	m_GD = _GD;
	m_DD = _DD;
	m_DD2D = _DD2D;
	m_fxFactory = _fxFactory;
	m_d3dDevice = _d3dDevice;
}

GameStateBase::~GameStateBase()
{
	//m_GD = nullptr;
	//m_DD = nullptr;
	//m_DD2D = nullptr;
}

bool GameStateBase::init(HWND _window, int _width, int _height)
{
	float AR = (float)_width / (float)_height;
	m_TPScam = new TPSCamera(5.25f * XM_PI, AR, -10000.0f, 10000.0f, Vector3(50.0f, 0.0f, 50.0f), Vector3::UnitY, Vector3(0.0f, 0.0f, 0.0f), Vector3(10.0f, tan(30.0f * XM_PI / 180.0f) * sqrt(200.0f),10.0f));
	m_GameObjects.push_back(m_TPScam);
	return true;
}

void GameStateBase::reset()
{

}

State GameStateBase::update(GameData& _game_data)
{
	for (list<GameObject*>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
	{
		(*it)->Tick(m_GD);
	}
	for (list<GameObject2D*>::iterator it = m_GameObjects2D.begin(); it != m_GameObjects2D.end(); it++)
	{
		(*it)->Tick(m_GD);
	}
	return m_state;
}

State GameStateBase::lateUpdate(GameData& _game_data)
{
	return m_state;
}

void GameStateBase::render3D()
{
	//
	m_DD->m_cam = m_TPScam;
	VBGO::UpdateConstantBuffer(m_DD);
	for (list<GameObject*>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
	{
		(*it)->Draw(m_DD);
	}
}

void GameStateBase::render2D()
{
	for (list<GameObject2D*>::iterator it = m_GameObjects2D.begin(); it != m_GameObjects2D.end(); it++)
	{
		(*it)->Draw(m_DD2D);
	}
}

