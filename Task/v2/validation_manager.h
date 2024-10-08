#ifndef VALIDATION_MANAGER_H
#define VALIDATION_MANAGER_H

#include "iostream"
#include "regex"
#include "limits"
#include "string"

using namespace std;

// Function to trim whitespace from the beginning and end of a string
string trim(string &str)
{
    size_t first = str.find_first_not_of(' ');
    if (first == string::npos)
    {
        return " "; 
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, last - first + 1);
}

// Function to validate names (author name, first/last name)
string validateName(const string &prompt)
{
    string name;
    regex namePattern("^[A-Za-z\\s]+$"); 
    while (true)
    {
        cout << prompt;
        cin>> name;
        name = trim(name);

        if (regex_match(name, namePattern))
        {
            return name; 
        }
        else
        {
            cout << "Invalid name! Please enter a valid name (letters and spaces only)." << endl;
        }
    }
}

// Function to validate integers
int validateIntegers(const string &prompt)
{
    int val;
    while (true)
    {
        cout << prompt;
        if (cin >> val) 
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            return val; // Return valid integer
        }
        else
        {
            cout << "Invalid input, please enter a valid integer." << endl;
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
    }
}

// Function to validate floating-point numbers
float validateFloat(const string &prompt)
{
    float val;
    while (true)
    {
        cout << prompt;
        if (cin >> val) 
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            return val; 
        }
        else
        {
            cout << "Invalid input! Please enter a valid number." << endl;
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// Function to validate phone numbers
string validatePhone(const string &prompt)
{
    string phone;
    regex phonePattern(R"(^\+\d{1,3}\d{9,10}$)"); 

    while (true)
    {
        cout << prompt;
        cin>>phone;
        phone = trim(phone);

        if (regex_match(phone, phonePattern))
        {
            return phone; 
        }
        else
        {
            cout << "Invalid phone number. Please enter a valid phone number including country code." << endl;
        }
    }
}

// Function to validate email addresses
string validateEmail(const string &prompt)
{
    string email;
    regex emailPattern(R"(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$)"); 
    while (true)
    {
        cout << prompt;
        cin >> email;
        email = trim(email);

        if (regex_match(email, emailPattern))
        {
            return email; 
        }
        else
        {
            cout << "Invalid email. Please enter a valid email address (example@gmail.com)." << endl;
        }
    }
}

// Function to validate gender
string validateGender(const string &prompt)
{
    string gender;
    while (true)
    {
        cout << prompt;
        cin >> gender;
        gender = trim(gender);

        if (gender == "M" || gender == "F" || gender == "m" || gender == "f") 
        {
            return gender; 
        }
        else
        {
            cout << "Invalid gender! Please enter 'M' for male or 'F' for female." << endl;
        }
    }
}

#endif
