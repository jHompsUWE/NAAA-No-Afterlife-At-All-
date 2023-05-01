#pragma once
#include "BaseAnimateWindow.h"
#include "ImageGO2D.h"
#include "GameObject2D.h"
#include "TextGO2D.h"
#include <vector>
#include "AnimatedImageGO2D.h"


class AdvisorWindow : public BaseAnimateWindow
{
public:
	AdvisorWindow(ID3D11Device* _GD);
	~AdvisorWindow();

	void Tick(GameData* _GD);
	void Draw(DrawData2D* _DD);

	void SetWindowScale(float scale);
	

private:

	//std::vector<GameObject2D*>& w_components;

	std::shared_ptr<ImageGO2D> background_sprite = nullptr;
	std::shared_ptr<AnimatedImageGO2D> angel_sprite = nullptr;
	std::shared_ptr<AnimatedImageGO2D> devil_sprite = nullptr;
	std::shared_ptr<TextGO2D> subtitles = nullptr;
	std::shared_ptr<TextGO2D> subtitles_test = nullptr;






	

};

