#include "pch.h"
#include "Animation.h"

Animation::Animation(string aname, int aframe_count, float aspeed, Vector2 astarting_pos, Vector2 asprite_sheet_size, int acell_size, bool aloop)
{
	name = aname;
	frame_count = aframe_count;
	speed = aspeed;
	starting_pos = astarting_pos;
	sprite_sheet_size = asprite_sheet_size;
	cell_size = acell_size;
	loop = aloop;


	StoreFrames();


}

Animation::~Animation()
{
}


void Animation::StoreFrames()
{
	int x = starting_pos.x * cell_size;
	int y = starting_pos.y * cell_size;

	for (int i = 0; i < frame_count; i++)
	{
		Vector2 frame = Vector2();
		frame.x = x;
		frame.y = y;

		frames.push_back(frame);

		x += cell_size;

		if (x == sprite_sheet_size.x)
		{
			x = 0;
			y += cell_size;
		}

	}
}