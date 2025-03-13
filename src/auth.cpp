#include "auth.hpp"
#include <string>

Auth::Auth()
{
    User admin("admin", "admin");
    users = {
        {"Anonymous", ""},
    };
    groups = {
        {"admin"},
        {"user"},
        {"guest"},
    };
    admin.groups.push_back(groups[0]);
    users.push_back(admin);
    fullAuthenticated = false;
    userAuthenticated = false;
    user = "";

}

void Auth::reset()
{
    fullAuthenticated = false;
    userAuthenticated = false;
    user = "";
}

bool Auth::validateLogin(
    const std::string &username, const std::string &password)
{
    for (const auto &u : users) {
        if (u.getUsername() == username) {
            if (u.getPassword() == password) {
                fullAuthenticated = true;
                user = username;
                return true;
            }
        }
    }
    return false;
}

bool Auth::validateUser(
    const std::string &username)
{
    for (const auto &u : users) {
        if (u.getUsername() == username) {
            userAuthenticated = true;
            user = username;
            return true;
        }
    }
    return false;
}