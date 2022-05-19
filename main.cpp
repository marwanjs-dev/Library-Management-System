// case1:
// Book issued to student
// check is student in student's table
// check if the book(ID , Name) in Book's table
// if there is more than 1 book with (name, id)  choose the first one
#include <iostream>
#include <string>
#include <vector>
#include "Home.h"
#include "Members.h"
#include "Viewer.h"
#include <fstream>
#include "json.hpp"
#include <cctype>

using json = nlohmann::json;
//#include

using namespace std;

//Home
void Home::login(){
    cout << "----------------------main menu----------------------" <<  endl;
    cout << "-----Login as Admin: 1, Login as Librarian: 2: ";
    cin>>loginAs;
    while(true){
        if (cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << endl;
            cout << "Please enter a valid integer:" << endl;
            cout << "Your Choice: ";
            cin >> loginAs;
        }
        if (loginAs == 1){
            Admin admin;
            admin.inputLogin();
            break;
        }
        else if (loginAs == 2){
            Librarian librarian;
            librarian.inputLogin();
            break;
        }
    }
}

//Admin
void Admin::inputLogin() {
    bool state;
    bool state2;
    while (true) {
        cout << "Insert your username: ";
        cin >> _enteredUsername;
        cout << endl;
        cout << "Insert your password: ";
        cin >> _enteredPassword;
        state = checkLogin(_enteredUsername, _enteredPassword);
        if (state) {
            state2 = adminPage();
        }
        else{
            cout << "please try again" << endl;
            continue;
        }
        if (state2){
            continue;
        }
        break;
    }
}

std::vector <json> Admin::getIDs(){
    json j = readJson();
    for (auto& [key, value] : j["admins"].items()) {
        IDs.emplace_back(key);
    }
    return IDs;
}

bool Admin::checkLogin(const std::string& enteredUsername, const std::string enteredPassword) {
    json j = readJson();
    IDs = getIDs();
    for(int i = 0; i < IDs.size(); i++){
        ID = IDs[i].get<std::string>();
        if (enteredUsername == j["admins"][ID]["username"]){
            if (enteredPassword == j["admins"][ID]["password"]){
                _accepted = true;
                break;
            }
        }
    }
    return _accepted;
}

bool Admin::adminPage() {
    int value;
    bool choice = false;
    int arr[7] = {0,1,2,3,4,5,6};

    while (true){
        cout << "Hello, this is the Admin Page" << endl;
        cout << "------------------------------------------" << endl;
        cout << "if you want to add a student, press 1" << endl;
        cout << "if you want to add a librarian press 2" << endl;
        cout << "if you want to add a Admin press 3" << endl;
        cout << "if you want to remove a student, press 4" << endl;
        cout << "if you want to remove a librarian press 5" << endl;
        cout << "if you want to remove a Admin press 6" << endl;
        cout << "------------------------------------------" << endl;
        cout << "press 0 to exit" << endl;

        cout << "your choice: ";
        cin >> value;
        if (cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << endl;
            cout << "Please enter a valid integer:" << endl;
            cout << "Your Choice: ";
            cin >> value;
        }
        for(int i = 0; i < sizeof(arr); i++){
            if(arr[i] == value){
                choice = true;
                break;
            }
        }
        if (!choice){
            cout << "please try again" << endl;
        }
        if (value == 0){return false;}
        else if(value == 1){
            while (true) {
                Student student;
                student.setStudentId();
                Admin admin;
                if (admin.isExistent(student.getStudentId(), "students")) {
                    cout << "admin id exists try again" << endl;
                    continue;
                }
                student.setStudentName();
                student.setEmail();
                student.setBirthday();
                student.setMobileNumber();
                AccessAdmin aAdmin;
                aAdmin.addStudent(student.getStudentId(), student.getStudentName(), student.getBirthday(),student.getEmail(), student.getMobileNumber());
                break;
            }
            continue;
        }
        else if(value == 2){ // add librarian
            while(true) {
                Librarian librarian1;
                librarian1.setLibrarianId();
                if (librarian1.isExistent(librarian1.getLibrarianId(), "librarians")) {
                    cout << "admin id exists try again" << endl;
                    continue;
                }
                librarian1.setUsername();
                librarian1.setPassword();
                AccessAdmin aAdmin;
                aAdmin.addLibrarian(librarian1.getLibrarianId(), librarian1.getUsername(), librarian1.getPassword());
                break;
            }
        }
        else if(value == 3){
            while (true) {
                Admin admin1;
                admin1.setAdminId();
                if (admin1.isExistent(admin1.getAdminId(), "admins")) {
                    cout << "admin id exists try again" << endl;
                    continue;
                }
                admin1.setUsername();
                admin1.setPassword();
                AccessAdmin aAdmin;
                aAdmin.addAdmin(admin1.getAdminId(), admin1.getUsername(), admin1.getPassword());
                break;
            }
        }
        else if(value == 4){//remove student
            while (true) {
                Student student;
                student.setStudentId();
                Admin admin1;
                if (!admin1.isExistent(student.getStudentId(), "students")) {
                    cout << "admin id doesn't exists try again" << endl;
                    continue;
                }
                AccessAdmin aAdmin;
                aAdmin.removeBy("students", student.getStudentId());
                break;
            }
        }
        else if(value == 5){//remove librarian
            while (true) {
                Librarian librarian;
                librarian.setLibrarianId();
                if (!librarian.isExistent(librarian.getLibrarianId(), "librarians")) {
                    cout << "librarian id doesn't exists try again" << endl;
                    continue;
                }
                AccessAdmin aAdmin;
                aAdmin.removeBy("librarians", librarian.getLibrarianId());
                break;
            }
        }
        else if(value == 6){ //remove admin
            while (true) {
                Admin admin;
                admin.setAdminId();
                if (!admin.isExistent(admin.getAdminId(), "admins")) {
                    cout << "admin id doesn't exists try again" << endl;
                    continue;
                }
                AccessAdmin aAdmin;
                aAdmin.removeBy("admins", admin.getAdminId());
                break;
            }
        }
        else if(value == 7){
            break;
        }
        else{
            cout << "please try again" << endl;
            continue;
        }
    }
}

//librarian
void Librarian::inputLogin() {
    bool state;
    while (true) {
        cout << "Insert your username: ";
        cin >> _enteredUsername;
        cout << endl;
        cout << "Insert your password: ";
        cin >> _enteredPassword;
        state = checkLogin(_enteredUsername, _enteredPassword);
        if (state){
            librarianPage();
        }
        else{
            cout << "please try again" << endl;
            continue;
        }
        break;
    }
}

std::vector <json> Librarian::getIDs(){
    json j = readJson();
    for (auto& [key, value] : j["librarians"].items()) {
        IDs.emplace_back(key);
    }
    return IDs;
}

bool Librarian::checkLogin(const std::string enteredUsername, const std::string enteredPassword) {
    json j = readJson();
    IDs = getIDs();
    for(int i = 0; i < IDs.size(); i++){
        ID = IDs[i].get<std::string>();
        if (enteredUsername == j["librarians"][ID]["username"]){
            if (enteredPassword == j["librarians"][ID]["password"]){
                accepted = true;
                break;
            }
        }
    }
    return accepted;
}

void Librarian::librarianPage() {
    int value;
    bool found = false;
    int array[7] = {1,2,3,4,5,6,7};
    while (true){
        cout << "Hello, this is the Librarian Page" << endl;
        cout << "------------------------------------------" << endl;
        cout << "if you want to add a Book, press 1" << endl;
        cout << "if you want to add Issued book press 2" << endl;
        cout << "if you want to search for a Book press 3" << endl;
        cout << "if you want to remove a Book, press 4" << endl;
        cout << "if you want to return a Book press 5" << endl;
        cout << "if you want to view Books press 6" << endl;
        cout << "if you want to view Issued Books press 7" << endl;
        cout << "------------------------------------------" << endl;
        cout << "your choice: ";
        cin >> value;
        if (cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << endl;
            cout << "Please enter a valid integer:" << endl;
            cout << "Your Choice: ";
            cin >> value;
        }
        for(int i = 0; i < sizeof (array); i++){
            if(array[i] == value){
                found = true;
                break;
            }
        }
        if (!found){
            cout << "please try again" << endl;
            continue;
        }
        else if(value == 0){
            break;
        }
        // Add book
        else if(value == 1) {
            while (true) {
                Librarian librarian;
                Book book;
                book.setBookId();
                if (librarian.isExistent(book.getBookId(), "books")) {
                    cout << "admin id exists try again" << endl;
                    continue;
                }
                book.setBookName();
                book.setAuthorName();
                book.setAvailableQuantity();
                book.setIssuedQuantity();
                librarian.addBook(book.getBookId(), book.getBookName(), book.getAuthorName(), book.getAvailableQuantity(), book.getIssuedQuantity());
                break;
            }
        }
        //Add issued Book
        else if(value == 2){
            while (true) {
                Librarian librarian;
                IssuedBook iBook;
                iBook.setProcedureId();
                iBook.setBookId();
                if (!librarian.isExistent(iBook.getBookId(), "books")) {
                    cout << "book doesn't exist" << endl;
                    continue;
                }
                iBook.setStudentId();
                librarian.issueBook(iBook.getProcedureId(), iBook.getBookId(), iBook.getStudentId(), false);
                break;
            }
        }
        //search for a book
        else if(value == 3){
            Librarian librarian;
            Book book;
            book.setBookId();
            book.setBookName();
            if (!librarian.isExistent(book.getBookId(), "books")) {
                cout << "book doesn't exist" << endl;
                continue;
            }
            librarian.searchBook(book.getBookId(), book.getBookName());
            cout << "book exists" << endl;
        }
        //remove a book
        else if(value == 4){
            Librarian librarian;
            Book book;
            book.setBookId();
            if (!librarian.isExistent(book.getBookId(), "books")) {
                cout << "book doesn't exist" << endl;
                continue;
            }
            librarian.deleteBook(book.getBookId());
        }
        //return book
        else if(value == 5){
            IssuedBook iBook;
            iBook.setBookId();
            Librarian librarian;
            librarian.returnBook(librarian.getBookId());
        }
        //view books
        else if(value == 6){
            Librarian librarian;
            librarian.viewBy("books");
        }
        //view issued books
        else if(value == 7){
            Librarian librarian;
            librarian.viewBy("issued books");
        }
        else{ continue; }
    }

}

//AccessAdmin
json AccessAdmin::readJson(){
    ifstream ifs1("/home/marwan/CLionProjects/assignment1/data.json");
    json j;
    ifs1 >> j;
    return j;
}

json Home::readJson(){
    ifstream ifs1("/home/marwan/CLionProjects/assignment1/data.json");
    json j;
    ifs1 >> j;
    return j;
}

json Admin::readJson(){
    ifstream ifs1("/home/marwan/CLionProjects/assignment1/data.json");
    json j;
    ifs1 >> j;
    return j;
}

json AccessLibrarian::readJson(){
    ifstream ifs1("/home/marwan/CLionProjects/assignment1/data.json");
    json j;
    ifs1 >> j;
    return j;
}

json Librarian::readJson(){
    ifstream ifs1("/home/marwan/CLionProjects/assignment1/data.json");
    json j;
    ifs1 >> j;
    return j;
}

const string &Admin::getUsername() const {
    return _username;
}

const string &Admin::getPassword() const {
    return _password;
}

const string &Admin::getAdminId() const {
    return _adminID;
}

void Admin::setUsername(){
    std::cout << "enter admin username";
    std::cin >> _username;
}

void Admin::setPassword(){
    std::cout << "enter admin password";
    std::cin >> _password;
}

void Admin::setAdminId(){
    std::cout << "enter admin ID";
    std::cin >> _adminID;
}

const string &Librarian::getUsername() const {
    return _username;
}

const string &Librarian::getPassword() const {
    return _password;
}

const string &Librarian::getLibrarianId() const {
    return _librarianID;
}

void Librarian::setUsername(){
    std::cout << "enter librarian username:";
    std::cin >> _username;
}

void Librarian::setPassword(){
    std::cout << "enter librarian password";
    std::cin >> _password;
}

void Librarian::setLibrarianId(){
    std::cout << "enter librarian ID";
    std::cin >> _librarianID;
}

void AccessAdmin::writeJson(const json& j){
    std::ofstream ofs;
    ofs.open("/home/marwan/CLionProjects/assignment1/data.json", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    ofstream ofs2("/home/marwan/CLionProjects/assignment1/data.json");
    ofs2 << j;
}

void AccessLibrarian::writeJson(json j){
    std::ofstream ofs;
    ofs.open("/home/marwan/CLionProjects/assignment1/data.json", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    ofstream ofs2("/home/marwan/CLionProjects/assignment1/data.json");
    ofs2 << j;
}

void AccessAdmin::addAdmin(std::string ID, std::string name, std::string password) {
    json j = readJson();
    j["admins"][ID]["password"] = password;
    j["admins"][ID]["username"] = name;
    writeJson(j);
}

void AccessAdmin::addStudent(std::string ID, std::string name, std::string birthday, std::string email, std::string mobileNumber){
    json j = readJson();
    j["students"][ID]["name"] = name;
    j["students"][ID]["birthday"] = birthday;
    j["students"][ID]["email"] = email;
    j["students"][ID]["mobile number"] = mobileNumber;
    writeJson(j);
}

void AccessAdmin::addLibrarian(std::string ID, std::string name, std::string password){
    json j = readJson();
    j["librarians"][ID]["password"] = password;
    j["librarians"][ID]["username"] = name;
    writeJson(j);
}

void AccessAdmin::removeBy(std::string entity, std::string ID){
    json j = readJson();
    j[entity].erase(ID);
    cout << j;
    writeJson(j);
}

//AccessLibrarian
//test
void AccessLibrarian::addBook(std::string ID, std::string bookName, std::string authorName, int availableQuantity, int issuedQuantity){
    json j = readJson();
    j["books"][ID]["book name"] = bookName;
    j["books"][ID]["author name"] = authorName;
    j["books"][ID]["available quantity"] = availableQuantity;
    j["books"][ID]["issued quantity"] = issuedQuantity;
    AccessLibrarian aLibrarian;
    aLibrarian.writeJson(j);
}

void AccessLibrarian::deleteBook(std::string ID){
    json j = readJson();
    j["books"].erase(ID);
    AccessLibrarian aLibrarian;
    aLibrarian.writeJson(j);
}

void AccessLibrarian::issueBook(std::string procedureID, std::string bookID, std::string studentID, bool returned){
    /*
     * procedureID
     * BookID
     * StudentID
     * Returned(True/False)
     */
    //check if the book exists
    //check if the quantity is more than 0
    json j = readJson();
    if (j["books"][bookID]["available quantity"].get<int>() > 0) {
        j["books"][bookID]["available quantity"] = j["books"][bookID]["available quantity"].get<int>() - 1;
    }
    else{
        cout << "this book isn't available" << endl;
        return ;
    }
    j["books"][bookID]["issued quantity"] = j["books"][bookID]["issued quantity"].get<int>() + 1;
}

void AccessLibrarian::returnBook(std::string procedureID ) {
    /*
     * procedureID
     * BookID
     * StudentID
     * Returned(True/False)
     */
    //check if the book exists
    //check if the quantity is more than 0
    //check if it is already issued
    json j = readJson();

    j["books"][j["issued books"][procedureID]["bookID"].get<std::string>()]["available quantity"] = j["books"][procedureID]["available quantity"].get<int>() +1;
    j["books"][j["issued books"][procedureID]["bookID"].get<std::string>()]["issued quantity"] = j["books"][j["issued books"][procedureID]["bookID"].get<std::string>()]["issued quantity"].get<int>() -1;
    j["issued books"][procedureID]["returned"] = true;
    // if new to
}

bool AccessLibrarian::searchBook(std::string bookID, std::string bookName) {
    json j = readJson();
    for(auto element : j["books"]){
        if (bookID != ""){
            if (element[bookID] == bookID){
                return true;
            }
        }
    }
    if (bookName != ""){
        json j = readJson();
        for (auto& [key, value] : j["books"].items()) {
            if (j["books"][key]["book name"] == bookName){
                return true;
            }
        }
    }
    return false;
}

void AccessLibrarian::viewBy(std::string category){
    json j = readJson();
    for (auto& [key, value] : j[category].items()) {
        for (auto& [key1, value1] : j[category][key].items()){
            cout << j[category][key][key1] << ",";
        }
        cout << endl;
    }
}

int main(){
    Home home{};
    home.login();
    return 1;
}