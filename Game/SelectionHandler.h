#pragma once

#include "WorldManager.h"
#include "GameData.h"
#include "TPSCamera.h"
#include "Listener.h"

#include <tuple>
#include <queue>
#include <unordered_map>
#include <utility>

enum class SelectionType
{
	None,
	Zone,
	Building,
	Road
};

class SelectionHandler: public Listener
{
public:
	SelectionHandler(std::shared_ptr<WorldManager> _world_manager, GameData* _GD, 
		Microsoft::WRL::ComPtr<ID3D11DeviceContext1> _d3dContext);
	
	void setStartPos(Vector3 _start_pos);

	void setEndPos(Vector3 _start_pos);

	void update(TPSCamera& tps_cam);

	void onEvent(const Event& event) override;

	
private:
	std::shared_ptr<WorldManager> m_world_manager;

	Vector3 m_start_pos;
	Vector3 m_end_pos;

	GameData* m_GD;

	Microsoft::WRL::ComPtr<ID3D11DeviceContext1> m_d3dContext;

	GridLocation* m_start_tile;
	GridLocation* m_end_tile;

	static const int radius = 500;

	bool currently_selecting;
	bool update_tile;

	SelectionType m_selection_type;

	Vector3 convertPosition(Vector3 _pos_to_convert, TPSCamera& tps_cam);

	void updateTiles();

	void updateRoads();

	void updateBuilding();

	void pathfindRoads();

	GridLocation* findNearestTile(Vector3 mouse_pos);

	PlaneType m_plane;
	TileType m_tile_type;
	ZoneType m_zone_type;
};

