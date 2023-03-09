#include "pch.h"
#include "TileGO.h"

#include "helper.h"


TileGO::TileGO(string _fileName, ID3D11Device* _pd3dDevice, IEffectFactory* _EF, Vector3 _pos, float _pitch, float _yaw, float _roll) :CMOGO(_fileName, _pd3dDevice, _EF)
{
    m_pos = _pos;
    m_pitch = _pitch;
    m_roll = _roll;
    m_yaw = _yaw;
    //
    // //if we've not created it yet do so now
    // if (!s_pRasterState)
    // {
    //     //Setup Raster State
    //     D3D11_RASTERIZER_DESC rasterDesc;
    //     rasterDesc.AntialiasedLineEnable = false;
    //     rasterDesc.CullMode = D3D11_CULL_BACK;
    //     rasterDesc.DepthBias = 0;
    //     rasterDesc.DepthBiasClamp = 0.0f;
    //     rasterDesc.DepthClipEnable = true;
    //     rasterDesc.FillMode = D3D11_FILL_SOLID;
    //     rasterDesc.FrontCounterClockwise = false;
    //     rasterDesc.MultisampleEnable = false;
    //     rasterDesc.ScissorEnable = false;
    //     rasterDesc.SlopeScaledDepthBias = 0.0f;
    //
    //     // Create the rasterizer state from the description we just filled out.
    //     HRESULT hr = _pd3dDevice->CreateRasterizerState(&rasterDesc, &s_pRasterState);
    //     assert(hr == S_OK);
    // }
    //
    // string filePath = "../Models/Tile/" + _fileName + ".cmo";
    //
    // wchar_t* file = Helper::charToWChar(filePath.c_str());
    //
    // m_model = Model::CreateFromCMO(_pd3dDevice, file, *_EF);
}

TileGO::~TileGO()
{
}
