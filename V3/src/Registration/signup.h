#ifndef SIGNUP_H
#define SIGNUP_H

#include <iostream>
#include <string>
#include "../db/db.h"
#include "../models/users_model.h"
#include "../cli/user_registration_cli.h"

class signUp
{
private:
    string first_name;
    string last_name;
    string phone;
    string email;
    string password;

public:
    signUp(const string &_first_name, const string &_last_name, const string &_phone,
           const string &_email, const string &_password)
        : first_name(_first_name), last_name(_last_name), phone(_phone),
          email(_email), password(_password) {}

    signUp() : first_name(""), last_name(""), phone(""), email(""), password("") {}

    // Set user details
    void setDetails(const string &_first_name, const string &_last_name,
                    const string &_phone, const string &_email, const string &_password)
    {
        first_name = _first_name;
        last_name = _last_name;
        phone = _phone;
        email = _email;
        password = _password;
    }

    // Validate input data
    bool validate() const
    {

        if (first_name.empty() || last_name.empty() || phone.empty() || email.empty() || password.empty())
        {
            cerr << "Error: All fields must be filled!" << endl;
            return false;
        }

        return true;
    }

    // Register the user in the database
    bool registerUser() const
    {
        if (!validate())
        {
            return false;
        }

        User newUser(first_name, last_name, email, phone, password);

        try
        {
            User::InsertUser(newUser);
            cout << "User registered successfully!" << endl;
            return true;
        }
        catch (const exception &e)
        {
            cerr << "registration Failed. " << e.what() << endl;
            return false;
        }
    }
};

#endif
