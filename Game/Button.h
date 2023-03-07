#pragma once
#include "GameObject2D.h"
#include "ImageGO2D.h"

//=================================================================
//Button class based off ImageGO2D class
//Work in progress
// 
//=================================================================

class Button :public GameObject2D
{
public:
	Button(string _fileName, ID3D11Device* _GD, ImageGO2D* parent, ImageGO2D* toggle);
	virtual ~Button();

	virtual void Tick(GameData* _GD);
	virtual void Draw(DrawData2D* _DD);

protected:
	Rectangle bounds;

	ImageGO2D* parentWindow;
	ImageGO2D* toggleWindow;

	ID3D11ShaderResourceView* m_pTextureRV;
};
