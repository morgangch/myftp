#include "command_handler.hpp"
#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>
#include <unistd.h>
#include "constants.hpp"
#include "session.hpp"
#include "transfer.hpp"
#include "ftp_constants.hpp"

CommandHandler::CommandHandler(Session *session) : session(session)
{
}

void CommandHandler::handleUser(const std::string &command)
{
    if (!session)
        return;
    if (session->isAuthenticated()) {
        session->sendResponse(PASS_RESPONSE);
        return;
    }
    std::string username = command.substr(command.find(' ') + 1);
    username = username.substr(0, username.find('\r'));
    username = username.substr(0, username.find('\n'));
    if (session->auth.validateUser(username, "")) {
        session->sendResponse(USER_RESPONSE);
    } else {
        session->sendResponse(NOT_LOGGED_IN);
    }
}

void CommandHandler::handlePass(const std::string &argument)
{
    if (!session)
        return;

    std::string password = argument.substr(argument.find(' ') + 1);
    password = password.substr(0, password.find('\r'));
    password = password.substr(0, password.find('\n'));
    if (!session->auth.hasUsername() || session->isAuthenticated()) {
        session->sendResponse(NOT_LOGGED_IN);
        return;
    }
    if (session->auth.validateUser(session->auth.getUser(), password)) {
        session->setAuthenticated(true);
        session->sendResponse(PASS_RESPONSE);
    } else {
        session->sendResponse(NOT_LOGGED_IN);
    }
}

void CommandHandler::handleList(const std::string &argument)
{
    (void) argument;
    if (!session)
        return;

    if (session->isAuthenticated()) {
        session->sendResponse(COMMAND_NOT_IMPLEMENTED);
    } else {
        session->sendResponse(NOT_LOGGED_IN);
    }
}

void CommandHandler::handleRetr(const std::string &argument)
{
    (void) argument;
    if (!session)
        return;

    if (session->isAuthenticated()) {
        session->sendResponse(COMMAND_NOT_IMPLEMENTED);
    } else {
        session->sendResponse(NOT_LOGGED_IN);
    }
}

void CommandHandler::handleStor(const std::string &argument)
{
    (void) argument;
    if (!session)
        return;

    if (session->isAuthenticated()) {
        session->sendResponse(COMMAND_NOT_IMPLEMENTED);
    } else {
        session->sendResponse(NOT_LOGGED_IN);
    }
}

void CommandHandler::handleQuit(const std::string &argument)
{
    (void) argument;
    if (!session)
        return;

    session->sendResponse(LOGOUT_RESPONSE);
    session->closeSession();
}

void CommandHandler::handleCommand(const std::string &command)
{
    if (!session)
        return;

    std::string cmd = command.substr(0, command.find(' '));
    std::map<std::string, void (CommandHandler::*)(const std::string &)>
        command_map = {
            {"USER", &CommandHandler::handleUser},
            {"PASS", &CommandHandler::handlePass},
            {"LIST", &CommandHandler::handleList},
            {"RETR", &CommandHandler::handleRetr},
            {"STOR", &CommandHandler::handleStor},
            {"QUIT", &CommandHandler::handleQuit},
        };
    cmd = cmd.substr(0, cmd.find('\r'));
    cmd = cmd.substr(0, cmd.find('\n'));
    auto it = command_map.find(cmd);
    if (it != command_map.end()) {
        (this->*(it->second))(command);
    } else {
        session->sendResponse("502 Command not implemented.");
    }
}
