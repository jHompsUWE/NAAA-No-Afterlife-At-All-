#pragma once
#include "GameObject2D.h"
#include "Button.h"
#include <array>
#include "Window.h"
#include "TextGO2D.h"
#include "Listener.h"

class UIRemote :public GameObject2D, public Listener
{
public:

	UIRemote(ID3D11Device* _GD);
	virtual ~UIRemote();

	void SetButtonBounds();

	void InitButtonNames();

	void SetButtonToggle(int i, GameObject2D* toggle);

	void onEvent(const Event& event) override;

	void setString(int stringNum, std::string _text);

	virtual void Tick(GameData* _GD);
	virtual void Draw(DrawData2D* _DD);

	bool renderable = true;

	std::array<Button*, 37> buttons;
	std::array<TextGO2D*, 8> text;
	int money = 999999999;
	//int year = 0;

protected:

	ID3D11ShaderResourceView* m_pTextureRV;
	Rectangle bounds;

	bool dragged = false;

	float differenceX = 0.0f;
	float differenceY = 0.0f;

	float renderOrder;
};
