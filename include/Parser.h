#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include "def.h"
#include "FileManager.h"

using json = nlohmann::json;

class Parser
{
    public:
      Parser();
      std::string parse(const std::string& raw);

    private:
      std::string data;   

    private:
      std::string convert_file_to_str(const std::string &file_name);  
      bool file_exists(const std::string &file_name);
      FileManager file_manager;
};