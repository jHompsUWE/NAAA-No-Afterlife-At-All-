#include "pch.h"
#include "FileManager.h"



void FileManager::awake()
{
    save_struct = std::make_unique<SaveStruct>();
    if (file_exist( filepath + "save.json"))
    {
        // load file
        //load();
    }    
    Manager::awake();
}

void FileManager::update(DX::StepTimer const& _timer)
{
    //std::cout << test_val << std::endl;
}

void FileManager::save()
{ 
    to_json();
    std::ofstream file(filepath + "save.json");
    save_struct->current_money = test_val;
    file << obj;
    file.close();
    
}

void FileManager::load()
{
    std::ifstream file(filepath + "save.json");
    json json_file = json::parse(file);
    file.close();

    if (!json_file.empty())
    {
        test_val = json_file["Gold"];        
    }
    std::cout << test_val << std::endl;
}

void FileManager::to_json()
{
   obj = json{
       {"Gold", 10},
       {"Bool", true},
       {"Third", 2}
   };
}

bool FileManager::file_exist(const std::string& path)
{
    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0);
}
