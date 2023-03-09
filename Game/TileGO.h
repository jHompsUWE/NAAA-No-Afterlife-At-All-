#pragma once
#include "CMOGO.h"
#include "ImageGO2D.h"

enum TileType
{
    // None means no type has been allocated to that space yet
    // Rocks are terrain where players cannot build
    // Liquid is for ports / river crossings
    // Transport is for roads / rail. Areas where buildings cannot go
    // Colors represent differents sins/virtues
    WATER,
    LAVA,
    ROCK,
    ROAD,
    ZONE,
    GATE,
    NONE_TILE    
};

enum ZoneType
{
    BLUE,
    RED,
    GREEN,
    YELLOW,
    BROWN,
    GENERIC,
    ORANGE,
    PURPLE,
    NONE_ZONE
};


class TileGO : public CMOGO
{
public:

    TileGO(string _fileName, ID3D11Device* _pd3dDevice, IEffectFactory* _EF, Vector3 _pos, float _pitch, float _yaw, float _roll);
    ~TileGO();

    void Tick(GameData* _GD) override { _GD; };

private:
    bool connected_;
    bool is_gate_;
    bool empty_;
    int vibes_ = 0;
    vector<Vector3> connected_directions_;
    

    ZoneType zone_type_ = NONE_ZONE;
    TileType tile_type_ = NONE_TILE;        
    
    
};
