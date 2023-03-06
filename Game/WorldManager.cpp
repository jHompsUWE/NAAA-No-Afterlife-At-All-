#include "pch.h"
#include "WorldManager.h"

WorldManager::WorldManager()
{
	m_num_of_planes = 3;

	m_grid_x = 10;
	m_grid_y = 10;

	m_world[PlaneType::Earth].reserve(m_grid_x * m_grid_y);
	m_world[PlaneType::Heaven].reserve(m_grid_x * m_grid_y);
	m_world[PlaneType::Hell].reserve(m_grid_x * m_grid_y);
	
}

WorldManager::~WorldManager()
{

}

void WorldManager::setConnected(GridLocation _grid_location, PlaneType _plane)
{
	// Call when road is placed, set connection status of tiles affected

	Vector2 start = _grid_location.getGridData().m_position;

	Vector2 directions[24] =
	{
		{1, 0}, {2, 0}, {3, 0}, // right
		{0, -1}, {0, -2}, {0, -3}, // back
		{-1, 0}, {-2, 0}, {-3, 0}, // left
		{0, 1}, {0, 2}, {0, 3}, // front
		{1, 1}, {1, 2}, {2, 1}, // top right
		{1, -1}, {1, -2}, {2, -1}, // bottom right
		{-1, 1}, {-1, 2}, {-2, 1}, // top left
		{-1, -1}, {-1, -2}, {-2, -1} // bottom left
	};

	for (Vector2 dir : directions)
	{
		Vector2 current = { start.x + dir.x, start.y + dir.y };

		if (!withinRange(current)) continue;

		m_world[_plane][getIndex(current)].getGridData().m_connected = true;
	}
}

void WorldManager::updateVibes(GridLocation _grid_location, PlaneType _plane)
{
	// To be replaced by building radius when ready
	int radius = 3;
	// _grid_location.getGridData().m_stored_building.getStats().radius;
	
	// To be replaced by building vibes when ready
	int vibe = 1;
	// _grid_location.getGridData().m_stored_building.getStats().vibes;

	Vector2 start_position = _grid_location.getGridData().m_position;

	std::vector<Vector2> range;
	range.reserve(25);

	switch (radius)
	{
	case 1:
		range =
		{
			{1, 0}, {-1, 0}, {0, 1}, {0, -1}, Vector2::Zero // Up, Down, Left, Right, self
		};
		break;
	case 2:
		range =
		{
			{1, 0}, {2, 0}, {-1, 0}, {-2, 0}, // Left, Right
			{0, 1}, {0, 2}, {0, -1}, {0, -2}, // Up, Down
			{1, 1}, {1, -1}, {-1, 1}, {-1, -1}, Vector2::Zero // Corners, self
		};
		break;
	case 3:
		range =
		{
			{1, 0}, {2, 0}, {3, 0}, // right
			{0, -1}, {0, -2}, {0, -3}, // back
			{-1, 0}, {-2, 0}, {-3, 0}, // left
			{0, 1}, {0, 2}, {0, 3}, // front
			{1, 1}, {1, 2}, {2, 1}, // top right
			{1, -1}, {1, -2}, {2, -1}, // bottom right
			{-1, 1}, {-1, 2}, {-2, 1}, // top left
			{-1, -1}, {-1, -2}, {-2, -1}, // bottom left
			Vector2::Zero // self
		};
		break;
	default:
		range =
		{
			Vector2::Zero // self
		};
		break;
	}

	for (Vector2 tile : range)
	{
		Vector2 pos = { start_position.x + tile.x, start_position.y + tile.y };

		if (!withinRange(pos)) continue;

		m_world[_plane][getIndex(pos)].getGridData().vibes += vibe;
	}
}

void WorldManager::update()
{

}

int WorldManager::getIndex(Vector2 position)
{
	return position.x + position.y * m_grid_x;
}

bool WorldManager::withinRange(Vector2 position)
{
	if (position.x > m_grid_x - 1 || position.x < 0 ||
		position.y > m_grid_y - 1 || position.y < 0) return false;
	return true;
}

