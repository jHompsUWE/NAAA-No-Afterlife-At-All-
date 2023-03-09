#include "pch.h"
#include "TextureToTxT.h"

#include <codecvt>

struct ImgVertex {
    float x, y, z;
    float u, v;
};
void TextureToTxT::ConvertToTxtModel(ID3D11Device* _GD, std::string filename)
{
    int width, height, channels;
    width = 360;
    height = 326;
    // // Load the image
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    std::wstring wstr = converter.from_bytes(filename);
    //ID3D11Resource* resource;
    //Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;
    //DirectX::CreateDDSTextureFromFile(nullptr, L"../Game/mug.jpg", &resource, nullptr);
    //DirectX::CreateDDSTextureFromFile(_GD, L"../Game/mug.jpg", nullptr, &resource);
    
    // Get the texture from the resource
    
    
    // Get the texture description
    //D3D11_TEXTURE2D_DESC desc;
    //texture->GetDesc(&desc);
    
    //width = desc.Width;
    //height = desc.Height;
    
    // Load image file using stb_image
   
    // unsigned char* data_conv = stbi_load("../Game/mug.jpg", &width, &height, &channels, STBI_rgb_alpha);
    // if (!data_conv)
    // {
    //     std::cerr << "Failed to load image." << std::endl;
    // }

    // Generate vertex and index data
    std::vector<ImgVertex> vertices;
    std::vector<unsigned int> indices;
    for(int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            ImgVertex vertex = {
                static_cast<float>(x) - width / 2.0f,
                static_cast<float>(y) - height / 2.0f,
                0.0f,
                static_cast<float>(x) / static_cast<float>(width),
                static_cast<float>(y) / static_cast<float>(height)					
            };
            vertices.push_back(vertex);
        }
    }
    for (unsigned int i = 0; i < vertices.size() - width; i++)
    {
        if ((i + 1) % width == 0) continue;
        indices.push_back(i);
        indices.push_back(i + width);
        indices.push_back(i + 1);

        indices.push_back(i + 1);
        indices.push_back(i + width);
        indices.push_back(i + width + 1);
    }

    // Write vertex and index data to file
    std::ofstream file("../Game/download.txt");
    file << "T\n";
    file << L"download" << "\n";
    file << vertices.size() << "\n";

    for (const auto& vertex : vertices) {
        file << vertex.x << ' ' << vertex.y << ' ' << vertex.z << ' '
            << vertex.u << ' ' << vertex.v << '\n';
    }

    file << indices.size() / 3 << '\n';
    for (unsigned int i = 0; i < indices.size() - 2; i += 3) {
        file << i << ' ' << indices[i] << ' ' << indices[i + 1] << ' ' << indices[i + 2] << '\n';
    }
		
    // Clean up resources
    //stbi_image_free(data_conv);
    file.close();
}

