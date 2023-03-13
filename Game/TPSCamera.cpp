#include "pch.h"
#include "TPSCamera.h"
#include "GameData.h"

TPSCamera::TPSCamera(float _fieldOfView, float _aspectRatio, float _nearPlaneDistance, float _farPlaneDistance, Vector3 _target, Vector3 _up, Vector3 _dpos, Vector3 _offset, GameData* _game_data)
	:Camera(_fieldOfView, _aspectRatio, _nearPlaneDistance, _farPlaneDistance, _up)
{
	m_dpos = _dpos;
	offset = _offset;
	m_pos = _target;
	game_data = _game_data;
}

TPSCamera::~TPSCamera()
{

}

void TPSCamera::Tick(GameData* _GD)
{
	//CameraMovement(_GD);
	
	// Calculate the orthographic projection matrix
	float viewWidth = 1000.0f; // replace with the desired width of the view
	float viewHeight = viewWidth / m_aspectRatio;
	m_pos = camera_target + offset;
	m_projMat = XMMatrixOrthographicRH(viewHeight * cameraZoom, viewWidth * cameraZoom, m_nearPlaneDistance * cameraZoom, m_farPlaneDistance * cameraZoom);
	m_viewMat = XMMatrixLookAtRH(m_pos, camera_target, up);

	GameObject::Tick(_GD);
}

void TPSCamera::onEvent(const Event& event)
{
	switch (event.type)
	{
		case EventType::ZOOM_IN:
		{
			if (cameraZoom >= 0.09f)
			{
				cameraZoom -= 0.9f * game_data->m_dt;
			}
			break;
		}
		case EventType::ZOOM_OUT:
		{
			std::cout << "zoom in";
			if (cameraZoom <= 1.2f)
			{
				cameraZoom += 0.9f * game_data->m_dt;
			}
			break;
		}
		case EventType::SCROLL_UP:
		{
			camera_target += movementYAxis * game_data->m_dt;
			break;
		}
		case EventType::SCROLL_DOWN:
		{
			camera_target -= movementYAxis * game_data->m_dt;
			break;
		}
		case EventType::SCROLL_LEFT:
		{
			camera_target += movementZAxis * game_data->m_dt;
			break;
		}
		case EventType::SCROLL_RIGHT:
		{
			camera_target -= movementZAxis * game_data->m_dt;
			break;
		}
		default:;
	}
}

