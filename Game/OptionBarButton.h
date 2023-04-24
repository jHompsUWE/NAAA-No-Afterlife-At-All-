#pragma once
#include "Button.h"
#include "TextGO2D.h"
#include "Window.h"

class OptionBarButton : public Button
{
public:
	OptionBarButton(ID3D11Device* _GD, float xi, string text);
	~OptionBarButton();

	virtual void Tick(GameData* _GD) override;
	virtual void Draw(DrawData2D* _DD);

	void Toggle();

	void SetHover(bool hoveredOver);

	void setToggle(Window* _toggle);
	void setText(string _string);

	TextGO2D* buttonText;
	bool hover = false;

	Window* toggle;

	Rectangle bounds;
};

