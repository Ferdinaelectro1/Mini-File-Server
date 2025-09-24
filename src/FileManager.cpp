#include "../include/FileManager.h"

FileManager::FileManager(){}

json FileManager::createFile(const std::string& file_name)
{
    json response;
    std::ofstream file(file_name);
    if(file.is_open())
    {
        response["status"] = "OK";
        response["message"] = "File created successfully";
    }
    else
    {
        response["status"] = "ERROR";
        response["message"] = "File already exists";
    }
    response["filename"] = file_name;
    return response;
}

json FileManager::unknowCmd()
{
    json response;
    response["status"] = "ECHEC";
    response["message"] = "Commande inconnu !!";
    return response;
}
