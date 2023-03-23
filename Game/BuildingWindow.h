#pragma once
#include "GameObject2D.h"
#include "TextGO2D.h"
#include "BuildingButton.h"
#include <vector>
#include "GameManager.h"

class BuildingWindow : public GameObject2D
{
public:
	BuildingWindow(string _fileName, ID3D11Device* _GD, int _buttoNum);
	virtual ~BuildingWindow();

	void SetTextPos();

	virtual void Tick(GameData* _GD);
	virtual void Draw(DrawData2D* _DD);


	std::vector<BuildingButton*> buttons;

protected:

	ID3D11ShaderResourceView* m_pTextureRV;
	Rectangle bounds;

	
	BuildingButton* hovered;


	Vector2 m_scale;

	float renderOrder;
};

