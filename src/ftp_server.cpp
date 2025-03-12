#include "ftp_server.hpp"
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <poll.h>
#include <unistd.h>
#include <vector>
#include "auth.hpp"
#include "client.hpp"
#include "constants.hpp"
#include "command_handler.hpp"

FtpServer::FtpServer(int port) : port(port)
{
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket creation failed");
        exit(84);
    }
    sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);
    if (bind(server_socket, (struct sockaddr *) &server_addr,
            sizeof(server_addr))
        < 0) {
        perror("Bind failed");
        close(server_socket);
        exit(84);
    }
    commandHandler = new CommandHandler();
    listen(server_socket, MAX_CLIENTS);
}

void FtpServer::run()
{
    fds.push_back({server_socket, POLLIN, 0});

    std::cout << "Server started on port " << port << std::endl;
    while (true) {
        int poll_count = poll(fds.data(), fds.size(), -1);
        if (poll_count < 0) {
            perror("Poll error");
            break;
        }
        try {
            for (size_t i = 0; i < fds.size(); i++) {
                if (fds[i].revents & POLLIN) {
                    if (fds[i].fd == server_socket) {
                        handleNewConnection();
                    } else {
                        handleClientRequest(fds[i].fd, client_sessions[fds[i].fd]);
                        if (commandHandler->hasJustQuitted()) {
                            close(fds[i].fd);
                            fds.erase(fds.begin() + i);
                            client_sessions.erase(fds[i].fd);
                        }
                    }
                }
            }
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            FtpServer::~FtpServer();
            throw e;
        }
    }
}

void FtpServer::handleNewConnection()
{
    int client_fd = accept(server_socket, nullptr, nullptr);
    if (client_fd < 0) {
        perror("Accept failed");
        return;
    }
    fds.push_back({client_fd, POLLIN, 0});
    std::cout << "New client connected: " << client_fd << std::endl;
    Session session(client_fd);
    client_sessions[client_fd] = Session(client_fd);
    client_sessions[client_fd].sendResponse(LOGIN_RESPONSE);
}

void FtpServer::handleClientRequest(int client_fd, Session &session)
{
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, sizeof(buffer));
    size_t bytes_received = read(client_fd, buffer, sizeof(buffer));

    if (bytes_received <= 0) {
        close(client_fd);
        std::cout << "Client disconnected: " << client_fd << std::endl;
        return;
    }
    commandHandler->setSession(&session);
    commandHandler->handleCommand(buffer);
}

FtpServer::~FtpServer()
{
    close(server_socket);
    for (const auto &client : fds) {
        close(client.fd);
    }
}