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

json FileManager::createDir(const fs::path& dir_path)
{
    json response;
    if(fs::create_directory(dir_path))
    {
        response["status"] = "SUCCES";
        response["message"] = "Directory Create Succesfull";
    }
    else
    {
        response["status"] = "ERROR";
        response["message"] = "Directory already exists";
    }
    response["dirName"] = dir_path;
    return response;
}

json FileManager::removeFile(const std::string& file_name)
{
    json response;
    if(fs::remove(file_name))
    {
        response["status"] = "SUCCES";
        response["message"] = "Fichier supprimé";
    }
    else
    {
        response["status"] = "ERROR";
        response["message"] = "Impossible de supprimer (inexistant ?)";
    }
    response["filName"] = file_name;
    return response;
}

json FileManager::removeDir(const std::string& dir_path)
{
    json response;
    if(fs::remove_all(dir_path))
    {
        response["status"] = "SUCCES";
        response["message"] = "Dossier supprimé";
    }
    else
    {
        response["status"] = "ERROR";
        response["message"] = "Impossible de supprimer le dossier (inexistant ?)";
    }
    response["dirName"] = dir_path;
    return response;
}