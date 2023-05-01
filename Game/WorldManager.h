#pragma once

#include <vector>
#include <map>

#include "Manager.h"
#include "GridLocation.h"
#include "PlaneType.h"
#include <iostream>
#include "DrawData.h"

class SoulManager;

class WorldManager :
    public Manager
{
public:
    WorldManager(int size_x, int size_y);
    ~WorldManager();

    void init(Microsoft::WRL::ComPtr<ID3D11DeviceContext1> _device, DirectX::IEffectFactory* _fxFactory);

    void setConnected(GridLocation& _grid_location);
    void resetConnections();

    // 1x1 update
    void updateVibes(GridLocation& _grid_location);

    void update(GameData& _game_data) override;

    void lateUpdate(GameData& _game_data) override;

    void render(DrawData* _DD) override;

    std::map<PlaneType, std::vector<std::unique_ptr<GridLocation>>>& getWorld();

    int getIndex(Vector2 position);
    bool withinRange(Vector2 position);

private:
    Microsoft::WRL::ComPtr<ID3D11DeviceContext1>    m_d3dContext;

    void calculateEfficiency(GridLocation& _grid_location);

    int adjacencyScoreHeaven(GridLocation& _grid_location);
    int adjacencyScoreHell(GridLocation& _grid_location);

    void generateWorld();

    int m_grid_x;
    int m_grid_y;
    int m_total_tiles;
    
    std::map<PlaneType, std::vector<std::unique_ptr<GridLocation>>> m_world;

    std::map<int, std::vector<Vector2>> range_map;
};

