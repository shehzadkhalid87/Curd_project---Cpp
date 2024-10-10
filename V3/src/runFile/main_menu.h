#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <iostream>
#include "../cli/books_cli_menu.h"
#include "../cli/user_cli_menu.h"
#include "../cli/user_registration_cli.h" 

using namespace std;




void showMenus() {
    cout << "\n**************************************************\n";
    cout << "        WELCOME TO DB MANAGEMENT SYSTEM\n";
    cout << "*****************************************************\n";
    cout << "Please choose an option:\n";
    cout << "1. User\n";
    cout << "2. Books\n";
    cout << "3. Exit\n";
    cout << "***********************************\n";
}

void Menu() {
    int choice;

    while (true) {
        cout << "**********************************************" << endl;
        cout << "              WELCOME TO REGISTRATION          " << endl;
        cout << "**********************************************" << endl;
        cout << "1. Signup" << endl;
        cout << "2. Login" << endl;
        cout << "3. Return to main menu" << endl;
        cout << "4. Exit program (0)" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                performSignUp();  
                break;
            case 2:
                performLogin();  
                break;
            case 3:
                cout << "Returning to main menu..." << endl;
                return;
            case 0:
                cout << "Exiting the program..." << endl;
                exit(0);
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }
}

void mainMenu(User &user, Books &book) {
    int choice;
    do {
        showMenus();
        cout << "Enter your Choice\n";
        cin >> choice;
        switch (choice) {
        case 1:
            userCli(user);
            break;
        case 2:
            BookCli(book);
            break;
        case 3:
            return;
        case 4:
            cout << "Exiting program..." << endl;
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 4);
}

#endif
