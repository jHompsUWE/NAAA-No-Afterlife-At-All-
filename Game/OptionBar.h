#pragma once
#include "GameObject2D.h"
#include "OptionBarButton.h"
#include "OptionBarWindow.h"
#include "Button.h"
#include <array>
#include <vector>
#include <iostream>

class OptionBar : public GameObject2D
{
public:
	OptionBar(ID3D11Device* _GD);
	~OptionBar();

	void Tick(GameData* _GD);
	void Draw(DrawData2D* _DD);

private:
	std::array<OptionBarButton*, 4> optionButtons;
	std::vector<OptionBarWindow*> optionWindows;

	ID3D11ShaderResourceView* m_pTextureRV;
	Rectangle bounds;

	OptionBarButton* hovered;

};

