#pragma once

#include "WorldManager.h"
#include "GameData.h"
#include "TPSCamera.h"

class SelectionHandler
{
public:
	SelectionHandler(std::map<PlaneType, std::vector<std::unique_ptr<GridLocation>>>& _world, GameData* _GD);
	
	void setStartPos(Vector3 _start_pos);

	void setEndPos(Vector3 _start_pos);

	void update(TPSCamera& tps_cam);

private:
	std::map<PlaneType, std::vector<std::unique_ptr<GridLocation>>>& m_world;

	Vector3 m_start_pos;
	Vector3 m_end_pos;

	GameData* m_GD;
};

