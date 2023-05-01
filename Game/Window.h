#pragma once
#include "GameObject2D.h"
#include "TextGO2D.h"

class Window :public GameObject2D
{
public:
	Window();

	Window(ID3D11Device* _GD, string _windowName, bool render, XMVECTORF32 _colour);
	virtual ~Window();

	virtual void Tick(GameData* _GD);
	virtual void Draw(DrawData2D* _DD);


	ID3D11ShaderResourceView* m_pTextureRV;
	Rectangle bounds;

	Vector2 m_scale;
};

