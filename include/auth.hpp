#ifndef AUTH_HPP
#define AUTH_HPP

#include <string>
#include <unordered_map>

class Auth {
    public:
        Auth();
        bool validateUser(const std::string& username, const std::string& password);
        bool hasUsername() { return userAuthenticated; }
        bool isAuthenticated() { return fullAuthenticated; }
        std::string getUser() { return user; }
    private:
        std::unordered_map<std::string, std::string> users; // User database
        std::string user;
        bool fullAuthenticated;
        bool userAuthenticated;
    };

#endif // AUTH_HPP