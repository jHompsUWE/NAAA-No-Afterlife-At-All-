#pragma once
#include "GameObject2D.h"
#include "Button.h"
#include "ButtonToggleWindow.h"
#include "ButtonOpenBW.h"
#include <array>
#include "Window.h"
#include "TextGO2D.h"
#include "Listener.h"
#include <unordered_map>

class UIRemote :public GameObject2D, public Listener
{
public:

	UIRemote(ID3D11Device* _GD);
	virtual ~UIRemote();

	void SetButtonBounds();

	void SetButtonToggle(int i, Window* toggle);
	void SetButtonToggle(int i, BuildingWindow* toggle);

	void onEvent(const Event& event) override;

	void setString(int stringNum, std::string _text);

	virtual void Tick(GameData* _GD);
	virtual void Draw(DrawData2D* _DD);

	bool renderable = true;

	std::array<Button*, 21> buttonsSwitch;
	std::array<ButtonOpenBW*, 9> buttonsBuilding;
	std::array<ButtonToggleWindow*, 7> buttonsWindow;

	std::array<TextGO2D*, 8> text;
	int money = 999999999;
	//int year = 0;

	bool buildingWindowOpen = false;
	bool dragged = false;

protected:

	ID3D11ShaderResourceView* m_pTextureRV;
	Rectangle bounds;

	float differenceX = 0.0f;
	float differenceY = 0.0f;
};
