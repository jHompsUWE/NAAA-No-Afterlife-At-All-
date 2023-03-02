#include "pch.h"
#include "GameStateBase.h"
#include "GameData.h"
#include "DrawData.h"
#include "DrawData2D.h"

GameStateBase::GameStateBase()
{
	m_state = State::GAME_UNKNOWN;
}

GameStateBase::GameStateBase(State _state)
{
	m_state = _state;
}

GameStateBase::GameStateBase(State _state, GameData* _GD, DrawData* _DD, DrawData2D* _DD2D)
{
	m_state = _state;
	m_GD = _GD;
	m_DD = _DD;
	m_DD2D = _DD2D;
}

GameStateBase::~GameStateBase()
{
	m_GD = nullptr;
	m_DD = nullptr;
	m_DD2D = nullptr;
}

bool GameStateBase::init()
{
	return true;
}

void GameStateBase::reset()
{

}

State GameStateBase::update()
{
	return m_state;
}

void GameStateBase::render()
{

}