#include "pch.h"
#include "VBQuad.h"

#include <iostream>

#include "DDSTextureLoader.h"
#include "DrawData.h"
#include "helper.h"
#include "WICTextureLoader.h"


VBQuad::~VBQuad()
{
    delete m_vertices;
}

void VBQuad::init(ID3D11Device* _GD, const std::string& textureFilename, const Vector3& position,
    const Vector3& rotation, const Vector3& scale)
{
    HRESULT hr = CreateDDSTextureFromFile(_GD, L"../Assets/mug.dds", nullptr, &m_pTextureRV);
    assert(hr == S_OK);
    m_pos = position;
    m_scale = scale;
    m_pitch = rotation.x;
    m_roll = rotation.y;
    m_yaw = rotation.z;
    

    int numVerts = 6 * 6 * (m_size - 1) * (m_size - 1);
    m_numPrims = numVerts / 3;
    m_vertices = new myVertex[4];

    m_vertices[0].Pos =  Vector3(-0.5f, 0.5f, 0.0f);
    m_vertices[0].Norm =  Vector3(0, 0, 0);

    m_vertices[1].Pos =  Vector3(0.5f, 0.5f, 0.0f);
    m_vertices[1].Norm =  Vector3(1.0f, 0, 0);

    m_vertices[2].Pos =  Vector3(-0.5f, -0.5f, 0.0f);
    m_vertices[2].Norm =  Vector3(0, 1.0f, 0);

    m_vertices[3].Pos =  Vector3(0.5f, -0.5f, 0.0f);
    m_vertices[3].Norm =  Vector3(1.0f, 1.0f, 0); 
    
    BuildVB(_GD, numVerts, m_vertices);
    
}


void VBQuad::SetTexture(ID3D11Device* _GD, std::string textureName)
{
}

void VBQuad::Draw(DrawData* _DD)
{
    //UINT stride = sizeof(m_vertices);
    //UINT offset = 0;
    //_DD->m_pd3dImmediateContext->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
    //_DD->m_pd3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
    
    //ID3D11ShaderResourceView* textureView = m_pTextureRV;
    //_DD->m_pd3dImmediateContext->PSSetShaderResources(0,1, &textureView);


    m_worldMat = Matrix::CreateScale(m_scale) * Matrix::CreateRotationZ(m_yaw) * Matrix::CreateRotationX(m_pitch) * Matrix::CreateRotationY(m_roll) * Matrix::CreateTranslation(m_pos);
    UpdateConstantBuffer(_DD);
    
    _DD->m_pd3dImmediateContext->Draw(4, 0);

    //VBGO::Draw(_DD);
}
