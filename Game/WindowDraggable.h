#pragma once
#include "Window.h"
#include "TextGO2D.h"

class WindowDraggable :public Window
{
public:
	WindowDraggable();

	WindowDraggable(ID3D11Device* _GD, string _windowName, bool render, XMVECTORF32 _colour);
	virtual ~WindowDraggable();

	void SetTextPos();

	virtual void Tick(GameData* _GD);
	virtual void Draw(DrawData2D* _DD);


	ID3D11ShaderResourceView* m_pTextureRV;
	Rectangle bounds;

	TextGO2D* windowname;

	bool dragged = false;

	Vector2 m_scale;

	float differenceX = 0.0f;
	float differenceY = 0.0f;
};

