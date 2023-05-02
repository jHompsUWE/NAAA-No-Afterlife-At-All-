#pragma once
#include "GameObject2D.h"
#include "Window.h"
#include "Event.h"
#include "Listener.h"

enum class Direction
{
	NONE,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Button :public GameObject2D, public Listener
{
public:
	Button();
	Button(ID3D11Device* _GD, GameObject2D* _parent);
	Button(ID3D11Device* _GD, GameObject2D* _parent, string _name, Vector2 _scale, Vector2 _position, EventType _type, Direction _diretion);
	virtual ~Button();

	virtual void Tick(GameData* _GD);
	virtual void Draw(DrawData2D* _DD);

	virtual void onEvent(const Event& event) override;

	void SetBounds();
	void SetName(string _name);
	void SetType(EventType _event_type);

	float differenceX;
	float differenceY;
	
	string buttonName = "Button";
	EventType event_type;
	Direction direction;
	
	bool pressed = false;

protected:
	Rectangle bounds;

	GameObject2D* parentWindow;
	
	ID3D11ShaderResourceView* m_pTextureRV;
};
