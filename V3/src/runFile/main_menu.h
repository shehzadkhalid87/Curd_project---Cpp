#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "iostream"
#include "../cli/books_cli_menu.h"
#include "../cli/user_cli_menu.h"
using namespace std;


void showMenus()
{
    cout << "\n**************************************************\n";
    cout << "        WELCOME TO DB MANAGNEMNT SYSTEM\n";
    cout << "*****************************************************\n";
    cout << "Please choose an option:\n";
    cout << "1. User\n";
    cout << "2. Books\n";
    cout << "3. Exit\n";
    cout << "***********************************\n";
}

void mainMenu(User &user, Books &book)
{
    int choice;
    do
    {
        showMenus();
        cout << "Enter your Choice\n";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            userCli(user);
            break;
        }

        case 2:
        {
            BookCli(book);
            break;
        }

        case 3:
        {
            return;
            break;
        }

        case 4:
        {
            cout << "Exiting program..." << endl;
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
        }
        }
    } while (choice != 4);
}
#endif