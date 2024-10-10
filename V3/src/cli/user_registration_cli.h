#ifndef USER_REGISTRATION_CLI_H
#define USER_REGISTRATION_CLI_H

#include <iostream>
#include "../Registration/login.h"
#include "../Registration/signup.h"
#include "../runFile/main_menu.h"
#include "../passwordmanger/PasswordManager.h"
using namespace std;

void performSignUp();
void performLogin();
void mainMenu(User &user, Books &book);

void performSignUp()
{
    string firstName, lastName, phone, email, password;
    firstName = validateName("Enetr First Name: ");
    lastName = validateName("Enter Last Name: ");
        while (true)
    {
       
        phone = validatePhone("Enter Phone Number: ");
        if (User::checkIfPhone(phone)) 
        {
            cout << "Phone already taken." << endl;
        }
        else
        {
            break;
        }
    }
    while (true)
    {
        
        email = validateEmail("Enter email: ");
        if (User::checkIfEmail(email)) 
        {
            cout << "Email already exists. Please try again." << endl;
        }
        else
        {
            break;
        }
    }
    password = validatePassword("Enter your password: ");

    signUp newUser;
    newUser.setDetails(firstName, lastName, phone, email, password);

    if (newUser.registerUser())
    {
        cout << "Signup successful!" << endl;
    }
    else
    {
        cout << "Signup failed. Please try again." << endl;
        return;
    }
}

void performLogin()
{
    string email, password;

    cout << "Enter Email: ";
    cin >> email;
    cout << "Enter Password: ";
    cin >> password;

    try
    {
        
        User user = User::findUserByEmail(email);
        string storedHashedPassword = user.password;

        if (BCrypt::validatePassword(password, storedHashedPassword))
        {
            cout << "Login successful!" << endl;
            Books book;
            mainMenu(user, book);
        }
        else
        {
            cout << "Login failed. Invalid credentials." << endl;
        }
    }
    catch (const exception &e)
    {
        cout << "Error: " << e.what() << endl;
    }
}

#endif
