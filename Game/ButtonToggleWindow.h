#pragma once
#include "Button.h"

class ButtonToggleWindow : public Button
{
public:
	ButtonToggleWindow(ID3D11Device* _GD, GameObject2D* _parent);
	ButtonToggleWindow(ID3D11Device* _GD, GameObject2D* _parent, string _name, Vector2 _scale, Vector2 _position, EventType _type);
	virtual ~ButtonToggleWindow();

	void SetToggle(Window* toggle);
	void Toggle();

protected:
	Window* toggleWindow;
};

