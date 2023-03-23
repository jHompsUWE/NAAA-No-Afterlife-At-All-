#pragma once

#include <tuple>
#include <queue>
#include <unordered_map>
#include <utility>
#include <map>

#include "SimpleMath.h"
#include "GridLocation.h"
#include "PlaneType.h"
#include "WorldManager.h"

using namespace DirectX;
using namespace SimpleMath;

using Location = std::tuple<int, int>;

namespace std
{
	template<> struct hash<Location>
	{
		std::size_t operator()(const Location& id) const noexcept
		{
			return std::get<0>(id) ^ std::get<0>(id);
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

std::vector<Vector2> pathfinding(GridLocation& start_pos, GridLocation& end_pos,
	WorldManager& world);

void Astar(WorldManager& world,
	Location start, Location end, std::unordered_map<Location, Location>& came_from,
	std::unordered_map<Location, int>& cost_so_far);

std::vector<Location> getNeighbours(WorldManager& world,
	Location start);

int heuristic(Location& a, Location& b);

std::vector<Location> reconstruct_path(Location start, Location end,
	std::unordered_map<Location, Location>& came_from);
