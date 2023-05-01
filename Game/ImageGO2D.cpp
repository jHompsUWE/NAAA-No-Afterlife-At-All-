#include "pch.h"
#include "ImageGO2D.h"
#include "DDSTextureLoader.h"
#include "DrawData2D.h"
#include "GameData.h"
#include "helper.h"
#include <iostream>
#include "Mouse.h"

ImageGO2D::ImageGO2D() : m_pTextureRV(nullptr)
{

}

ImageGO2D::ImageGO2D(string _fileName, ID3D11Device* _GD) : m_pTextureRV(nullptr)
{
	string fullfilename = "../Assets/" + _fileName + ".dds";
	HRESULT hr = CreateDDSTextureFromFile(_GD, Helper::charToWChar(fullfilename.c_str()), nullptr, &m_pTextureRV);
	if (hr != S_OK)
	{
		CreateDDSTextureFromFile(_GD, L"../Assets/white.dds", nullptr, &m_pTextureRV);
		cout << "Missing Texture : " << _fileName << endl;
	}

	//this nasty thing is required to find out the size of this image!
	ID3D11Resource* pResource;
	m_pTextureRV->GetResource(&pResource);
	((ID3D11Texture2D*)pResource)->GetDesc(&Desc);

	m_origin = 0.5f * Vector2((float)Desc.Width, (float)Desc.Height);//around which rotation and scaing is done



	if (hr != S_OK)
	{
		SetScale(20.0f);
		m_colour = Colors::HotPink;
	}

	bounds = { (long)m_origin.x,(long)m_origin.y,(long)(Desc.Width * m_scale.x), (long)(Desc.Height * m_scale.y) };

}






ImageGO2D::~ImageGO2D()
{
	if (m_pTextureRV)
	{
		m_pTextureRV->Release();
		m_pTextureRV = nullptr;
	}

}

void ImageGO2D::SetUV(RECT* animated_uv)
{
	uv_ref = animated_uv;
}

void ImageGO2D::CalculateBounds()
{
	ID3D11Resource* pResource;
	m_pTextureRV->GetResource(&pResource);
	((ID3D11Texture2D*)pResource)->GetDesc(&Desc);

	m_origin = 0.5f * Vector2((float)Desc.Width, (float)Desc.Height);//around which rotation and scaing is done

	bounds = { (long)m_origin.x,(long)m_origin.y,(long)(Desc.Width * m_scale.x), (long)(Desc.Height * m_scale.y) };
}






void ImageGO2D::Tick(GameData* _GD)
{
	
}



void ImageGO2D::Draw(DrawData2D* _DD)
{
	//nullptr can be changed to a RECT* to define what area of this image to grab
	//you can also add an extra value at the end to define layer depth
	//right click and "Go to Defintion/Declaration" to see other version of this in DXTK

	//_DD->m_Sprites->Draw(m_pTextureRV, m_pos, uv_ref, m_colour, m_rotation, m_origin, m_scale, SpriteEffects_None);

	if (renderable)
	{
		_DD->m_Sprites->Draw(m_pTextureRV, m_pos, uv_ref, m_colour, m_rotation, m_origin, m_scale, SpriteEffects_None);
	}
}

Vector2 ImageGO2D::GetImageSize()
{
	return Vector2(bounds.width, bounds.height);
}



