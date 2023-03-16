#pragma once

#include "WorldManager.h"
#include "GameData.h"
#include "TPSCamera.h"
#include "Listener.h"

class SelectionHandler: public Listener
{
public:
	SelectionHandler(std::map<PlaneType, std::vector<std::unique_ptr<GridLocation>>>& _world, GameData* _GD);
	
	void setStartPos(Vector3 _start_pos);

	void setEndPos(Vector3 _start_pos);

	void update(TPSCamera& tps_cam);

	void onEvent(const Event& event) override;

	PlaneType m_plane;
	TileType m_tile_type;
	ZoneType m_zone_type;
private:
	std::map<PlaneType, std::vector<std::unique_ptr<GridLocation>>>& m_world;

	Vector3 m_start_pos;
	Vector3 m_end_pos;

	GameData* m_GD;

	Vector3 convertPosition(Vector3 _pos_to_convert, TPSCamera& tps_cam);

};

