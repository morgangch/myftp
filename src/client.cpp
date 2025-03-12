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
    send(socket_fd, response.c_str(), response.length(), 0);
}

std::string Client::receiveCommand() {
    ssize_t bytes_received = recv(socket_fd, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received > 0) {
        buffer[bytes_received] = '\0'; // Null-terminate the received string
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