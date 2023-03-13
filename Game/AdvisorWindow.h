#pragma once
#include "window.h"
#include "json.hpp"
#include "AnimatedImageGO2D.h"


class AdvisorWindow : public Window
{
public:

	AdvisorWindow(ID3D11Device* _GD);
	~AdvisorWindow();

	AnimatedImageGO2D* devil_sprite;
	AnimatedImageGO2D* angel_sprite;

	void Tick(GameData* _GD);
	void Draw(DrawData2D* _DD);



};

