#pragma once
#include "GameObject2D.h"
#include "BuildingWindow.h"
#include "Event.h"

class ButtonOpenBW :public GameObject2D
{
public:
	ButtonOpenBW(ID3D11Device* _GD, GameObject2D* _parent, BuildingWindow* _toggle);
	ButtonOpenBW(ID3D11Device* _GD, GameObject2D* _parent);
	virtual ~ButtonOpenBW();

	virtual void Tick(GameData* _GD);
	virtual void Draw(DrawData2D* _DD);

	void SetBounds();
	void SetName(string _name);
	void SetType(EventType _event_type);
	void SetToggle(BuildingWindow* toggle);

	void toggle();

	float differenceX;
	float differenceY;

	string buttonName = "Button";
	EventType event_type;

	bool pressed = false;

protected:
	Rectangle bounds;

	GameObject2D* parentWindow;

	BuildingWindow* toggleWindow;


	ID3D11ShaderResourceView* m_pTextureRV;
};


