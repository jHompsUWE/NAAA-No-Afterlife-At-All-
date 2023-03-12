#ifndef _TPS_CAMERA_
#define _TPS_CAMERA_
#include "camera.h"

//=================================================================
//TPS style camera which will follow a given GameObject around _target
//=================================================================

class TPSCamera : public Camera
{
public:
	TPSCamera(float _fieldOfView, float _aspectRatio, float _nearPlaneDistance, float _farPlaneDistance, Vector3 _target, Vector3 _up, Vector3 _dpos, Vector3 _offset);
	virtual ~TPSCamera();

	virtual void Tick(GameData* _GD) override;

protected:
	GameObject*	m_targetObject; //I'm following this object
	Vector3	m_dpos; //I'll lurk this far behind and away from it

	const Vector3 up = Vector3::UnitY;
	Vector3 camera_target;
	Vector3 offset;
};

#endif
