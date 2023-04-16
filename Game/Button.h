#pragma once
#include "GameObject2D.h"
#include "Window.h"
#include "Event.h"

class Button :public GameObject2D
{
public:
	Button(ID3D11Device* _GD, GameObject2D* _parent, GameObject2D* _toggle);
	Button(ID3D11Device* _GD, GameObject2D* _parent);
	virtual ~Button();

	virtual void Tick(GameData* _GD);
	virtual void Draw(DrawData2D* _DD);

	void SetBounds();
	void SetName(string _name);
	void SetType(EventType _event_type);
	void SetToggle(GameObject2D* toggle);

	void toggle();

	float differenceX;
	float differenceY;
	
	string buttonName = "Button";
	EventType event_type;
	
	bool pressed = false;

protected:
	Rectangle bounds;

	GameObject2D* parentWindow;

	GameObject2D* toggleWindow;
	

	ID3D11ShaderResourceView* m_pTextureRV;
};
