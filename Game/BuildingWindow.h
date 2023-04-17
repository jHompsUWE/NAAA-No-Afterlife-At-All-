#pragma once
#include "Window.h"
#include "TextGO2D.h"
#include "ButtonSelectBW.h"
#include <vector>

class BuildingWindow : public Window
{
public:
	BuildingWindow(ID3D11Device* _GD, int numOfButtons);
	~BuildingWindow();

	//virtual void Tick(GameData* _GD) override;
	virtual void Draw(DrawData2D* _DD) override;

	void OpenWindow();
	//void setButtonBounds();

	//std::vector <ButtonSelectBW*> buttons;

protected:

};