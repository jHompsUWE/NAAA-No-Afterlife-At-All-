#include "pch.h"
#include "AdvisorWindow.h"

AdvisorWindow::AdvisorWindow(ID3D11Device* _GD)
{
	background_sprite = new ImageGO2D("advisor-window", _GD);
	background_sprite->SetScale(0.6);
	background_sprite->CalculateBounds();

	SetBounds(background_sprite->GetImageSize());


	w_components.push_back(background_sprite);
}

AdvisorWindow::~AdvisorWindow()
{
	delete background_sprite;
}

void AdvisorWindow::Tick(GameData* _GD)
{
	DragBounds(_GD);

	for (int i = 0; i < w_components.size(); i++)
	{
		GameObject2D& component = *w_components[i];
		component.SetPos(m_pos + component.GetOffset());
	}
}

void AdvisorWindow::Draw(DrawData2D* _DD)
{
	if (renderable)
	{
		background_sprite->Draw(_DD);
	}
}
