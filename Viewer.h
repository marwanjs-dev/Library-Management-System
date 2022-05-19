//
// Created by marwan on 11/11/21.
//
#include "json.hpp"
#include "entities.h"
using json = nlohmann::json;
#ifndef ASSIGNMENT1_VIEWER_H
#define ASSIGNMENT1_VIEWER_H
class AccessLibrarian : public Book{
public:
    virtual json readJson();
    void writeJson(json j);
    void viewBy(std::string category);
    void addBook(std::string ID, std::string bookName, std::string authorName, int availableQuantity, int issuedQuantity);
    void deleteBook(std::string ID);
    void issueBook(std::string procedureID, std::string bookID, std::string studentID, bool returned = false);
    void returnBook(std::string procedureID);
    bool searchBook(std::string bookID = "", std::string bookName = "");
};
class AccessAdmin : public Student {
public:
    virtual json readJson();
    static void writeJson(const json& j);
    void addAdmin(std::string ID, std::string name, std::string password);
    void addStudent(std::string ID, std::string name, std::string birthday, std::string email, std::string mobileNumber);
    void addLibrarian(std::string ID, std::string name, std::string password);
    void removeBy(std::string entity, std::string ID);
};
#endif //ASSIGNMENT1_VIEWER_H
