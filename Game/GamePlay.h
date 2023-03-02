#pragma once
#include "GameStateBase.h"
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

