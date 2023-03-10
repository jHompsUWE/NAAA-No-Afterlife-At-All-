#pragma once
#include <string>
//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <DDSTextureLoader.h>
#include <locale>

class TextureToTxT
{
public:
    static void ConvertToTxtModel(ID3D11Device* _GD, std::string filename);
};
