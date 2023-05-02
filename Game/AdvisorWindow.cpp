#include "pch.h"
#include "AdvisorWindow.h"

AdvisorWindow::AdvisorWindow(ID3D11Device* _GD) //: w_components(w_components_w)
{
	//m_pos = Vector2(300, 300);

	Init(_GD);

	background_sprite = std::make_shared<ImageGO2D>("advisor-window", _GD);
	background_sprite->SetScale(m_scale);
	background_sprite->CalculateBounds();

	angel_sprite = std::make_shared<AnimatedImageGO2D>("angel-advisor-Sheet", 305, _GD);
	angel_sprite->SetScale(m_scale);
	//angel_sprite->sprite->SetOrigin(Vector2(0, 0));
	angel_sprite->SetOffset(Vector2(0, 0 - background_sprite->GetImageSize().y / 2));
	angel_sprite->NewAnimation("idle", 5, 0, Vector2(0, 0), true);
	//angel_sprite->StopAnimation();

	devil_sprite = std::make_shared<AnimatedImageGO2D>("devil-advisor-Sheet", 305, _GD);
	devil_sprite->SetScale(m_scale);
	devil_sprite->SetOffset(Vector2(0 - background_sprite->GetImageSize().x / 2, 0 - background_sprite->GetImageSize().y / 2));
	devil_sprite->NewAnimation("idle", 5, 0, Vector2(0, 0), true);

	subtitles = std::make_shared<TextGO2D>("omg");
	subtitles->SetScale(0.5);
	subtitles->AddToString("these", Color(0.4,0,0));
	subtitles->AddToString("are all", Color(0, 1, 0));
	subtitles->AddToString("different", Color(0.5, 0.5, 0.1));
	subtitles->AddToString("colours!!!!", Color(0.1, 0.5, 0.5));
	subtitles->AddToString("isn'tth", Color(1, 0, 0));
	subtitles->AddToString("atcool!!?", Color(1, 0, 0.3));

	subtitles_test = std::make_shared<TextGO2D>("isnt isnt");

	SetBounds(background_sprite->GetImageSize());

	SetWindowScale(0.7);


	w_components.push_back(background_sprite);
	w_components.push_back(angel_sprite);
	w_components.push_back(devil_sprite);
	w_components.push_back(subtitles);



	w_components.push_back(close_button_sprite);

	close_button_sprite->SetOffset(bounds.width/2, 0 - bounds.height / 2);
}

AdvisorWindow::~AdvisorWindow()
{
	background_sprite.reset();
	angel_sprite.reset();
	devil_sprite.reset();
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
	//UpdateCloseButton();
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

	close_button_sprite->SetOffset(0 + bounds.width / 2, 0 - bounds.height / 2);

	SetBounds(background_sprite->GetImageSize());

}
