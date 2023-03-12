#pragma once
#include "GameObject2D.h"
#include "TextGO2D.h"

class Window :public GameObject2D
{
public:

	Window(string _fileName, ID3D11Device* _GD, string _windowName, bool render, XMVECTORF32 _colour);
	virtual ~Window();

	void SetTextPos();

	virtual void Tick(GameData* _GD);
	virtual void Draw(DrawData2D* _DD);

	bool renderable = true;

protected:

	ID3D11ShaderResourceView* m_pTextureRV;
	Rectangle bounds;

	TextGO2D* windowname;

	bool dragged = false;

	Vector2 m_scale;

	float differenceX = 0.0f;
	float differenceY = 0.0f;

	float renderOrder;
};

