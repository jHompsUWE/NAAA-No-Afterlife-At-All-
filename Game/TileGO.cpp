#include "pch.h"
#include "TileGO.h"

#include "helper.h"


TileGO::TileGO(string _fileName, ID3D11Device* _pd3dDevice, IEffectFactory* _EF, Vector3 _pos, float _pitch, float _yaw, float _roll) :CMOGO(_fileName, _pd3dDevice, _EF)
{
    m_pos = _pos;
    m_pitch = _pitch;
    m_roll = _roll;
    m_yaw = _yaw;
    m_scale = Vector3(1.0f, 1.0f, 1.0f);

    Matrix scaleMat = Matrix::CreateScale(m_scale);
    m_rotMat = Matrix::CreateFromYawPitchRoll(m_yaw, m_pitch, m_roll);
    Matrix transMat = Matrix::CreateTranslation(m_pos);

    m_worldMat = m_fudge * scaleMat * m_rotMat * transMat;
}

TileGO::~TileGO()
{
}
