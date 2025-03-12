#ifndef AUTH_HPP
#define AUTH_HPP

#include <string>
#include <vector>
#include <unordered_map>

class Group {
  public:
    Group(const std::string &name) : name(name)
    {
    }
    std::string getName()
    {
        return name;
    }

  private:
    std::string name;
};

class User {
  public:
    User(const std::string name, const std::string &password)
        : password(password), username(name)
    {
    }
    std::string getPassword() const
    {
        return password;
    }
    std::string getUsername() const
    {
        return username;
    }
    std::vector<Group> groups;

  private:
    std::string password;
    std::string username;
};

class Auth {
  public:
    Auth();
    bool validateUser(
        const std::string &username);

    bool validateLogin(
        const std::string &username, const std::string &password);
    bool hasUsername()
    {
        return userAuthenticated;
    }
    bool isAuthenticated()
    {
        return fullAuthenticated;
    }
    std::string getUsername() const
    {
        return user;
    }
    User getUser(const std::string &username)
    {
        for (auto &u : users) {
            if (u.getUsername() == username) {
                return u;
            }
        }
        return User("", "");
    }
    bool userInGroup(const std::string &username, const std::string &group)
    {
        for (auto &u : users) {
            if (u.getUsername() == username) {
                for (auto &g : u.groups) {
                    if (g.getName() == group) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    bool groupExists(const std::string &group)
    {
        for (auto &g : groups) {
            if (g.getName() == group) {
                return true;
            }
        }
        return false;
    }
    bool userIsAdmin(const std::string &username)
    {
        return userInGroup(username, "admin");
    }

  private:
    std::string user;
    std::vector<Group> groups;
    std::vector<User> users;
    bool fullAuthenticated;
    bool userAuthenticated;
};

#endif // AUTH_HPP