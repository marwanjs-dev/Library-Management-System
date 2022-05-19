//
// Created by marwan on 11/14/21.
//

#ifndef ASSIGNMENT1_ENTITIES_H
#define ASSIGNMENT1_ENTITIES_H

#include <string>
#include "json.hpp"

class Book{
    std::vector <std::string> bookIDs;
    std::string _bookID;
    std::string _bookName;
    std::string _authorName;
    int _availableQuantity;
    int _issuedQuantity;
public:
    //setters
    void setBookId() {
        std::cout << "enter Book ID : ";
        std::cin >> _bookID;
    }

    void setBookName() {
        std::cout << "enter Book Name: ";
        std::getline(std::cin >> std::ws, _bookName);
    }

    void setAuthorName() {
        std::cout << "enter author name : ";
        std::cin >> _authorName;
    }

    void setAvailableQuantity() {
        std::cout << "enter Book available quantity";
        std::cin >> _availableQuantity;
    }

    void setIssuedQuantity() {
        std::cout << "enter Book issued quantity";
        std::cin >> _issuedQuantity;
    }

    //getters
    [[nodiscard]] const std::string &getBookId() const {
        return _bookID;
    }

    [[nodiscard]] const std::string &getBookName() const {
        return _bookName;
    }

    [[nodiscard]] const std::string &getAuthorName() const {
        return _authorName;
    }

    [[nodiscard]] int getAvailableQuantity() const {
        return _availableQuantity;
    }

    [[nodiscard]] int getIssuedQuantity() const {
        return _issuedQuantity;
    }
};

class Student{
    std::string _studentID;
    std::string _studentName;
    std::string _birthday;
    std::string _email;
    std::string _mobileNumber;
public:
    //setters
    void setStudentId() {
        while(true) {
            std::cout << "enter studentID: ";
            std::cin >> _studentID;
            if (_studentID == ""){
                std::cout << "please try again";
                continue;
            }
            else{
                break;
            }
        }
    }

    void setStudentName() {
        std::cout << "enter studentName: ";
        std::cin >> _studentName;
    }

    void setBirthday() {
        std::cout << "enter student birthday: ";
        std::cin >> _birthday;
    }

    void setEmail() {
        std::cout << "enter student email: ";
        std::cin >> _email;
    }

    void setMobileNumber() {
        std::cout << "enter student mobile number: ";
        std::cin >> _mobileNumber;
    }

    //getters
    [[nodiscard]] const std::string &getStudentId() const {
        return _studentID;
    }

    [[nodiscard]] const std::string &getStudentName() const {
        return _studentName;
    }

    [[nodiscard]] const std::string &getBirthday() const {
        return _birthday;
    }

    [[nodiscard]] const std::string &getEmail() const {
        return _email;
    }

    [[nodiscard]] const std::string &getMobileNumber() const {
        return _mobileNumber;
    }
};

class IssuedBook{
    std::string _procedureID;
    std::string _bookID;
    std::string _studentID;

public:
    //setters
    void setProcedureId() {
        std::cout << "enter procedure id";
        std::cin >> _procedureID;
    }

    void setBookId(){
        std::cout << "enter book id";
        std::cin >> _bookID;
    }

    void setStudentId() {
        std::cout << "enter student id";
        std::cin >> _studentID;
    }

    //getters
    [[nodiscard]] const std::string &getProcedureId() const {
        return _procedureID;
    }

    [[nodiscard]] const std::string &getBookId() const {
        return _bookID;
    }

    [[nodiscard]] const std::string &getStudentId() const {
        return _studentID;
    }
};

#endif //ASSIGNMENT1_ENTITIES_H
