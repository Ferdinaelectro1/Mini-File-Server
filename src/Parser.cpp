#include "../include/Parser.h"

Parser::Parser(){}

std::string Parser::parse(const std::string& raw)
{
    json request = json::parse(raw);
    json response ;
    cmdType cmdT = getCmdType(request["cmd"]);//récupérer le type de commande
    //std::cout << cmdT << std::endl;
    switch (cmdT)
    {
    case cmdType::CREATE_DIR :
        response = file_manager.createDir(request["args"][0]);
        break;
    case cmdType::CREATE_FILE :
        response = file_manager.createFile(request["args"][0]);
        break;
    case cmdType::LIST_DIR_FILE :
        /* code */
        break;
    case cmdType::READ_FILE :
        /* code */
        break;
    case cmdType::REMOVE_DIR :
        response = file_manager.removeDir(request["args"][0]);
        break;
    case cmdType::UNKNOW_CMD :
        response =  file_manager.unknowCmd();
        break;
    case cmdType::WRITE_FILE :
        /* code */
        break;  
    case cmdType::REMOVE_FILE :
        response = file_manager.removeFile(request["args"][0]);
        break;     
    default:
        break;
    }
    return response.dump(4);
}

bool Parser::file_exists(const std::string &file_name)
{
    if(file_name == "test.txt")
    {
        return true;
    }
    return false;
}

std::string Parser::convert_file_to_str(const std::string &file_name)//supp
{
    std::ifstream file(file_name);
    if(!file)
    {
        std::cerr << "Erreur lors de l'ouverture du fichier \""<<file_name<<"\""<<std::endl;
        return "None";
    }
    std::string content((std::istreambuf_iterator<char>(file)),std::istreambuf_iterator<char>());
    file.close();
    return content;
}