#pragma once
#include "Button.h"
#include "TextGO2D.h"
#include "Window.h"

class OptionBarButton : public Button
{
public:
	OptionBarButton(ID3D11Device* _GD, Vector2 pos, string text);
	~OptionBarButton();

	virtual void Tick(GameData* _GD) override;
	virtual void Draw(DrawData2D* _DD);
	void onEvent(const Event& event) override;

	void Toggle(bool toggleOn);

	void SetHover(bool hoveredOver);

	void setToggle(Window* _toggle);
	void setText(string _string);
	void centreText();

	TextGO2D* buttonText;
	bool hover = false;

	Window* toggle;

	Rectangle bounds;
};

