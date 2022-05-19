//
// Created by marwan on 11/11/21.
//
#include "Viewer.h"
#include "json.hpp"
#ifndef ASSIGNMENT1_MEMBERS_H
#define ASSIGNMENT1_MEMBERS_H
using json = nlohmann::json;

class Admin : public AccessAdmin{
    std::string _username;
    std::string _password;
    std::string _adminID;
    std::string _enteredUsername;
    std::string _enteredPassword;
    std::vector <json> IDs;
    std::string ID;
    bool _accepted = false;
public:
    bool isExistent(std::string ID, std::string category){
        bool state = false;
        json j = readJson();
        for (auto& [key, value] : j[category].items()) {
            if (ID == key){
                return true;
            }
        }
        return state;
    }

    void setUsername();

    void setPassword();

    void setAdminId();

    [[nodiscard]] const std::string &getUsername() const;

    [[nodiscard]] const std::string &getPassword() const;

    [[nodiscard]] const std::string &getAdminId() const;

    std::vector <json> getIDs();
//    void getUsernames();
//    void getPasswords();
    [[noreturn]] void inputLogin();
    bool checkLogin(const std::string& _enteredUsername, std::string _enteredPassword);
    bool adminPage();
    json readJson() override;
};

class Librarian: public AccessLibrarian{
    std::string _username;
    std::string _password;
    std::string _librarianID;
    std::string _enteredUsername;
    std::string _enteredPassword;
    std::vector <json> IDs;
    std::string ID;
    bool accepted = false;
public:
    bool isExistent(std::string ID, std::string category){
        bool state = false;
        json j = readJson();
        for (auto& [key, value] : j[category].items()) {
            if (ID == key){
                return true;
            }
        }
        return state;
    }

    std::vector <json> getIDs();

    void inputLogin();

    bool checkLogin(std::string _enteredUsername, std::string _enteredPassword);

    static void librarianPage();

    json readJson() override;

    void setUsername();

    void setPassword();

    void setLibrarianId();

    [[nodiscard]] const std::string &getUsername() const;

    [[nodiscard]] const std::string &getPassword() const;

    [[nodiscard]] const std::string &getLibrarianId() const;
};

#endif //ASSIGNMENT1_MEMBERS_H
