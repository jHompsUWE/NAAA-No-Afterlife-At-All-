#include "pch.h"
#include "TPSCamera.h"
#include "GameData.h"

TPSCamera::TPSCamera(float _fieldOfView, float _aspectRatio, float _nearPlaneDistance, float _farPlaneDistance, Vector3 _target, Vector3 _up, Vector3 _dpos, Vector3 _offset)
	:Camera(_fieldOfView, _aspectRatio, _nearPlaneDistance, _farPlaneDistance, _up)
{
	m_dpos = _dpos;
	offset = _offset;
	m_pos = _target;
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
	m_projMat = XMMatrixOrthographicLH(viewHeight * cameraZoom, viewWidth * cameraZoom, m_nearPlaneDistance * cameraZoom, m_farPlaneDistance * cameraZoom);
	m_viewMat = XMMatrixLookAtLH(m_pos, camera_target, up);

	GameObject::Tick(_GD);
}

void TPSCamera::CameraMovement(GameData* _GD)
{
	constexpr float cameraSpeed = 1.2f;
	const Vector3 movementYAxis = cameraSpeed * Vector3::UnitY;
	const Vector3 movementZAxis = cameraSpeed * Vector3::UnitZ;

	if (_GD->m_KBS.Q)
	{
		if (cameraZoom <= 1.2f)
		{
			cameraZoom += 0.2f * _GD->m_dt;
		}		
	}
	if (_GD->m_KBS.E)
	{
		if (cameraZoom >= 0.6f)
		{
			cameraZoom -= 0.2f * _GD->m_dt;
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
		camera_target -= movementZAxis;
	}

	if (_GD->m_KBS.D)
	{
		camera_target += movementZAxis;
	}
}

