#pragma once
#include "GameObject2D.h"
#include "ImageGO2D.h"


class AnimatedImageGO2D : public GameObject2D
{

public:
	AnimatedImageGO2D(string _filename, int cell_size, ID3D11Device* _GD);
	~AnimatedImageGO2D();


	void Tick(GameData* _GD);
	void Draw(DrawData2D* _DD);


	//Objects
	ImageGO2D* sprite;
	RECT* uv;


private:

	void UpdateProperties();

	void InitialProperties();

};

