//
// Created by marwan on 11/11/21.
//

#ifndef ASSIGNMENT1_HOME_H
#define ASSIGNMENT1_HOME_H
//#include ""
#include "json.hpp"
using json = nlohmann::json;

class Home{
    int loginAs;
public:
    void login();
    static json readJson();
};

#endif //ASSIGNMENT1_HOME_H