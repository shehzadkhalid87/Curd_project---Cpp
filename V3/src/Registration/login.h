#ifndef LOGIN_H
#define LOGIN_H

#include <iostream>
#include <string>
#include "../db/db.h"              
#include "../models/users_model.h"    
#include "../runFile/main_menu.h" 


void showMenus();  

using namespace std;

class Login
{
private:
    string email;
    string password;

public:
   
    Login() : email(""), password("") {}

    void setCredentials(const string& _email, const string& _password) {
        email = _email;
        password = _password;
    }

    bool authenticate() {
        try {
            User user = User::findUserByEmail(email);
            if (user.password == password) {
                cout << "Login successful!" << endl;
                showMenus();  
            } else {
                cout << "invalid credential." << endl;
                return false;
            }
        } catch (const runtime_error& e) {
            cerr << "invalid credentials: " << e.what() << endl;
            return false;
        }
        return true;
    }
};

#endif 
