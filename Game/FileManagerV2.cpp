#include "pch.h"
#include "FileManagerV2.h"

#include "GameManager.h"

void FileManagerV2::awake(GameData& _game_data)
{
    // Add json files
    AddFile("SaveFile", new ifstream(saveFilePath_));
    AddFile("keybinds_default", new ifstream(default_bindings_file_name));
    AddFile("keybinds_custom", new ifstream(custom_bindings_file_name));
    AddFile("buildings_table", new ifstream(filepath_ + "buildings_table.json"));
    AddFile("souls_name", new ifstream(filepath_ + "souls_name.json"));
    AddFile("remote_buttons", new ifstream(filepath_ + "remote_buttons.json"));
    AddFile("option_buttons", new ifstream(filepath_ + "option_buttons.json"));
    

    for (auto & file : files)
    {
        if (file.second->good())
        {
            AddJson(file.first, file.second);
        }
        else
        {
            ofstream newFile(filepath_ + file.first + ".json");
            if (newFile.good())
            {
                AddJson(file.first, file.second);
            }
        }
        file.second->close();
    }
}

void FileManagerV2::update(GameData& _game_data)
{
}

void FileManagerV2::AddFile(const std::string &fileName, ifstream *file)
{
    files.insert(std::make_pair(fileName, file));
}

void FileManagerV2::AddJson(const std::string& fileName, ifstream* file)
{
    json *parse = new json(json::parse(*(file)));
    jsonFiles.insert(make_pair(fileName, parse)); 
}
json *FileManagerV2::GetJson(const std::string &fileName) const
{
    JsonMap::const_iterator fileNameIt = jsonFiles.find(fileName);
    if (fileNameIt != jsonFiles.end())
    {
        return fileNameIt->second;
    }
    return nullptr;
}

string FileManagerV2::GetFile(const std::string& fileName) const
{
    FilesMap::const_iterator fileNameIt = files.find(fileName);
    if (fileNameIt != files.end())
    {
        std::stringstream buffer;
        buffer << (*fileNameIt).second->rdbuf();
        cout << buffer.str() << endl;
        return buffer.str();
    }
    return "";
}

void FileManagerV2::LoadGame()
{
    auto saveFile = GetJson("SaveFile");
    if (!saveFile->empty())
    {
        auto money = (*saveFile)["economy_manager"]["money"];
        cout << money << endl;
    }
}

void FileManagerV2::SaveGame()
{
    auto saveFile = GetJson("SaveFile");
    if (!saveFile->empty())
    {
        ofstream output(saveFilePath_);
        // Stuff that needs to be saved
        (*saveFile)["economy_manager"]["money"] = 12;
        output << (*saveFile);
        output.close();
    }
}

