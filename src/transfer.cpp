#include "transfer.hpp"
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>

Transfer::Transfer() {}

Transfer::~Transfer() {}

void Transfer::activeModeTransfer(int controlSocket, const std::string& ipAddress, int port) {
    int dataSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (dataSocket < 0) {
        std::cerr << "Failed to create data socket." << std::endl;
        return;
    }

    sockaddr_in dataAddr;
    memset(&dataAddr, 0, sizeof(dataAddr));
    dataAddr.sin_family = AF_INET;
    dataAddr.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &dataAddr.sin_addr);

    if (connect(dataSocket, (struct sockaddr*)&dataAddr, sizeof(dataAddr)) < 0) {
        std::cerr << "Failed to connect to data socket." << std::endl;
        close(dataSocket);
        return;
    }

    // Handle data transfer here (e.g., send/receive files)
    // ...

    close(dataSocket);
}

void Transfer::passiveModeTransfer(int controlSocket, int& dataPort) {
    int dataSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (dataSocket < 0) {
        std::cerr << "Failed to create data socket." << std::endl;
        return;
    }

    sockaddr_in dataAddr;
    memset(&dataAddr, 0, sizeof(dataAddr));
    dataAddr.sin_family = AF_INET;
    dataAddr.sin_addr.s_addr = INADDR_ANY;
    dataAddr.sin_port = 0; // Let the OS choose the port

    if (bind(dataSocket, (struct sockaddr*)&dataAddr, sizeof(dataAddr)) < 0) {
        std::cerr << "Failed to bind data socket." << std::endl;
        close(dataSocket);
        return;
    }

    if (listen(dataSocket, 1) < 0) {
        std::cerr << "Failed to listen on data socket." << std::endl;
        close(dataSocket);
        return;
    }

    socklen_t addrLen = sizeof(dataAddr);
    if (getsockname(dataSocket, (struct sockaddr*)&dataAddr, &addrLen) < 0) {
        std::cerr << "Failed to get data socket name." << std::endl;
        close(dataSocket);
        return;
    }

    dataPort = ntohs(dataAddr.sin_port); // Get the assigned port

    // Send the port back to the client
    // ...

    int clientDataSocket = accept(dataSocket, nullptr, nullptr);
    if (clientDataSocket < 0) {
        std::cerr << "Failed to accept data connection." << std::endl;
        close(dataSocket);
        return;
    }

    // Handle data transfer here (e.g., send/receive files)
    // ...

    close(clientDataSocket);
    close(dataSocket);
}