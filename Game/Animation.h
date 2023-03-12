#pragma once
#include "GameObject2D.h"
#include <iostream>
#include <vector>

struct Animation
{
	Animation(string name, int frame_count, float speed, Vector2 starting_pos, Vector2 sprite_sheet_size, int cell_size, bool loop);
	~Animation();

	void StoreFrames();

	string name;
	int frame_count;
	float speed;
	Vector2 starting_pos;
	int cell_size;
	Vector2 sprite_sheet_size;
	bool loop;

	std::vector<Vector2> frames;

};

