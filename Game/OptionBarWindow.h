#pragma once
#include "Window.h"
#include "OptionBarButton.h"
#include <vector>

class OptionBarWindow : public Window
{
public:
	OptionBarWindow(ID3D11Device* _GD, int buttonNum, Vector2 pos);
	~OptionBarWindow();

	virtual void Tick(GameData* _GD) override;
	virtual void Draw(DrawData2D* _DD) override;

	void SetButtonText(int button, string text);
	void SetButtonBounds();

	std::vector <OptionBarButton*> buttons;

	OptionBarButton* hovered;

	//bool renderable = false;

};