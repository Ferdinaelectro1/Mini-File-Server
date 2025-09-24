#pragma once
#include <fstream>
#include <unordered_map>

enum FileType
{
    BINARY_FILE = std::ios::binary,
    TEXT_FILE 
};

enum cmdType
{
    CREATE_FILE,
    READ_FILE,
    WRITE_FILE,
    REMOVE_FILE,
    CREATE_DIR,
    REMOVE_DIR,
    LIST_DIR_FILE,
    UNKNOW_CMD
};

const std::unordered_map<std::string,cmdType> cmdMaps = {
  {"create",CREATE_FILE},
  {"read",READ_FILE},
  {"write",WRITE_FILE},
  {"removeFile",REMOVE_FILE},
  {"createDir",CREATE_DIR},
  {"removeDir",REMOVE_DIR},
  {"listDirFiles",LIST_DIR_FILE}
};

inline cmdType getCmdType(const std::string& cmdStr)
{
    auto it = cmdMaps.find(cmdStr);
    if(it != cmdMaps.end())
       return it->second;
    else
       return UNKNOW_CMD;
}