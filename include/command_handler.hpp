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
    bool justQuit = false;
    bool justExit = false;

  private:
    Session *session;
    void handleUser(const std::string &argument);
    void handlePass(const std::string &argument);
    void handleList(const std::string &argument);
    void handleRetr(const std::string &argument);
    void handleStor(const std::string &argument);
    void handleQuit(const std::string &argument);
    void handleCwd(const std::string &argument);
    void handleHelp(const std::string &argument);
    void handleExit(const std::string &argument);
    void handleMkd(const std::string &argument);
    void handleCdup(const std::string &argument);
    void handlePwd(const std::string &argument);
    void handlePasv(const std::string &argument);
    void handleDele(const std::string &argument); 
    void handleRmd(const std::string &argument);
    void handlePort(const std::string &argument);
    void handleType(const std::string &argument);
    void handleSyst(const std::string &argument);
    void handleNoop(const std::string &argument);

    void sendResponse(int code, const std::string &message);
};

#endif // COMMAND_HANDLER_HPP