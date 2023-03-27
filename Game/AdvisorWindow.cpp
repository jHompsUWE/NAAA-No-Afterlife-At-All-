#include "pch.h"
#include "AdvisorWindow.h"

AdvisorWindow::AdvisorWindow(ID3D11Device* _GD)
{
	//m_pos = Vector2(300, 300);

	

	background_sprite = new ImageGO2D("advisor-window", _GD);
	background_sprite->SetScale(m_scale);
	background_sprite->CalculateBounds();

	angel_sprite = new AnimatedImageGO2D("angel-advisor-Sheet", 305, _GD);
	angel_sprite->SetScale(m_scale);
	//angel_sprite->sprite->SetOrigin(Vector2(0, 0));
	angel_sprite->SetOffset(Vector2(0, 0 - background_sprite->GetImageSize().y / 2));
	angel_sprite->NewAnimation("idle", 5, 60, Vector2(0, 0), true);
	//angel_sprite->StopAnimation();

	devil_sprite = new AnimatedImageGO2D("devil-advisor-Sheet", 305, _GD);
	devil_sprite->SetScale(m_scale);
	devil_sprite->SetOffset(Vector2(0 - background_sprite->GetImageSize().x / 2, 0 - background_sprite->GetImageSize().y / 2));
	devil_sprite->NewAnimation("idle", 5, 60, Vector2(0, 0), true);


	SetBounds(background_sprite->GetImageSize());

	SetWindowScale(0.6);

	w_components.push_back(background_sprite);
	w_components.push_back(angel_sprite);
	w_components.push_back(devil_sprite);
	
	
}

AdvisorWindow::~AdvisorWindow()
{
	delete background_sprite;
	delete angel_sprite;
	delete devil_sprite;
}

void AdvisorWindow::Tick(GameData* _GD)
{
	DragBounds(_GD);
	for (int i = 0; i < w_components.size(); i++)
	{
		GameObject2D& component = *w_components[i];
		component.SetPos(m_pos + component.GetOffset());
		component.Tick(_GD);
	}
}

void AdvisorWindow::Draw(DrawData2D* _DD)
{
	if (renderable)
	{
		for(int i = 0; i < w_components.size(); i++)
		{
			GameObject2D& component = *w_components[i];
			component.Draw(_DD);
		}
	}
}

void AdvisorWindow::SetWindowScale(float scale)
{
	m_scale = Vector2(scale, scale);

	background_sprite->SetScale(scale);
	background_sprite->CalculateBounds();


	angel_sprite->SetScale(scale);
	angel_sprite->SetOffset(Vector2(0, 0 - background_sprite->GetImageSize().y / 2));

	devil_sprite->SetScale(scale);
	devil_sprite->SetOffset(Vector2(0 - background_sprite->GetImageSize().x / 2, 0 - background_sprite->GetImageSize().y / 2));

	SetBounds(background_sprite->GetImageSize());

}
