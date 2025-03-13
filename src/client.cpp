#include "client.hpp"
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>

Client::Client(int socket_fd) : socket_fd(socket_fd), authenticated(false) {
    memset(buffer, 0, sizeof(buffer));
}

void Client::sendResponse(const std::string& response) {
    write(socket_fd, response.c_str(), response.size());
}

std::string Client::receiveCommand() {
    ssize_t bytes_received = read(socket_fd, buffer, sizeof(buffer) - 1);
    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';
        return std::string(buffer);
    }
    return "";
}

bool Client::isAuthenticated() const {
    return authenticated;
}

void Client::setAuthenticated(bool auth_status) {
    authenticated = auth_status;
}

int Client::getSocketFd() const {
    return socket_fd;
}

void Client::closeConnection() {
    close(socket_fd);
}