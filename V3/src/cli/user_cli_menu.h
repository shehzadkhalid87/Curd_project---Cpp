#ifndef USER_CLI_MENU_H
#define USER_CLI_MENU_H

#include "iostream"
#include "../models/users_model.h"
#include "../validation/validation_manager.h"

using namespace std;

void userCli(User &user)
{
    int choice;

    do
    {
        cout << "\nUser Menu:\n";
        cout << "1. Add User\n";
        cout << "2. Edit User\n";
        cout << "3. Delete User\n";
        cout << "4. View Users\n";
        cout << "5.Return back\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string f_n, l_n, em, ph, password;

            f_n = validateName("Enter first name: ");
            l_n = validateName("Enter last name: ");
            ph = validatePhone("Enter phone number: ");
            em = validateEmail("Enter email: ");
            password = validateName("Enter password: ");

            User newUser(f_n, l_n, em, ph, password);
            User::InsertUser(newUser);
            cout << "User added successfully.\n";
            break;
        }

        case 2:
        {
            int id;
            cout << "Enter user ID to edit: ";
            cin >> id;

            string f_n, l_n, ph, em, password;

            f_n = validateName("Enter first name: ");
            l_n = validateName("Enter last name: ");
            ph = validatePhone("Enter phone number: ");
            em = validateEmail("Enter email: ");
            password = validateName("Enter password: ");

            User updatedUser(f_n, l_n, em, ph, password);
            User::updateUser(id, updatedUser);
            cout << "User updated successfully.\n";
            break;
        }

        case 3:
        {
            int id;
            if (User::isDatabaseEmpty()) 
            {
                cout << "Database is empty!\n";
                break;
            }

            cout << "Enter user ID to delete: ";
            cin >> id;

            if (User::deleteUser(id)) 
            {
                cout << "User deleted successfully.\n";
            }
            else
            {
                cout << "User ID not found!\n";
            }

            break;
        }

        case 4:
        {
            vector<User> users = User::findAllUsers();
            for (const auto &user : users)
            {
                cout << "ID: " << user.id << ", Name: " << user.first_name << " " << user.last_name
                     << ", Email: " << user.email << ", Phone: " << user.phone << endl;
            }
            break;
        }
        case 5:{
            return;
            break;
        }

        case 6:
            cout << "Exiting user menu." << endl;
            break;

        default:
            cout << "Invalid choice, please try again." << endl;
            break;
        }
    } while (choice != 5);
}

#endif
