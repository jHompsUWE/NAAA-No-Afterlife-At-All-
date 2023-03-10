#pragma once

#include <vector>
#include <map>

#include "Manager.h"
#include "GridLocation.h"
#include "PlaneType.h"
#include <iostream>
#include "DrawData.h"

class WorldManager :
    public Manager
{
public:
    WorldManager();
    ~WorldManager();

    void init(Microsoft::WRL::ComPtr<ID3D11Device1> _device, DirectX::IEffectFactory* _fxFactory);

    void setConnected(GridLocation& _grid_location, PlaneType _plane);

    // 1x1 update
    void updateVibes(GridLocation& _grid_location, PlaneType _plane);

    void update(DX::StepTimer const& _timer) override;

    void render(DrawData* _DD);

    std::map<PlaneType, std::vector<std::unique_ptr<GridLocation>>>& getWorld();

private:
    void calculateEfficiency(GridLocation& _grid_location, PlaneType _plane);

    int adjacencyScoreHeaven(GridLocation& _grid_location);
    int adjacencyScoreHell(GridLocation& _grid_location);

    int getIndex(Vector2 position);
    bool withinRange(Vector2 position);

    int m_num_of_planes;

    int m_grid_x;
    int m_grid_y;

    std::map<PlaneType, std::vector<std::unique_ptr<GridLocation>>> m_world;

    std::map<int, std::vector<Vector2>> range_map;
};

