#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <sys/socket.h>
#include "constants.hpp"

class Client {
public:
    Client(int socket_fd);
    ~Client();

    void setUsername(const std::string& username);

    void setAuthenticated(bool authenticated);
    bool isAuthenticated() const;

    int getSocket() const;
    void closeConnection();
    std::string receiveCommand();
    void sendResponse(const std::string& response);
    void sendData(const char* data, size_t size);
    void receiveData(char* buffer, size_t size);
    int getSocketFd() const;

private:
    int socket_fd;
    std::string username;
    bool authenticated;
    char buffer[BUFFER_SIZE];
};

#endif // CLIENT_HPP