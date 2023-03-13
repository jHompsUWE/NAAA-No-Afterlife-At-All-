#pragma once
#include "GameObject2D.h"
#include "ImageGO2D.h"
#include "Animation.h"
#include <iostream>
#include <vector>


class AnimatedImageGO2D : public GameObject2D
{

public:
	AnimatedImageGO2D(string _filename, int cell_size, ID3D11Device* _GD);
	~AnimatedImageGO2D();


	void NewAnimation(string animation_name, int frame_count, float speed, Vector2 starting_pos, bool loop);
	void ChangeAnimation(string animation_name);
	void PlayAnimation();
	void StopAnimation();
	void StartAnimation();
	void SetSpeed(float new_speed);
	void SetFrame(int frame);
	void FocusUV();
	void CheckFinished();


	void Tick(GameData* _GD);
	void Draw(DrawData2D* _DD);

	bool on_finish = false;
	bool is_finished = false;

	//Objects
	ImageGO2D* sprite;
	RECT* uv;

	int timer;


private:

	Vector2 image_size;
	int cell_size;
	int current_frame = 0;

	bool is_animation_playing = true;

	std::vector<Animation> animation_list;

	void UpdateProperties();

};





