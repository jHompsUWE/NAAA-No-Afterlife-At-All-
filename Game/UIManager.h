#pragma once

#include "GameObject2D.h"
#include "UIRemote.h"
#include "Window.h"
#include "Button.h"
#include "Manager.h"


class UIManager : public Manager
{
public:
	UIManager(ID3D11Device* _ID, GameData* _GD);
	~UIManager();

	virtual void awake() override;
	virtual void update(GameData& _game_data) override;
	//virtual void lateUpdate(GameData& _game_data) override;

	void Draw(DrawData2D* _DD);

	//General remote
	UIRemote* remote;

	//View windows
	std::array<Window*, 6> viewWindows;

private:
	ID3D11Device* m_ID;
	GameData* m_GD;
};

