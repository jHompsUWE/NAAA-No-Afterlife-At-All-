#pragma once
#include <map>
#include "FileManagerV2.h"

class DataGenerator
{
public:
    static std::pair<std::string, std::string> GenerateData();

private:
    static std::string GenerateBio(std::string& name, json& dataList);
};
