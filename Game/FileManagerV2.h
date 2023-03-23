#pragma once
#include <fstream>

#include "Manager.h"
#include "json.hpp"
#include <sstream>

using json = nlohmann::json;
using namespace std;

class FileManagerV2 : public Manager
{
public:
    void awake() override;
    void update(GameData& _game_data) override;

    json *GetJson(const std::string &fileName) const;
    string GetFile(const std::string &fileName) const;

    void LoadGame();
    void SaveGame();

private:

    void AddFile(const std::string &fileName, ifstream *file);
    void AddJson(const std::string &fileName, ifstream *file);
    
    // Main path
    string filepath_ = "../Data/";

    // Location
    // Save file
    string saveFilePath_ = filepath_ + "SaveFile.json";    

    // Input file
    string default_bindings_file_name = filepath_ + "keybinds_default.json";
    string custom_bindings_file_name = filepath_ + "keybinds_custom.json";

    typedef std::map<std::string, ifstream *> FilesMap;
    FilesMap files;

    typedef map<string, json *> JsonMap;
    JsonMap jsonFiles;


    // Remove
    bool doOnce = true;
    
};
