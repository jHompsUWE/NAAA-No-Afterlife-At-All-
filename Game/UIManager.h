#pragma once

#include "GameObject2D.h"
#include "UIRemote.h"
#include "WindowDraggable.h"
#include "Button.h"
#include "Manager.h"
#include "BuildingWindow.h"


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
	std::array<WindowDraggable*, 6> viewWindows;

	std::array<BuildingWindow*, 3> buildWindows;

private:
	ID3D11Device* m_ID;
	GameData* m_GD;
};

