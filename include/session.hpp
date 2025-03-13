#ifndef SESSION_HPP
#define SESSION_HPP

#include <string>
#include <vector>
#include "auth.hpp"
#include "directory.hpp"
#include "transfer.hpp"

enum class DataMode { PASSIVE, ACTIVE };

class Session {
  public:
    Session(); // Add this default constructor declaration
    Session(int clientSocket, const std::string &rootDirectory);
    Session(const std::string &rootDirectory);
    ~Session();
    void setUser(const std::string &username);
    void setPassword(const std::string &password);
    std::string getUser() const
    {
        return auth.getUsername();
    }
    bool isAuthenticated() const
    {
        return authenticated;
    }
    void addCommandToHistory(const std::string &command);
    const std::vector<std::string> &getCommandHistory() const;
    void setTransferMode(bool isPassive)
    {
        dataMode = isPassive ? DataMode::PASSIVE : DataMode::ACTIVE;
    }
    DataMode getTransferMode() const
    {
        return dataMode;
    }
    void setDataMode(DataMode mode)
    {
        dataMode = mode;
    }
    int getClientSocket()
    {
        return clientSocket;
    }
    bool isPassiveMode() const
    {
        return dataMode == DataMode::PASSIVE;
    }
    void sendResponse(const std::string &response);
    void setAuthenticated(bool auth)
    {
        authenticated = auth;
    }
    void setSocket(int socket)
    {
        clientSocket = socket;
    }
    void reset();
    void closeSession();
    Auth auth;
    Directory directory;
    std::string getRootDirectory() const
    {
        return rootDirectory;
    }
    std::string currentDirectory;
    std::string getFiles();
    char transferType = 'A';
    int transferPort = -1;
    Transfer transfer = Transfer();

  private:
    int clientSocket;
    std::string username;
    std::string password;
    bool authenticated;
    std::vector<std::string> commandHistory;
    DataMode dataMode;
    int commandCount = 0;
    std::string const rootDirectory;
};

#endif // SESSION_HPP