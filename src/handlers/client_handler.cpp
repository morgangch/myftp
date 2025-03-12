#include "handlers.h"
#include <iostream>
#include <unistd.h>
#include <cstring>

void handle_client(int client_socket) {
    // Handle client commands and data transfer
    // ...
    std::cout << "Handling client on socket " << client_socket << std::endl;
    // Example: send a welcome message
    const char *welcome_msg = "220 Welcome to the FTP server\r\n";
    send(client_socket, welcome_msg, strlen(welcome_msg), 0);
}
