#include "pch.h"
#include "AnimatedImageGO2D.h"

AnimatedImageGO2D::AnimatedImageGO2D(string _filename, int acell_size, ID3D11Device* _GD)
{

	sprite = new ImageGO2D(_filename, _GD);
	uv = new RECT();
	cell_size = acell_size;

	uv->top = 0;
	uv->bottom = cell_size;
	uv->left = 0;
	uv->right = cell_size;

	image_size = Vector2(sprite->Desc.Width, sprite->Desc.Height);

	sprite->SetUV(uv);
}

AnimatedImageGO2D::~AnimatedImageGO2D()
{
	delete sprite;
	delete uv;
}

void AnimatedImageGO2D::NewAnimation(string animation_name, int frame_count, float speed, Vector2 starting_pos, bool loop)
{
	Animation animation = Animation(animation_name, frame_count, speed, starting_pos, image_size, cell_size, loop);
	animation_list.push_back(animation);

	if (animation_list.size() == 1)
	{
		timer = speed;
	}
}

void AnimatedImageGO2D::ChangeAnimation(string animation_name)
{
	if (animation_list[0].name != animation_name)
	{
		current_frame = 0;
		CheckFinished();
		for (int i = 0; i < animation_list.size(); i++)
		{
			std::swap(animation_list[i], animation_list[0]);
			FocusUV();
			timer = animation_list[0].speed;
			break;
		}
	}
}

void AnimatedImageGO2D::PlayAnimation()
{

	//Return Conditions
	if (!animation_list[0].speed > 0)
	{
		return;
	}

	if (timer >= 0)
	{ 
		return;
	}

	if (!is_animation_playing)
	{
		return;
	}

	if (animation_list.empty())
	{
		return;
	}

	//Play code

	if (current_frame < (animation_list[0].frame_count - 1))
	{
		current_frame++;
	}
	else if (animation_list[0].loop)
	{
		current_frame = 0;
	}
	FocusUV();
	timer = animation_list[0].speed;
	CheckFinished();

}

void AnimatedImageGO2D::StopAnimation()
{
	is_animation_playing = false;
}

void AnimatedImageGO2D::StartAnimation()
{
	is_animation_playing = true;
}

void AnimatedImageGO2D::SetSpeed(float new_speed)
{
	animation_list[0].speed = new_speed;
}

void AnimatedImageGO2D::SetFrame(int frame)
{
	if (frame < animation_list[0].frame_count)
	{
		current_frame = frame;
		FocusUV();
	}

}

void AnimatedImageGO2D::FocusUV()
{
	uv->left = animation_list[0].frames[current_frame].x;
	uv->right = uv->left + cell_size;
	uv->top = animation_list[0].frames[current_frame].y;
	uv->bottom = uv->top + cell_size;
}

void AnimatedImageGO2D::CheckFinished()
{
	on_finish = false;

	if ((current_frame)+1 == animation_list[0].frame_count)
	{
		if (!is_finished)
		{
			on_finish = true;
		}
		is_finished = true;
		return;
	}
	else
	{
		is_finished = false;
	}

}

void AnimatedImageGO2D::Tick(GameData* _GD)
{
	timer -= 1;
	PlayAnimation();
	UpdateProperties();
	sprite->Tick(_GD);

}

void AnimatedImageGO2D::Draw(DrawData2D* _DD)
{
	if (renderable)
	{
		sprite->Draw(_DD);
	}
}

void AnimatedImageGO2D::UpdateProperties()
{
	sprite->SetColour(this->m_colour);
	sprite->SetOrigin(this->m_origin);
	sprite->SetPos(this->m_pos);
	sprite->SetRot(this->m_rotation);
	sprite->SetScale(this->m_scale);
}
