#pragma once
#include "GameObject2D.h"
#include "TextGO2D.h"
#include "ImageGO2D.h"

class Window :public GameObject2D
{
public:
	Window();
	Window(ID3D11Device* _GD);
	Window(XMVECTORF32 _colour, string _windowName, bool render,  ID3D11Device* _GD);
	Window(string _fileName, string _windowName, bool render, ID3D11Device* _GD);
	virtual ~Window();

	void SetTextPos();

	void SetSpriteReference(ImageGO2D sprite);

	void Drag(GameData* _GD);

	virtual void Tick(GameData* _GD);
	virtual void Draw(DrawData2D* _DD);

	bool renderable = true;

	ImageGO2D* sprite;

protected:

	ID3D11ShaderResourceView* m_pTextureRV;
	Rectangle bounds;

	TextGO2D* windowname;

	bool dragged = false;

	Vector2 m_scale;

	bool is_sprite = false;

	float differenceX = 0.0f;
	float differenceY = 0.0f;

	float renderOrder;
};

