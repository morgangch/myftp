#include "auth.hpp"
#include <string>

Auth::Auth()
{
    users["Anonymous"] = "";
}

bool Auth::validateUser(
    const std::string &username, const std::string &password)
{
    auto it = users.find(username);
    if (it != users.end()) {
        if (it->second == password) {
            userAuthenticated = true;
            user = username;
            return true;
        }
    }
    return false; // User not found
}
