#pragma once

#include <vector>
#include <map>

#include "Manager.h"
#include "GridLocation.h"
#include "PlaneType.h"
#include <iostream>

class WorldManager :
    public Manager
{
public:
    WorldManager();
    ~WorldManager();

    void setConnected(GridLocation& _grid_location, PlaneType _plane);

    // 1x1 update
    void updateVibes(GridLocation& _grid_location, PlaneType _plane);

    void update() override;

private:
    void calculateEfficiency(GridLocation& _grid_location, PlaneType _plane);

    int adjacencyScoreHeaven(GridLocation& _grid_location);
    int adjacencyScoreHell(GridLocation& _grid_location);

    int getIndex(Vector2 position);
    bool withinRange(Vector2 position);

    int m_num_of_planes;

    int m_grid_x;
    int m_grid_y;

    std::map<PlaneType, std::vector<GridLocation>> m_world;

    std::map<int, std::vector<Vector2>> range_map;
};

