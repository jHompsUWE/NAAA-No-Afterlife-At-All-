#ifndef _TPS_CAMERA_
#define _TPS_CAMERA_
#include "camera.h"
#include "Listener.h"
#include <iostream>

//=================================================================
//TPS style camera which will follow a given GameObject around _target
//=================================================================

class TPSCamera : public Camera, public Listener
{
public:
	TPSCamera(float _fieldOfView, float _aspectRatio, float _nearPlaneDistance, float _farPlaneDistance, Vector3 _target, Vector3 _up, Vector3 _dpos, Vector3 _offset, GameData* _game_data);
	virtual ~TPSCamera();

	virtual void Tick(GameData* _GD) override;
	float getZoom() { return cameraZoom; }
	Vector3 GetDirection();
	Vector3 camera_target{};
protected:
	
	//void CameraMovement(GameData* _GD);
	void onEvent(const Event& event) override;

	
	
	GameObject*	m_targetObject; //I'm following this object
	Vector3	m_dpos; //I'll lurk this far behind and away from it

	const Vector3 up = Vector3::UnitY;
	
	Vector3 offset {10.0f, 10.0f, 0.0f};
	float cameraZoom  = 1.0f;

	const float cameraSpeed = 3.0f;
	const Vector3 movementYAxis = cameraSpeed * Vector3::UnitY;
	const Vector3 movementZAxis = cameraSpeed * Vector3(-0.5, 0,  0.5);
	GameData* game_data = nullptr;
};

#endif
