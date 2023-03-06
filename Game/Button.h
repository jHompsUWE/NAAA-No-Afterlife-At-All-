#pragma once
#include "GameObject2D.h"
#include "ImageGO2D.h"

//=================================================================
//A Game Object 2D for displaying images
//image needs to have been converted to a dds by the Assets project
//add orginal file to this project and set it to "Image Content Pipeline"
// in a similar fashion as getting the models
//=================================================================

class Button :public GameObject2D
{
public:
	Button(string _fileName, ID3D11Device* _GD, ImageGO2D* parent);
	virtual ~Button();

	virtual void Tick(GameData* _GD);
	virtual void Draw(DrawData2D* _DD);

protected:
	Rectangle bounds;

	ImageGO2D* parentWindow;

	ID3D11ShaderResourceView* m_pTextureRV;
};
