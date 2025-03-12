#ifndef TRANSFER_HPP
#define TRANSFER_HPP

#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

class Transfer {
public:
    Transfer();
    ~Transfer();
    void passiveModeTransfer(int controlSocket, int& dataPort);
    void activeModeTransfer(int controlSocket, const std::string& ipAddress, int port);

private:
    int createActiveDataSocket(int port);
    int acceptDataConnection(int dataSocket);
    void sendFileData(int dataSocket, const std::string& filePath);
    void receiveFileData(int dataSocket, const std::string& filePath);
};

#endif // TRANSFER_HPP