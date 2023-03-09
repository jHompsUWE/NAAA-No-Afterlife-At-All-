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
	Button(string _fileName, ID3D11Device* _GD, GameObject2D* parent, Window* toggle);
	virtual ~Button();

	virtual void Tick(GameData* _GD);
	virtual void Draw(DrawData2D* _DD);

	void SetBounds();

	float differenceX;
	float differenceY;

protected:
	Rectangle bounds;

	GameObject2D* parentWindow;
	Window* toggleWindow;

	ID3D11ShaderResourceView* m_pTextureRV;
};
