#include <iostream>
#include <string>
#include "string.h"
#include <vector>
#include <fstream>
#include "json.hpp"
using json = nlohmann::json;

using namespace std;

json readJson(){
    ifstream ifs1("/home/marwan/CLionProjects/assignment1/data.json");
    json j;
    ifs1 >> j;
    return j;
}

void writeJson(json j){
    std::ofstream ofs;
    ofs.open("/home/marwan/CLionProjects/assignment1/data.json", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    ofstream ofs2("/home/marwan/CLionProjects/assignment1/data.json");
    ofs2 << j;
}

void addAdmin(std::string ID, std::string Name, std::string password) {
    json j = readJson();
    j["admins"][ID]["password"] = password;
    j["admins"][ID]["username"] = Name;
    writeJson(j);
}

void addStudent(std::string ID, std::string name, std::string birthday, std::string email, std::string mobileNumber){
    json j = readJson();
    j["students"][ID]["name"] = name;
    j["students"][ID]["birthday"] = birthday;
    j["students"][ID]["email"] = email;
    j["students"][ID]["mobile number"] = mobileNumber;
    writeJson(j);
}

void addLibrarian(std::string ID, std::string name, std::string password){
    json j = readJson();
    j["librarians"][ID]["password"] = password;
    j["librarians"][ID]["username"] = name;
    writeJson(j);
}

void viewStudents(std::string ID){
    json j = readJson();
    cout << j["librarians"][ID]["password"] << endl;
    cout << j["librarians"][ID]["username"] << endl;
}

void removeBy(std::string entity, std::string ID){
    json j = readJson();
    //for (auto& element : j) {
    //    std::cout << element << '\n';
    //}
    j[entity].erase(ID);
    //cout << count_one << endl;
    cout << j;
    //writeJson(j);
}

void issueBook(std::string ID, std::string name, std::string studentID){
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
    j["books"][ID]["available quantity"] = j["books"][ID]["available quantity"].get<int>() - 1;
    //cout << typeid(j["books"][ID]["available quantity"]).name() << endl; // of wierd type, should be type casted with int.
    j["books"][ID]["issued quantity"] = j["books"][ID]["issued quantity"].get<int>() + 1;
    //j["num"] = j["num"].get<int>() + 1;
    cout << j;
    // if new to
}

//int enter(){
//    int numb;
//    std::cin >> numb;
//    return numb;
//}

void login(){
    int loginAs;
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
            //Admin admin;
            //admin.checkLogin();
            cout << "Admin" << endl;
            break;
        }
        else if (loginAs == 2){
            //Librarian librarian;
            //librarian.checkLogin();
            cout << "librarian" << endl;
            break;
        }
    }
}


std::vector <json> getIDs(){
    std::vector <json> IDs;
    json j = readJson();
    for (auto& [key, value] : j["admins"].items()) {
        IDs.emplace_back(key);
    }
    return IDs;
}

bool checkLogin(std::string enteredUsername, std::string enteredPassword) {
    std::vector <json> IDs;
    std::string ID;
    bool accepted = false;
    json j = readJson();
    IDs = getIDs();

    //cout << j["admins"][IDs[0].get<std::string>()]["password"];
    for(int i = 0; i < IDs.size(); i++){
        ID = IDs[i].get<std::string>();
        if (enteredUsername == j["admins"][ID]["username"]){
            if (enteredPassword == j["admins"][ID]["password"]){
                accepted = true;
                break;
            }
        }
    }
    return accepted;
}

void inputLogin() {
    std::string _enteredUsername;
    std::string _enteredPassword;
    bool state;
    while (true) {
        cout << "Insert your username: ";
        cin >> _enteredUsername;
        cout << endl;
        cout << "Insert your password: ";
        cin >> _enteredPassword;
        state = checkLogin(_enteredUsername, _enteredPassword);
        if (state){
            break;
        }
        else{
            cout << "please try again" << endl;
            continue;
        }
    }
}

int main(){
    //addLibrarian("4321", "hamooda", "hamoodahtml");
    //std::for_each(data.begin(), data.end(), [](char & c){
    //    c = ::toupper(c);
    //});
    //viewStudents("4321");
    //bla();
    //issueBook("1000", "Oliver Twist", "marwan khaled");
    json j = readJson();
    //for(auto& element : j["books"]){
    //    std::cout << element << '\n';
    //}
    std::vector <json> flamingo;
    for (auto& [key, value] : j["librarians"].items()) {
        std::cout << typeid(key).name() << "\n";
        flamingo.emplace_back(key);
    }
    std::string btengan = "btengan";
//    for (int i = 0; i < flamingo.size(); i++){
//        cout << typeid(flamingo[i].get<std::string>()).name() << endl;
//    }
    std::cout << typeid(btengan).name();
    //std::cout << flamingo;
    //login();
    //inputLogin();

    return 1;
}