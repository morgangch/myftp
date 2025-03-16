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
        session->setAuthenticated(false);
        session->auth.reset();
    }
    std::string username = command.substr(command.find(' ') + 1);
    username = username.substr(0, username.find('\r'));
    username = username.substr(0, username.find('\n'));
    session->auth.validateUser(username);
    session->sendResponse(USER_RESPONSE);
}

void CommandHandler::handlePass(const std::string &argument)
{
    if (!session)
        return;
    std::string password = argument.substr(argument.find(' ') + 1);
    password = password.substr(0, password.find('\r'));
    password = password.substr(0, password.find('\n'));
    if (!session->auth.hasUsername() || session->isAuthenticated()) {
        session->sendResponse(session->auth.hasUsername() ? NOT_LOGGED_IN
                                                         : INVALID_SEQUENCE);
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
        std::string files = session->getFiles();
        session->sendResponse(files);
    } else {
        session->sendResponse(NOT_LOGGED_IN);
    }
}

void CommandHandler::handleMkd(const std::string &argument)
{
    if (!session)
        return;

    std::string new_directory = argument.substr(argument.find(' ') + 1);
    new_directory = new_directory.substr(0, new_directory.find('\r'));
    new_directory = new_directory.substr(0, new_directory.find('\n'));
    if (new_directory == "MKD") {
        new_directory = "";
    }
    if (new_directory.empty()) {
        session->sendResponse(INVALID_ARGUMENT);
        return;
    }
    if (session->isAuthenticated()) {
        if (new_directory[0] == '/') {
            new_directory = new_directory.substr(1);
        }
        if (session->directory.createDirectory(new_directory)) {
            session->sendResponse(MKD_RESPONSE);
        } else {
            session->sendResponse(INVALID_ARGUMENT);
        }
    } else {
        session->sendResponse(NOT_LOGGED_IN);
    }
}

void CommandHandler::handleRmd(const std::string &argument)
{
    if (!session)
        return;

    std::string new_directory = argument.substr(argument.find(' ') + 1);
    new_directory = new_directory.substr(0, new_directory.find('\r'));
    new_directory = new_directory.substr(0, new_directory.find('\n'));
    if (new_directory == "RMD") {
        new_directory = "";
    }
    if (new_directory.empty()) {
        session->sendResponse(INVALID_ARGUMENT);
        return;
    }
    if (session->isAuthenticated()) {
        if (new_directory[0] == '/') {
            new_directory = new_directory.substr(1);
        }
        if (session->directory.removeDirectory(new_directory)) {
            session->sendResponse(RMD_RESPONSE);
        } else {
            session->sendResponse(INVALID_ARGUMENT);
        }
    } else {
        session->sendResponse(NOT_LOGGED_IN);
    }
}

void CommandHandler::handleDele(const std::string &argument)
{
    if (!session)
        return;

    std::string new_file = argument.substr(argument.find(' ') + 1);
    new_file = new_file.substr(0, new_file.find('\r'));
    new_file = new_file.substr(0, new_file.find('\n'));
    if (new_file == "DELE") {
        new_file = "";
    }
    if (new_file.empty()) {
        session->sendResponse(INVALID_ARGUMENT);
        return;
    }
    if (session->isAuthenticated()) {
        if (new_file[0] == '/') {
            new_file = new_file.substr(1);
        }
        if (session->directory.removeFile(new_file)) {
            session->sendResponse(DELE_RESPONSE);
        } else {
            session->sendResponse(INVALID_ARGUMENT);
        }
    } else {
        session->sendResponse(NOT_LOGGED_IN);
    }
}

void CommandHandler::handleCwd(const std::string &argument)
{
    if (!session)
        return;

    if (session->isAuthenticated()) {
        std::string new_directory = argument.substr(argument.find(' ') + 1);
        new_directory = new_directory.substr(0, new_directory.find('\r'));
        new_directory = new_directory.substr(0, new_directory.find('\n'));
        if (new_directory == "CWD") {
            new_directory = "";
        }
        if (new_directory.empty()) {
            session->sendResponse(INVALID_ARGUMENT);
            return;
        }
        if (new_directory[0] == '/') {
            if (new_directory == "/") {
                session->currentDirectory = session->getRootDirectory();
                session->sendResponse(CWD_RESPONSE);
                return;
            }
            new_directory = new_directory.substr(1);
            session->currentDirectory =
                session->getRootDirectory() + "/" + new_directory;
            session->sendResponse(CWD_RESPONSE);
            return;
        }
        if (new_directory == "..") {
            if (session->currentDirectory == session->getRootDirectory()) {
                session->sendResponse(LOGIN_RESPONSE);
                return;
            }
            session->currentDirectory = session->currentDirectory.substr(
                0, session->currentDirectory.find_last_of('/'));
        } else {
            std::string new_path =
                session->currentDirectory + "/" + new_directory;
            if (access(new_path.c_str(), F_OK) == -1) {
                session->sendResponse(INVALID_ARGUMENT);
                return;
            }
            session->currentDirectory = new_path;
        }
        session->sendResponse(CWD_RESPONSE);
    } else {
        session->sendResponse(NOT_LOGGED_IN);
    }
}

void CommandHandler::handleCdup(const std::string &argument)
{
    (void) argument;
    if (!session)
        return;

    if (session->isAuthenticated()) {
        if (session->currentDirectory == session->getRootDirectory()) {
            session->sendResponse(INVALID_ARGUMENT);
            return;
        }
        session->currentDirectory = session->currentDirectory.substr(
            0, session->currentDirectory.find_last_of('/'));
        session->sendResponse(CWD_RESPONSE);
    } else {
        session->sendResponse(NOT_LOGGED_IN);
    }
}

void CommandHandler::handlePwd(const std::string &argument)
{
    (void) argument;
    if (!session)
        return;

    if (session->isAuthenticated()) {
        std::string response = "257 \"";
        if (session->currentDirectory == session->getRootDirectory())
            response += "/";
        else
            response += session->currentDirectory[0] == '.' ?
                            session->currentDirectory.substr(1) :
                            session->currentDirectory;
        response += "\"\r\n";
        session->sendResponse(response);
    } else {
        session->sendResponse(NOT_LOGGED_IN);
    }
}

void CommandHandler::handlePasv(const std::string &argument)
{
    (void) argument;
    if (!session)
        return;

    if (session->isAuthenticated()) {
        session->setTransferMode(true);
        session->sendResponse(PASV_RESPONSE);
    } else {
        session->sendResponse(NOT_LOGGED_IN);
    }
}

void CommandHandler::handleRetr(const std::string &argument)
{
    if (!session)
        return;
    std::string new_file = argument.substr(argument.find(' ') + 1);
    new_file = new_file.substr(0, new_file.find('\r'));
    new_file = new_file.substr(0, new_file.find('\n'));

    if (new_file == "RETR") {
        new_file = "";
    }
    if (new_file.empty()) {
        session->sendResponse(INVALID_ARGUMENT);
        return;
    }
    if (session->isAuthenticated()) {
        session->sendResponse(COMMAND_NOT_IMPLEMENTED);
    } else {
        session->sendResponse(NOT_LOGGED_IN);
    }
}

void CommandHandler::handleStor(const std::string &argument)
{
    if (!session)
        return;
    std::string new_file = argument.substr(argument.find(' ') + 1);
    new_file = new_file.substr(0, new_file.find('\r'));
    new_file = new_file.substr(0, new_file.find('\n'));
    if (new_file == "STOR") {
        new_file = "";
    }
    if (new_file.empty()) {
        session->sendResponse(INVALID_ARGUMENT);
        return;
    }
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

void CommandHandler::handlePort(const std::string &argument)
{
    (void) argument;
    if (!session)
        return;

    if (session->isAuthenticated()) {
        session->setTransferMode(false);
        session->sendResponse(PORT_RESPONSE);
    } else {
        session->sendResponse(NOT_LOGGED_IN);
    }
}

void CommandHandler::handleType(const std::string &argument)
{
    if (!session)
        return;

    std::string type = argument.substr(argument.find(' ') + 1);
    type = type.substr(0, type.find('\r'));
    type = type.substr(0, type.find('\n'));
    if (type == "TYPE") {
        type = "";
    }
    if (type.empty()) {
        session->sendResponse(INVALID_ARGUMENT);
        return;
    }
    if (session->isAuthenticated()) {
        if (type == "I" || type == "A") {
            session->transferType = type[0];
            session->sendResponse(DIRECTORY_ACTION_OK);
        } else {
            session->sendResponse(INVALID_ARGUMENT);
        }
    } else {
        session->sendResponse(NOT_LOGGED_IN);
    }
}

void CommandHandler::handleSyst(const std::string &argument)
{
    (void) argument;
    if (!session)
        return;

    if (session->isAuthenticated()) {
        session->sendResponse("215 UNIX Type: L8");
    } else {
        session->sendResponse(NOT_LOGGED_IN);
    }
}

void CommandHandler::handleNoop(const std::string &argument)
{
    (void) argument;
    if (!session)
        return;

    session->sendResponse(NOOP_RESPONSE);
}

void CommandHandler::handleHelp(const std::string &argument)
{
    (void) argument;
    if (!session)
        return;

    session->sendResponse(HELP_RESPONSE);
    std::string help_message = "Commands available:\r\n";
    help_message += "USER <username> - Log in with username\r\n";
    help_message += "PASS <password> - Log in with password\r\n";
    help_message += "LIST - List files in current directory\r\n";
    help_message += "RETR <filename> - Download file\r\n";
    help_message += "STOR <filename> - Upload file\r\n";
    help_message += "QUIT - Log out\r\n";
    help_message += "HELP - Show help message\r\n";
    help_message += "EXIT - Close server\r\n";
    help_message += "MKD <directory> - Create directory\r\n";
    help_message += "CWD <directory> - Change working directory\r\n";
    help_message += "CDUP - Change to parent directory\r\n";
    help_message += "PWD - Print working directory\r\n";
    help_message += "PASV - Enable passive mode\r\n";
    help_message += "DELE <file> - Delete file\r\n";
    help_message += "RMD <directory> - Remove directory\r\n";
    help_message += "PORT <address> - Enable active mode\r\n";
    help_message += "TYPE <type> - Set transfer type\r\n";
    help_message += "SYST - Show system information\r\n";
    help_message += "NOOP - Do nothing\r\n";
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

    session->directory.currentDirectory = session->currentDirectory;
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
            {"MKD", &CommandHandler::handleMkd},
            {"CWD", &CommandHandler::handleCwd},
            {"CDUP", &CommandHandler::handleCdup},
            {"PWD", &CommandHandler::handlePwd},
            {"PASV", &CommandHandler::handlePasv},
            {"DELE", &CommandHandler::handleDele},
            {"RMD", &CommandHandler::handleRmd},
            {"PORT", &CommandHandler::handlePort},
            {"TYPE", &CommandHandler::handleType},
            {"SYST", &CommandHandler::handleSyst},
            {"NOOP", &CommandHandler::handleNoop},
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
