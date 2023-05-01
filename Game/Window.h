#pragma once
#include "GameObject2D.h"
#include "TextGO2D.h"
#include "ImageGO2D.h"
#include <vector>


class Window :public GameObject2D
{
public:
	Window();

	Window(string _fileName, ID3D11Device* _GD, string _windowName, bool render, XMVECTORF32 _colour);
	virtual ~Window();

	void Init(ID3D11Device* _GD);

	void SetTextPos();

	virtual void DragBounds(GameData* _GD);

	void SetBounds(float width, float height);
	void SetBounds(Vector2 new_bounds);

	void UpdateCloseButton();

	
	std::vector<std::shared_ptr<GameObject2D>> w_components;


	void tickComponents(GameData* _GD);
	void drawComponents(DrawData2D* _DD);



	virtual void Tick(GameData* _GD);
	virtual void Draw(DrawData2D* _DD);

private:


protected:

	ID3D11ShaderResourceView* m_pTextureRV;
	Rectangle bounds;
	std::shared_ptr<TextGO2D> windowname = nullptr;
	std::shared_ptr<ImageGO2D> close_button_sprite = nullptr;

	bool dragged = false;

	Vector2 m_scale;
	
	

	float differenceX = 0.0f;
	float differenceY = 0.0f;

	float renderOrder;
};

