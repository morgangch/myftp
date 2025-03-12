#include <iostream>
#include "ftp_server.hpp"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " [port] [directory path]" << std::endl;
        return 84;
    }
    int port = std::atoi(argv[1]);
    if (port <= 0) {
        std::cerr << "Invalid port number" << std::endl;
        return 84;
    }
    const std::string directory_path(argv[2]);
    FtpServer ftp_server(port, directory_path);
    try {
        ftp_server.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}