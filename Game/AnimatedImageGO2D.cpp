#include "pch.h"
#include "AnimatedImageGO2D.h"

AnimatedImageGO2D::AnimatedImageGO2D(string _filename, int cell_size, ID3D11Device* _GD)
{

	sprite = new ImageGO2D(_filename, _GD);
	uv = new RECT();

	uv->top = 0;
	uv->bottom = cell_size;
	uv->left = 0;
	uv->right = cell_size;


	
}

AnimatedImageGO2D::~AnimatedImageGO2D()
{
	delete sprite;
	delete uv;
}

void AnimatedImageGO2D::Tick(GameData* _GD)
{
	sprite->Tick(_GD);
	UpdateProperties();
}

void AnimatedImageGO2D::Draw(DrawData2D* _DD)
{
	sprite->Draw(_DD);
}

void AnimatedImageGO2D::UpdateProperties()
{
	sprite->SetColour(this->m_colour);
	sprite->SetOrigin(this->m_origin);
	sprite->SetPos(this->m_pos);
	sprite->SetRot(this->m_rotation);
	sprite->SetScale(this->m_scale);
}

void AnimatedImageGO2D::InitialProperties()
{
}
