#ifndef COMMAND_HANDLER_HPP
#define COMMAND_HANDLER_HPP

#include <string>
#include "session.hpp"

class CommandHandler {
  public:
    CommandHandler(Session *session = nullptr);

    void handleCommand(const std::string &command);
    void setSession(Session *session)
    {
        this->session = session;
    }
    Session *getSession()
    {
        return session;
    }
    bool hasJustQuitted()
    {
        return justQuit;
    }

  private:
    Session *session;
    void handleUser(const std::string &argument);
    void handlePass(const std::string &argument);
    void handleList(const std::string &argument);
    void handleRetr(const std::string &argument);
    void handleStor(const std::string &argument);
    void handleQuit(const std::string &argument);
    void handleCwd(const std::string &argument);

    bool justQuit = false;
    void sendResponse(int code, const std::string &message);
};

#endif // COMMAND_HANDLER_HPP