#pragma once
#include "Button.h"
#include "BuildingWindow.h"
#include "Event.h"

class ButtonOpenBW :public Button
{
public:
	ButtonOpenBW(ID3D11Device* _GD, GameObject2D* _parent);
	ButtonOpenBW(ID3D11Device* _GD, GameObject2D* _parent, string _name, Vector2 _scale, Vector2 _position, EventType _type);
	virtual ~ButtonOpenBW();

	void SetToggle(BuildingWindow* toggle);

	BuildingWindow* GetToggle();
	void toggle();


protected:
	BuildingWindow* toggleWindow;
};


