#pragma once
#include "VBCube.h"
#include "VBGO.h"
#include "vertex.h"
#include <DirectXMath.h>
#include <DDSTextureLoader.h>
#include <SpriteBatch.h>
#include <SpriteFont.h>

class VBQuad : public VBGO
{
public:
    VBQuad(){};
    virtual ~VBQuad();

    //initialise the Veretx and Index buffers for the cube
    void init(ID3D11Device* _GD, const std::string& textureFilename, const Vector3& position, const Vector3& rotation, const Vector3& scale);
    void SetTexture(ID3D11Device* _GD, std::string textureName);
    void updateMatrix(ID3D11DeviceContext* context, SpriteBatch* spriteBatch);
    void Draw(DrawData* _DD) override;

protected:
    

    int m_size = 0;
    myVertex* m_vertices = nullptr;
    D3D11_TEXTURE2D_DESC Desc;

private:
    UINT stride;
    UINT offset;
};

