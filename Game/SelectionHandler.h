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
	Road,
	Nuke
};

class SelectionHandler: public Listener
{
public:
	SelectionHandler(std::shared_ptr<WorldManager> _world_manager, GameData* _GD, 
		Microsoft::WRL::ComPtr<ID3D11DeviceContext1> _d3dContext);
	
	void setStartPos(Vector3 _start_pos);

	void setEndPos(Vector3 _start_pos);

	void update(TPSCamera& tps_cam);

	void draw(DrawData* m_DD);

	void onEvent(const Event& event) override;

	void calculateGridSpaces(Vector2& low_grid, Vector2& high_grid);


private:
	std::shared_ptr<WorldManager> m_world_manager;

	Vector3 m_start_pos;
	Vector3 m_end_pos;

	GameData* m_GD;

	Microsoft::WRL::ComPtr<ID3D11DeviceContext1> m_d3dContext;

	GridLocation* m_start_tile;
	GridLocation* m_end_tile;

	static const int radius = 500;

	/// <summary>
	/// True whilst highlighting an area to change
	/// </summary>
	bool currently_selecting;

	/// <summary>
	/// Becomes true when selection has finished
	/// </summary>
	bool update_tile;

	SelectionType m_selection_type;

	Vector3 convertPosition(Vector3 _pos_to_convert, TPSCamera& tps_cam);

	void updateTiles();

	void updateRoads();

	void updateBuilding();

	void updateNuke();

	void createTempBuilding();

	GenericBuilding* temp_building_stats;
	GPGO* temp_building;
	Vector3 temp_building_pos;
	void updateTempPos();

	GridLocation* findNearestTile(Vector3 mouse_pos);

	PlaneType m_plane;
	TileType m_tile_type;
	ZoneType m_zone_type;
};

