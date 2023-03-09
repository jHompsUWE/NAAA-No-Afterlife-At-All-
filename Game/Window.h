#pragma once
#include "GameObject2D.h"

class Window :public GameObject2D
{
public:

	Window(string _fileName, ID3D11Device* _GD);
	virtual ~Window();

	virtual void Tick(GameData* _GD);
	virtual void Draw(DrawData2D* _DD);

	bool renderable = true;

protected:

	ID3D11ShaderResourceView* m_pTextureRV;
	Rectangle bounds;

	bool dragged = false;

	float differenceX = 0.0f;
	float differenceY = 0.0f;

	float renderOrder;
};

