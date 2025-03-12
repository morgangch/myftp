#include "session.hpp"
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include "constants.hpp"

Session::Session(int client_socket)
    : clientSocket(client_socket), dataMode(DataMode::PASSIVE)
{
    commandCount = 0;
    for (int i = 0; i < MAX_COMMAND_HISTORY; i++) {
        commandHistory.push_back("");
    }
    authenticated = false;
    auth = Auth();
}

Session::Session() : clientSocket(-1), dataMode(DataMode::PASSIVE)
{
    commandCount = 0;
    for (int i = 0; i < MAX_COMMAND_HISTORY; i++) {
        commandHistory.push_back("");
    }
    authenticated = false;
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
