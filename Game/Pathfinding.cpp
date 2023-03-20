#include "pch.h"
#include "Pathfinding.h"

std::vector<Vector2> pathfinding(GridLocation& start_pos, GridLocation& end_pos,
	WorldManager& world)
{
	Location start = start_pos.getGridData().m_position;
	Location end = end_pos.getGridData().m_position;

	int tile_cost = 1;

	std::vector<Vector2> tiles_to_visit;
	tiles_to_visit.reserve(100);

	std::unordered_map<Location, Location> came_from;
	std::unordered_map<Location, int> cost_so_far;

	Astar(world, start, end, came_from, cost_so_far);

	for (auto& tile : reconstruct_path(start, end, came_from))
	{
		tiles_to_visit.push_back({ float(std::get<0>(tile)), float(std::get<1>(tile)) });
	}

	return tiles_to_visit;
}

void Astar(WorldManager& world,
	Location start, Location end, std::unordered_map<Location, Location>& came_from,
	std::unordered_map<Location, int>& cost_so_far)
{
	PriorityQueue frontier;

	frontier.put(start, 0);

	came_from[start] = start;
	cost_so_far[start] = 0;

	while (!frontier.empty())
	{
		Location current = frontier.get();

		if (current == end)
		{
			break;
		}

		for (auto node : getNeighbours(world, current))
		{
			int new_cost = cost_so_far[current] + 1;

			if (cost_so_far.find(node) == cost_so_far.end() ||
				new_cost < cost_so_far[node])
			{
				cost_so_far[node] = new_cost;
				int priority = new_cost + heuristic(node, end);
				frontier.put(node, priority);
				came_from[node] = current;
			}
		}
	}
}

std::vector<Location> getNeighbours(WorldManager& world,
	Location start)
{
	std::vector<Location> neighbours;
	neighbours.reserve(4);

	std::tuple<int, int> DIRS[4] = {
		{1, 0},
		{-1, 0},
		{0, 1},
		{0, -1}
	};

	for (auto direction : DIRS)
	{
		Vector2 current = { float(std::get<0>(start)) + float(std::get<0>(direction)),
	  float(std::get<1>(start)) + float(std::get<1>(direction)) };

		if (world.withinRange(current))
		{
			neighbours.push_back(std::make_tuple<int, int>(int(current.x), int(current.y)));
		}
	}

	return neighbours;
}

int heuristic(Location& a, Location& b)
{
	return (abs(std::get<0>(a) - abs(std::get<0>(b))) +
		abs(std::get<1>(a) - abs(std::get<1>(b))));
}


std::vector<Location> reconstruct_path(
	Location start, Location end,
	std::unordered_map<Location, Location>& came_from)
{
	std::vector<Location> path;
	path.reserve(100);

	Location current = end;

	if (came_from.find(end) == came_from.end())
	{
		return path; // nothing found
	}

	while (current != start)
	{
		path.push_back(current);
		current = came_from[current];
	}
	path.push_back(start); // adds start
	std::reverse(path.begin(), path.end());

	return path;
}