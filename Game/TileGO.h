#pragma once
#include "CMOGO.h"
#include "ImageGO2D.h"

#include "TileType.h"
#include "ZoneType.h"
#include "GridData.h"


class TileGO : public CMOGO
{
public:

    TileGO(string _fileName, ID3D11Device* _pd3dDevice, IEffectFactory* _EF, Vector3 _pos, float _pitch, float _yaw, float _roll);
    ~TileGO() override;

    void Tick(GameData* _GD) override { _GD; };

private:
    
    
};
