#pragma once
#include "GameObject2D.h"
#include "Window.h"

//=================================================================
//Button class based off ImageGO2D class
//Work in progress
// 
//=================================================================

class Button :public GameObject2D
{
public:
	Button(ID3D11Device* _GD, GameObject2D* _parent, Window* _toggle);
	Button(ID3D11Device* _GD, GameObject2D* _parent);
	virtual ~Button();

	virtual void Tick(GameData* _GD);
	virtual void Draw(DrawData2D* _DD);

	void SetBounds();
	void SetName(string _name);

	float differenceX;
	float differenceY;
	
	string buttonName = "Button";
	bool pressed = false;

protected:
	Rectangle bounds;

	GameObject2D* parentWindow;
	Window* toggleWindow;

	ID3D11ShaderResourceView* m_pTextureRV;
};
