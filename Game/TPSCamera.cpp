#include "pch.h"
#include "TPSCamera.h"
#include "GameData.h"

TPSCamera::TPSCamera(float _fieldOfView, float _aspectRatio, float _nearPlaneDistance, float _farPlaneDistance, GameObject* _target, Vector3 _up, Vector3 _dpos, Vector3 _offset)
	:Camera(_fieldOfView, _aspectRatio, _nearPlaneDistance, _farPlaneDistance, _up)
{
	m_targetObject = _target;
	m_dpos = _dpos;
	offset = _offset;
}

TPSCamera::~TPSCamera()
{

}

void TPSCamera::Tick(GameData* _GD)
{
	//Set up position of camera and target position of camera based on new position and orientation of target object
	Matrix rotCam = Matrix::CreateFromYawPitchRoll(0.f, -10.0f, -45.0f);
	m_target = m_targetObject->GetPos();
	m_pos = m_target + offset;

	// Calculate the orthographic projection matrix
	float viewWidth = 100.0f; // replace with the desired width of the view
	float viewHeight = viewWidth / m_aspectRatio;
	m_fieldOfView = m_farPlaneDistance - m_nearPlaneDistance;

	//m_projMat = XMMatrixOrthographicLH(viewWidth, viewHeight , m_nearPlaneDistance, m_farPlaneDistance);
	//m_projMat = Matrix::CreateOrthographic(viewWidth, viewHeight, m_nearPlaneDistance, m_farPlaneDistance);
	m_projMat = XMMatrixOrthographicOffCenterRH(
		-viewWidth / 2.0f, // left
		viewWidth / 2.0f, // right
		-viewHeight / 2.0f, // bottom
		viewHeight / 2.0f, // top
		m_nearPlaneDistance, // near plane distance
		m_farPlaneDistance // far plane distance)
		);

	//m_viewMat = Matrix::CreateLookAt(m_pos, m_target, m_up);
	m_viewMat = XMMatrixLookAtRH(m_pos, camera_target, up);
	m_projMat = m_viewMat * m_projMat;

	//and then set up proj and view matrices
	//Camera::Tick(_GD);
}

