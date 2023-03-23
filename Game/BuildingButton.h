#pragma once
#include "GameObject2D.h"
#include "TextGO2D.h"
#include "Window.h"
#include "Event.h"

class BuildingButton :public GameObject2D
{
public:
	BuildingButton(ID3D11Device* _GD, GameObject2D* _parent, string _buttonName);
	virtual ~BuildingButton();

	virtual void Tick(GameData* _GD);
	virtual void Draw(DrawData2D* _DD);

	void SetBounds();
	void SetText(bool name, string _name);
	void SetType(EventType _event_type);
	void SetHover(bool _hover);

	void setTextPos();

	void toggle();

	EventType event_type;
	bool hover = false;
	
	TextGO2D* buildName;
	TextGO2D* buildCost;

	Rectangle bounds;

protected:
	

	GameObject2D* parentWindow;
	GameObject2D* toggleWindow;

	ID3D11ShaderResourceView* m_pTextureRV;
};
