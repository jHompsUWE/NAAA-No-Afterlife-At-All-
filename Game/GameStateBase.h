#pragma once

struct GameData;
struct DrawData;
struct DrawData2D;

enum class State
{
	GAME_UNKNOWN = -1,
	GAME_EXIT = 0,
	GAME_MENU = 1,
	GAME_PLAY = 2,
	GAME_PAUSED = 3,
	GAME_TUTORIAL = 4,
	GAME_OVER
};

class GameStateBase
{
public:
	GameStateBase();
	GameStateBase(State _state);
	GameStateBase(State _state, GameData* _GD, DrawData* _DD, DrawData2D* _DD2D);
	~GameStateBase();

	virtual bool init();
	virtual void reset();
	virtual State update();
	virtual void render();

protected:
	State m_state;
	GameData* m_GD = NULL;
	DrawData* m_DD = NULL;
	DrawData2D* m_DD2D = NULL;
};

