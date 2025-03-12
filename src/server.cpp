#include "server.h"
#include "handlers.h"
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <poll.h>
#include <cstring>

#define PORT 21
#define MAX_CLIENTS 10

void start_server() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    struct pollfd fds[MAX_CLIENTS];
    int nfds = 1, current_size = 0, i;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("socket");
        return;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        close(server_socket);
        return;
    }

    if (listen(server_socket, MAX_CLIENTS) < 0) {
        perror("listen");
        close(server_socket);
        return;
    }

    memset(fds, 0, sizeof(fds));
    fds[0].fd = server_socket;
    fds[0].events = POLLIN;
    std::cout << "Server started on port " << PORT << std::endl;
    std::cout << "Waiting for incoming connections..." << std::endl;

    while (true) {
        int poll_count = poll(fds, nfds, -1);
        if (poll_count < 0) {
            perror("poll");
            break;
        }

        current_size = nfds;
        for (i = 0; i < current_size; i++) {
            if (fds[i].revents == 0)
                continue;

            if (fds[i].revents != POLLIN) {
                std::cerr << "Error: revents = " << fds[i].revents << std::endl;
                break;
            }

            if (fds[i].fd == server_socket) {
                client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
                std::cout << "New client connected" << std::endl;
                if (client_socket < 0) {
                    perror("accept");
                    break;
                }

                fds[nfds].fd = client_socket;
                fds[nfds].events = POLLIN;
                char const *welcome_msg = "220 Welcome to the FTP server\r\n";
                send(client_socket, welcome_msg, strlen(welcome_msg), 0);
                nfds++;
            } else {
                handle_client(fds[i].fd);
                close(fds[i].fd);
                fds[i].fd = -1;
            }
        }
    }
    close(server_socket);
}
