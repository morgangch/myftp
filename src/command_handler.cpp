#include "command_handler.hpp"
#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>
#include <unistd.h>
#include "constants.hpp"
#include "session.hpp"
#include "transfer.hpp"

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
    if (session->auth.validateUser(username)) {
        session->sendResponse(USER_RESPONSE);
    } else {
        session->sendResponse(INVALID_USERNAME);
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
    if (password == "PASS") {
        password = "";
    }
    if (session->auth.validateLogin(session->auth.getUsername(), password)) {
        session->setAuthenticated(true);
        session->sendResponse(PASS_RESPONSE);
    } else {
        session->sendResponse(INVALID_USERNAME);
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
    this->justQuit = true;
}

void CommandHandler::handleHelp(const std::string &argument)
{
    (void) argument;
    if (!session)
        return;

    std::string help_message = "214 Help message\nCommands available:\n";
    help_message += "USER <username> - Log in with username\n";
    help_message += "PASS <password> - Log in with password\n";
    help_message += "LIST - List files in current directory\n";
    help_message += "RETR <filename> - Download file\n";
    help_message += "STOR <filename> - Upload file\n";
    help_message += "QUIT - Log out\n";
    help_message += "HELP - Show help message\n";
    help_message += "EXIT - Close server\n";
    session->sendResponse(help_message);
}

void CommandHandler::handleExit(const std::string &argument)
{
    (void) argument;
    if (!session)
        return;
    if (!session->isAuthenticated()
        || !session->auth.userIsAdmin(session->getUser())) {
        session->sendResponse(INVALID_PERMISSIONS);
        return;
    }
    session->sendResponse(QUIT_RESPONSE);
    session->closeSession();
    this->justQuit = true;
    this->justExit = true;
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
            {"?", &CommandHandler::handleHelp},
            {"HELP", &CommandHandler::handleHelp},
            {"EXIT", &CommandHandler::handleExit},
        };
    cmd = cmd.substr(0, cmd.find('\r'));
    cmd = cmd.substr(0, cmd.find('\n'));
    if (cmd.empty()) {
        return;
    }
    auto it = command_map.find(cmd);
    if (it != command_map.end()) {
        (this->*(it->second))(command);
        session->addCommandToHistory(command);
    } else {
        session->sendResponse(INVALID_COMMAND);
    }
}
