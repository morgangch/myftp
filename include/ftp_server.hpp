#ifndef FTP_SERVER_HPP
#define FTP_SERVER_HPP

#include <map>
#include <poll.h>
#include <vector>
#include "session.hpp"
#include "command_handler.hpp"

class FtpServer {
  public:
    FtpServer(int port);
    ~FtpServer();
    void run();

  private:
    int port;
    int server_socket;
    std::vector<struct pollfd> fds;
    std::map<int, Session> client_sessions;
    CommandHandler *commandHandler;
    void handleNewConnection();
    void handleClientRequest(int client_fd);
};

#endif // FTP_SERVER_HPP