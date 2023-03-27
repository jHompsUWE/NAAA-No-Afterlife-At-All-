#pragma once
#include "Window.h"
#include "ImageGO2D.h"
#include "GameObject2D.h"
#include <vector>
#include "AnimatedImageGO2D.h"


class AdvisorWindow : public Window
{
public:
	AdvisorWindow(ID3D11Device* _GD);
	~AdvisorWindow();

	void Tick(GameData* _GD);
	void Draw(DrawData2D* _DD);

	void SetWindowScale(float scale);
	

private:

	ImageGO2D* background_sprite;
	AnimatedImageGO2D* angel_sprite;
	AnimatedImageGO2D* devil_sprite;

	std::vector<GameObject2D*> w_components;




	

};

