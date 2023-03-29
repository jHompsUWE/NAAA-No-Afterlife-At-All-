#include "pch.h"
#include "DataGenerator.h"

#include "GameData.h"
#include "GameManager.h"

std::pair<std::string, std::string> DataGenerator::GenerateData()
{
    std::srand(std::time(nullptr));
    auto dataList = GameManager::get()->getFileManagerV2()->GetJson("souls_name");    
    
    if (!dataList->empty())
    {
        string name =  (*dataList)["names"][std::rand() % 30];
        string bio = GenerateBio(name, *dataList);
        cout << bio << endl;
        return std::make_pair(name, bio);        
    }
    return std::make_pair("", "");
}

std::string DataGenerator::GenerateBio(std::string& name, json& dataList)
{
    int hobbyIndex1, hobbyIndex2, hobbyIndex3;
    do {
        hobbyIndex1 = std::rand() % 40;
        hobbyIndex2 = std::rand() % 40;
        hobbyIndex3 = std::rand() % 40;
    } while (hobbyIndex1 == hobbyIndex2 || hobbyIndex1 == hobbyIndex3 || hobbyIndex2 == hobbyIndex3);

    string bio = name + " is a " + dataList["ages"][std::rand() % 82].get<std::string>() + " years-old " + dataList["jobs"][std::rand() % 40].get<std::string>() + " who enjoys " + dataList["hobbies"][hobbyIndex1].get<std::string>() + ", " + dataList["hobbies"][hobbyIndex2].get<std::string>() + ", and " + dataList["hobbies"][hobbyIndex3].get<std::string>();
    return bio;
}
