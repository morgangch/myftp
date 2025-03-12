#ifndef TRANSFER_HPP
#define TRANSFER_HPP

#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

class Transfer {
public:
    // Constructor
    Transfer();

    // Destructor
    ~Transfer();

    // Method to handle active mode data transfer
    void passiveModeTransfer(int controlSocket, int& dataPort);

    // Method to handle passive mode data transfer
    void activeModeTransfer(int controlSocket, const std::string& ipAddress, int port);

private:
    // Helper method to create a data socket for active mode
    int createActiveDataSocket(int port);

    // Helper method to accept a connection on the data socket
    int acceptDataConnection(int dataSocket);

    // Helper method to send file data
    void sendFileData(int dataSocket, const std::string& filePath);

    // Helper method to receive file data
    void receiveFileData(int dataSocket, const std::string& filePath);
};

#endif // TRANSFER_HPP