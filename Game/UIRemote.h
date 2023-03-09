#pragma once
#include "GameObject2D.h"
#include "Button.h"
#include <array>
#include "Window.h"

class UIRemote :public GameObject2D
{
public:

	UIRemote(string _fileName, ID3D11Device* _GD, Window* toggle);
	virtual ~UIRemote();

	void SetButtonPos();

	virtual void Tick(GameData* _GD);
	virtual void Draw(DrawData2D* _DD);

	bool renderable = true;

	std::array<Button*, 37> buttons;

protected:

	ID3D11ShaderResourceView* m_pTextureRV;
	Rectangle bounds;

	bool dragged = false;

	float differenceX = 0.0f;
	float differenceY = 0.0f;

	float renderOrder;
};

