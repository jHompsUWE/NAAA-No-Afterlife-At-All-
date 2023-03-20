#pragma once
#include "Manager.h"
#include "UIRemote.h"


class UIManager : public Manager
{
public:

	virtual void awake() override;
	virtual void update(GameData& _game_data) override;
	virtual void lateUpdate(GameData& _game_data) override;

private:
	UIRemote remote;
};

