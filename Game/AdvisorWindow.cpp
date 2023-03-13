#include "pch.h"
#include "AdvisorWindow.h"

AdvisorWindow::AdvisorWindow(ID3D11Device* _GD)
{
	sprite = new ImageGO2D("advisor-window", _GD);
	sprite->SetScale(0.5f);

	devil_sprite = new AnimatedImageGO2D("devil-advisor-Sheet", 305, _GD);
	devil_sprite->NewAnimation("idle", 5, 60, Vector2(0, 0), true);
	angel_sprite = new AnimatedImageGO2D("angel-advisor-Sheet", 305, _GD);
	angel_sprite->NewAnimation("idle", 5, 60, Vector2(0, 0), true);
}

AdvisorWindow::~AdvisorWindow()
{
	delete devil_sprite;
	delete angel_sprite;
}

void AdvisorWindow::Tick(GameData* _GD)
{
	Drag(_GD);
	devil_sprite->SetPos(300,300);
	angel_sprite->SetPos(300, 300);

}

void AdvisorWindow::Draw(DrawData2D* _DD)
{
	if (renderable)
	{
		sprite->Draw(_DD);
		windowname->Draw(_DD);
		devil_sprite->Draw(_DD);
		angel_sprite->Draw(_DD);
	}
}
