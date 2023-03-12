#include "pch.h"
#include "TPSCamera.h"
#include "GameData.h"

TPSCamera::TPSCamera(float _fieldOfView, float _aspectRatio, float _nearPlaneDistance, float _farPlaneDistance, Vector3 _target, Vector3 _up, Vector3 _dpos, Vector3 _offset)
	:Camera(_fieldOfView, _aspectRatio, _nearPlaneDistance, _farPlaneDistance, _up)
{
	//m_targetObject = _target;
	m_dpos = _dpos;
	offset = _offset;
	m_pos = _target;
}

TPSCamera::~TPSCamera()
{

}

void TPSCamera::Tick(GameData* _GD)
{
	//Set up position of camera and target position of camera based on new position and orientation of target object
	//Matrix rotCam = Matrix::CreateFromYawPitchRoll(0.f, -10.0f, -45.0f);
	m_target = Vector3::Zero;
	m_pos = m_target + offset;

	// Calculate the orthographic projection matrix
	float viewWidth = 1000.0f; // replace with the desired width of the view
	float viewHeight = viewWidth / m_aspectRatio;
	m_fieldOfView = m_farPlaneDistance - m_nearPlaneDistance;

	m_projMat = XMMatrixOrthographicLH(viewWidth, viewHeight , m_nearPlaneDistance, m_farPlaneDistance);

	m_viewMat = XMMatrixLookAtLH(m_pos, camera_target, up);

	GameObject::Tick(_GD);
}

