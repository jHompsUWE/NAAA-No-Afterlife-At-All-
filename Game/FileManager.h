#pragma once

#include <fstream>
#include <iostream>
#include "Manager.h"
#include "SaveStruct.h"
#include "json.hpp"

#define GET_VARIABLE_NAME(Variable) (#Variable)

using json = nlohmann::json;


class FileManager : public Manager
{
public:
    void awake() override;
    void update(GameData& _game_data) override;

    ////////////////////////////////////////////////////////////
    /// \brief Save the game.
    ////////////////////////////////////////////////////////////
    void save();

    ////////////////////////////////////////////////////////////
    /// \brief Load the save file.
    ////////////////////////////////////////////////////////////
    void load();

    ////////////////////////////////////////////////////////////
    /// \brief Converts values to json object.
    ////////////////////////////////////////////////////////////
    void to_json();

    ////////////////////////////////////////////////////////////
    /// \brief Check if the save file exists.
    ////////////////////////////////////////////////////////////
    inline bool file_exist(const std::string& path);

    
private:
    std::string filepath = "../Data/";
    std::ifstream file;
    json obj;
    std::unique_ptr<SaveStruct> save_struct;
    int test_val;
    
};
