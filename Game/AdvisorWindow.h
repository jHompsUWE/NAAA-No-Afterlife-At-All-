#pragma once
#include "Window.h"
#include "ImageGO2D.h"
#include "GameObject2D.h"
#include <vector>
class AdvisorWindow : public Window
{
public:
	AdvisorWindow(ID3D11Device* _GD);
	~AdvisorWindow();

	void Tick(GameData* _GD);
	void Draw(DrawData2D* _DD);
	

private:

	ImageGO2D* background_sprite;

	std::vector<GameObject2D*> w_components;




	

};

