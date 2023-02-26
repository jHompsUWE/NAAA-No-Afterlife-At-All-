#pragma once
#include "GameStateBase.h"
class GameMenu :
    public GameStateBase
{
public:
    bool init() override;
    void reset() override;
    State update() override;
    void render() override;
private:
};

