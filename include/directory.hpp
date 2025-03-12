/*
** EPITECH PROJECT, 2025
** myftp
** File description:
** directory
*/

#ifndef DIRECTORY_HPP_
#define DIRECTORY_HPP_

#include <string>
#include <iostream>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

class Directory {
    public:
        Directory(const std::string &root);
        std::string getRootDirectory() const;
        std::string currentDirectory;
        bool isRootDirectory() const;
        bool changeDirectory(const std::string &new_directory);
        bool changeToParentDirectory();
        std::string printWorkingDirectory() const;
        bool createDirectory(const std::string &directory);
        bool removeDirectory(const std::string &directory);
        bool removeFile(const std::string &file);
        bool isDirectory(const std::string &directory) const;
        bool isFile(const std::string &file) const;
        bool isDirectoryEmpty(const std::string &directory) const;
    private:
        std::string rootDirectory;
};

#endif /* !DIRECTORY_HPP_ */