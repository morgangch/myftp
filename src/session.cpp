#include "session.hpp"
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include "constants.hpp"

#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include "constants.hpp"
#include "session.hpp"

Session::Session(int client_socket, const std::string &rootDirectory)
    : clientSocket(client_socket), authenticated(false),
      dataMode(DataMode::PASSIVE), commandCount(0), currentDirectory(rootDirectory),
      rootDirectory(rootDirectory), directory(Directory(rootDirectory))
{
    for (int i = 0; i < MAX_COMMAND_HISTORY; i++) {
        commandHistory.push_back("");
    }
    auth = Auth();
    directory = Directory(rootDirectory);
}

Session::Session(const std::string &rootDirectory)
    : clientSocket(-1), authenticated(false), dataMode(DataMode::PASSIVE),
      commandCount(0), rootDirectory(rootDirectory),
      currentDirectory(rootDirectory), directory(Directory(rootDirectory))
{
    for (int i = 0; i < MAX_COMMAND_HISTORY; i++) {
        commandHistory.push_back("");
    }
    auth = Auth();
}

// Add a default constructor that uses a default root directory
Session::Session()
    : clientSocket(-1), currentDirectory("./"), authenticated(false),
      dataMode(DataMode::PASSIVE), commandCount(0), rootDirectory("./"), directory(Directory("./"))
{
    for (int i = 0; i < MAX_COMMAND_HISTORY; i++) {
        commandHistory.push_back("");
    }
    auth = Auth();
}

void Session::addCommandToHistory(const std::string &command)
{
    if (commandCount < MAX_COMMAND_HISTORY) {
        commandHistory[commandCount++] = command;
    }
}

void Session::sendResponse(const std::string &response)
{
    char *response_cstr = new char[response.size() + 2];
    std::strcpy(response_cstr, response.c_str());
    std::strcat(response_cstr, "\n");
    if (send(clientSocket, response_cstr, response.size() + 1, 0) == -1) {
        std::cerr << "Error sending response to client " << clientSocket
                  << std::endl;
    }
    delete[] response_cstr;
}

void Session::closeSession()
{
    if (clientSocket != -1 && close(clientSocket) == -1) {
        std::cerr << "Error closing client socket" << std::endl;
    }
    reset();
    clientSocket = -1;
}

void Session::reset()
{
    commandCount = 0;
    dataMode = DataMode::PASSIVE;
}

std::string Session::getFiles()
{
    std::string files = "";
    FILE *fp;
    char path[1035];
    std::string command = "ls -l " + currentDirectory;
    fp = popen(command.c_str(), "r");
    if (fp == NULL) {
        std::cerr << "Failed to run command" << std::endl;
        return "";
    }
    while (fgets(path, sizeof(path), fp) != NULL) {
        files += path;
    }
    pclose(fp);
    return files;
}