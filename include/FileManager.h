#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include <sys/types.h>
#include <vector>
#include <nlohmann/json.hpp>

namespace fs = std::filesystem;
using json = nlohmann::json;

inline void print(const std::string& msg)
{
    #ifdef DEBUG
      std::cout << msg << std::endl;
    #endif
}

class FileManager
{
    public:
       FileManager();
       std::string readStringFile(const std::string &file_name);
       char* readCharFile(const std::string &file_name);
       uint8_t* readByteFile(const std::string &file_name);
       json createFile(const std::string& file_name);
       json createFile(const std::string& file_name,const fs::path& dir_path);
       json removeFile(const std::string& file_name);
       json removeFile(const std::string& file_name,const fs::path& dir_path);
       json writeToFile(const std::string& file_name);
       json writeToFile(const std::string& file_name,const fs::path& dir_path);
       json createDir(const fs::path& dir_path);
       json createDirs(const fs::path& dir_path);
       json removeDir(const fs::path& dir_path);
       json renameDir(const fs::path& dir_path);
       json unknowCmd();
       int  getDirFilesLength(const fs::path& dir_path);
       std::vector<std::string> getDirFiles(const fs::path& dir_path);
       std::string* getDirFiles();


    private:
};