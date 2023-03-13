#include "pch.h"
#include "TPSCamera.h"
#include "GameData.h"

TPSCamera::TPSCamera(float _fieldOfView, float _aspectRatio, float _nearPlaneDistance, float _farPlaneDistance, Vector3 _target, Vector3 _up, Vector3 _dpos, Vector3 _offset)
	:Camera(_fieldOfView, _aspectRatio, _nearPlaneDistance, _farPlaneDistance, _up)
{
	m_dpos = _dpos;
	offset = _offset;
	m_pos = _target;
	m_viewMat = XMMatrixLookAtRH(m_pos, camera_target, up);
}

TPSCamera::~TPSCamera()
{

}

void TPSCamera::Tick(GameData* _GD)
{
	CameraMovement(_GD);
	
	// Calculate the orthographic projection matrix
	float viewWidth = 1000.0f; // replace with the desired width of the view
	float viewHeight = viewWidth / m_aspectRatio;
	m_pos = camera_target + offset;
	m_projMat = XMMatrixOrthographicRH(viewHeight * cameraZoom, viewWidth * cameraZoom, m_nearPlaneDistance * cameraZoom, m_farPlaneDistance * cameraZoom);
	m_viewMat = XMMatrixLookAtRH(m_pos, camera_target, up);

	GameObject::Tick(_GD);
}


// Elvin helped with this to fix projection from mouse to correct world space
Vector3 TPSCamera::GetDirection()
{
	Vector3 cameraToTarget = camera_target - m_pos;
	float magnitude = sqrt(pow(cameraToTarget.x, 2) + pow(cameraToTarget.y, 2) + pow(cameraToTarget.z, 2));
	return Vector3{cameraToTarget.x / magnitude, cameraToTarget.y / magnitude, cameraToTarget.z / magnitude};
}

void TPSCamera::CameraMovement(GameData* _GD)
{
	constexpr float cameraSpeed = 1.2f;
	const Vector3 movementYAxis = cameraSpeed * Vector3::UnitY;
	const Vector3 movementZAxis = cameraSpeed * Vector3(-1.f, 0.0f, 1.0f);

	if (_GD->m_KBS.Q)
	{
		if (cameraZoom <= 1.2f)
		{
			cameraZoom += .9f * _GD->m_dt;
		}		
	}
	if (_GD->m_KBS.E)
	{
		if (cameraZoom >= 0.09f)
		{
			cameraZoom -= 0.9f * _GD->m_dt;
		}		
	}
	
	if (_GD->m_KBS.W)
	{
		camera_target += movementYAxis;
	}

	if (_GD->m_KBS.S)
	{
		camera_target -= movementYAxis;
	}
	if (_GD->m_KBS.A)
	{
		camera_target += movementZAxis;
	}

	if (_GD->m_KBS.D)
	{
		camera_target -= movementZAxis;
	}
}

