#pragma once

#include "WorldManager.h"
#include "GameData.h"
#include "TPSCamera.h"
#include "Listener.h"

#include <tuple>
#include <queue>
#include <unordered_map>

using Location = Vector2;

namespace std
{
	template<> struct hash<Location>
	{
		std::size_t operator()(const Location& id) const noexcept
		{
			return int(id.x) ^ int(id.y);
		}
	};
}

using PQElement = std::pair<int, Location>;

struct PriorityQueue
{
	std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement>> elements;

	inline bool empty() const { return elements.empty(); }

	inline void put(Location item, int priority) { elements.emplace(priority, item); }

	Location get()
	{
		Location best_item = elements.top().second;
		elements.pop();
		return best_item;
	}
};

class SelectionHandler: public Listener
{
public:
	SelectionHandler(WorldManager& _world_manager, GameData* _GD);
	
	void setStartPos(Vector3 _start_pos);

	void setEndPos(Vector3 _start_pos);

	void update(TPSCamera& tps_cam);

	void onEvent(const Event& event) override;

	PlaneType m_plane;
	TileType m_tile_type;
	ZoneType m_zone_type;
private:
	WorldManager& m_world_manager;

	Vector3 m_start_pos;
	Vector3 m_end_pos;

	GameData* m_GD;

	Vector3 convertPosition(Vector3 _pos_to_convert, TPSCamera& tps_cam);

	void updateTiles();

	void pathfindRoads();

};

