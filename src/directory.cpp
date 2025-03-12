/*
** EPITECH PROJECT, 2025
** myftp
** File description:
** directory
*/

#include "directory.hpp"

Directory::Directory(const std::string &root) : rootDirectory(root)
{
}

std::string Directory::getRootDirectory() const
{
    return rootDirectory;
}

bool Directory::isRootDirectory() const
{
    return currentDirectory == rootDirectory;
}

bool Directory::changeDirectory(const std::string &new_directory)
{
    if (new_directory == "..") {
        if (currentDirectory == rootDirectory) {
            return false;
        }
        currentDirectory = currentDirectory.substr(
            0, currentDirectory.find_last_of('/'));
    } else {
        std::string new_path = currentDirectory + "/" + new_directory;
        if (access(new_path.c_str(), F_OK) == -1) {
            return false;
        }
        currentDirectory = new_path;
    }
    return true;
}

bool Directory::changeToParentDirectory()
{
    if (currentDirectory == rootDirectory) {
        return false;
    }
    currentDirectory = currentDirectory.substr(
        0, currentDirectory.find_last_of('/'));
    return true;
}

std::string Directory::printWorkingDirectory() const
{
    return currentDirectory;
}

bool Directory::createDirectory(const std::string &directory)
{
    std::string new_directory = currentDirectory + "/" + directory;
    if (access(new_directory.c_str(), F_OK) != -1) {
        return false;
    }
    mkdir(new_directory.c_str(), 0777);
    return true;
}

bool Directory::removeDirectory(const std::string &directory)
{
    std::string new_directory = currentDirectory + "/" + directory;
    if (access(new_directory.c_str(), F_OK) == -1) {
        return false;
    }
    rmdir(new_directory.c_str());
    return true;
}

bool Directory::removeFile(const std::string &file)
{
    std::string new_file = currentDirectory + "/" + file;
    if (access(new_file.c_str(), F_OK) == -1) {
        return false;
    }
    remove(new_file.c_str());
    return true;
}

bool Directory::isDirectory(const std::string &directory) const
{
    std::string new_directory = currentDirectory + "/" + directory;
    struct stat sb;
    if (stat(new_directory.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode)) {
        return true;
    }
    return false;
}

bool Directory::isFile(const std::string &file) const
{
    std::string new_file = currentDirectory + "/" + file;
    struct stat sb;
    if (stat(new_file.c_str(), &sb) == 0 && S_ISREG(sb.st_mode)) {
        return true;
    }
    return false;
}

bool Directory::isDirectoryEmpty(const std::string &directory) const
{
    std::string new_directory = currentDirectory + "/" + directory;
    DIR *dir = opendir(new_directory.c_str());
    if (dir == NULL)
        return true;
    struct dirent *entry;
    if ((entry = readdir(dir)) != NULL) {
        closedir(dir);
        return false;
    }
    closedir(dir);
    return true;
}
