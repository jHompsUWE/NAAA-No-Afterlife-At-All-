#ifndef _IMAGE_GO_2D_H_
#define _IMAGE_GO_2D_H_
#include "GameObject2D.h"

//=================================================================
//A Game Object 2D for displaying images
//image needs to have been converted to a dds by the Assets project
//add orginal file to this project and set it to "Image Content Pipeline"
// in a similar fashion as getting the models
//=================================================================

class ImageGO2D :public GameObject2D
{
public:
	ImageGO2D(string _fileName, ID3D11Device* _GD);
	virtual ~ImageGO2D();

	void SetUV(RECT* animated_uv);


	virtual void Tick(GameData* _GD);
	virtual void Draw(DrawData2D* _DD);

	D3D11_TEXTURE2D_DESC Desc;



	bool renderable = true;
protected:

	RECT uv;
	RECT* uv_ref = &uv;


	Rectangle bounds;

	ID3D11ShaderResourceView* m_pTextureRV;
};

#endif