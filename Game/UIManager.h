#pragma once

#include "GameObject2D.h"
#include "UIRemote.h"
#include "Window.h"
#include "BuildingWindow.h"
#include "Button.h"
#include "BuildingButton.h"


class UIManager
{
public:
	UIManager(ID3D11Device* _GD);
	~UIManager();

	void awake() ;
	void update(GameData& _game_data);
	void lateUpdate(GameData& _game_data) ;

	void Draw(DrawData2D* _DD);

	//General remote
	UIRemote* remote;

	//View windows
	std::array<Window*, 6> viewWindows;

	//Building windows
	std::array<BuildingWindow*, 3> buildWindows;

private:

};

