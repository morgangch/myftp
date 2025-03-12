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
    (void) controlSocket;
    (void) ipAddress;
    (void) port;
    return;
}

void Transfer::passiveModeTransfer(int controlSocket, int& dataPort) {
    (void) controlSocket;
    (void) dataPort;
    return;
}