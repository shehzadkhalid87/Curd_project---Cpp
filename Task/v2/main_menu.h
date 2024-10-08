#ifndef MAINMENU_H
#define MAINMENU_H

#include "iostream"
#include "validation_manager.h"
#include "contact_manager.h"
#include "car_manager.h"
#include "book_manager.h"

using namespace std;

// Main Menu Implementation
void showMenu()
{
    cout << "\n***********************************\n";
    cout << "        WELCOME TO CRUD MANAGER\n";
    cout << "***********************************\n";
    cout << "Please choose an option:\n";
    cout << "1. Contacts\n";
    cout << "2. Books\n";
    cout << "3. Cars\n";
    cout << "4. Exit\n";
    cout << "***********************************\n";
}

void contactMenu(ContactManager &manager)
{
    int choice;
    do
    {
        cout << "\n***********************************\n";
        cout << "        WELCOME TO CONTACT MANAGER\n";
        cout << "***********************************\n";
        cout << "1. Create a contact\n";
        cout << "2. Print all contacts\n";
        cout << "3. Update a contact\n";
        cout << "4. Get contact by ID\n";
        cout << "5. Delete a contact\n";
        cout << "6. Return to main menu\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string f_n, l_n, ph, em, gender;
            int age;

            f_n = validateName("Enter first name: ");
            l_n = validateName("Enter last name: ");

            do
            {
                ph = validatePhone("Enter phone number: ");
                if (manager.isPhoneExist(ph))
                {
                    cout << "Error: A contact with this phone number (" << ph << ") already exists." << endl;
                }
            } while (manager.isPhoneExist(ph));

            do
            {
                em = validateEmail("Enter email: ");
                if (manager.isEmailExist(em))
                {
                    cout << "Error: A contact with this email (" << em << ") already exists." << endl;
                }
            } while (manager.isEmailExist(em));

            age = validateIntegers("Enter age: ");
            gender = validateGender("Enter gender (M/F): ");

            manager.createNewContact(f_n, l_n, ph, em, age, gender);
            break;
        }
        case 2:
            manager.getAllContacts();
            break;
        case 3:
        {
            string id, f_n, l_n, ph, em, gender;
            int age;
            cout << "Enter contact ID to update: ";
            cin >> id;

            f_n = validateName("Enter first name: ");
            l_n = validateName("Enter last name: ");

            do
            {
                ph = validatePhone("Enter phone number: ");
                if (manager.isPhoneExist(ph))
                {
                    cout << "Error: A contact with this phone number (" << ph << ") already exists." << endl;
                }
            } while (manager.isPhoneExist(ph));

            do
            {
                em = validateEmail("Enter email: ");
                if (manager.isEmailExist(em))
                {
                    cout << "Error: A contact with this email (" << em << ") already exists." << endl;
                }
            } while (manager.isEmailExist(em));

            age = validateIntegers("Enter age: ");
            gender = validateGender("Enter gender (M/F): ");

            manager.updateContactById(id, f_n, l_n, ph, em, age, gender);
            break;
        }
        case 4:
        {
            string id;
            cout << "Enter contact ID: ";
            cin >> id;
            manager.getcontactbyId(id);
            break;
        }
        case 5:
        {
            string id;
            cout << "Enter contact ID to delete: ";
            cin >> id;
            manager.deleteContactbyId(id);
            break;
        }
        case 6:
            return;
        case 7:
            cout << "Exiting the program." << endl;
            exit(0);
        default:
            cout << "Invalid option. Please try again." << endl;
        }
    } while (choice != 7);
}

// Book Manager Menu Implementation
void bookMenu(BookManager &manager)
{
    int choice;
    do
    {
        cout << "\n***********************************\n";
        cout << "        WELCOME TO BOOK MANAGER\n";
        cout << "***********************************\n";
        cout << "1. Add a new book\n";
        cout << "2. Print all books\n";
        cout << "3. Update a book\n";
        cout << "4. Get book by ID\n";
        cout << "5. Delete a book\n";
        cout << "6. Return to main menu\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string title, author, genre;
            float price;
            int publicationYear;

            title = validateName("Enter book title: ");
            author = validateName("Enter author name: ");
            genre = validateName("Enter genre: ");
            price = validateFloat("Enter price: ");
            publicationYear = validateIntegers("Enter publication year: ");

            manager.createNewBook(author, title, publicationYear, price, genre);

            break;
        }
        case 2:
            manager.getAllBooks();
            break;
        case 3:
        {
            string id, title, author, genre;
            float price;
            int publicationYear;

            cout << "Enter book ID to update: ";
            cin >> id;
            title = validateName("Enter new book title: ");
            author = validateName("Enter new author name: ");
            genre = validateName("Enter new genre: ");
            price = validateFloat("Enter new price: ");
            publicationYear = validateIntegers("Enter new publication year: ");

            manager.updatebookById(id, title, author, genre, price, publicationYear);
            break;
        }
        case 4:
        {
            string id;
            cout << "Enter book ID: ";
            cin >> id;
            manager.getbookbyId(id);
            break;
        }
        case 5:
        {
            string id;
            cout << "Enter book ID to delete: ";
            cin >> id;
            manager.deleteBook(id);
            break;
        }
        case 6:
            return;
            cout << "Exiting the program." << endl;
            exit(0);
        default:
            cout << "Invalid option. Please try again." << endl;
        }
    } while (choice != 7);
}
// Car Manager Menu Implementation
void carMenu(CarManager &manager)
{
    int choice;
    do
    {
        cout << "\n***********************************\n";
        cout << "        WELCOME TO CAR MANAGER\n";
        cout << "***********************************\n";
        cout << "1. Add a new car\n";
        cout << "2. Print all cars\n";
        cout << "3. Update a car\n";
        cout << "4. Get car by ID\n";
        cout << "5. Delete a car\n";
        cout << "6. Return to main menu\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string ID,make, model, color;
            int year;
            float price;
            do
            {
                if (manager.isIdExists(ID))
                {
                    cout << "Car with id " << ID << " already exists" << endl;
                    return;
                }
            }while(!manager.isIdExists(ID));
            make = validateName("Enter car make: ");
            model = validateName("Enter car model: ");
            year = validateIntegers("Enter year of manufacture: ");
            price = validateFloat("Enter price: ");
            color = validateName("Enter car color: ");

            manager.createNewCar(make, model, year, price, color);
            break;
        }
        case 2:
            manager.getAllCars();
            break;
        case 3:
        {
            string id, make, model, color;
            int year;
            float price;

            cout << "Enter car ID to update: ";
            cin >> id;
            make = validateName("Enter new car make: ");
            model = validateName("Enter new car model: ");
            year = validateIntegers("Enter new year of manufacture: ");
            price = validateFloat("Enter new price: ");
            color = validateName("Enter car color: ");

            manager.createNewCar(make, model, year, price, color);

            break;
        }
        case 4:
        {
            string id;
            cout << "Enter car ID: ";
            cin >> id;
            manager.getCarById(id);
            break;
        }
        case 5:
        {
            string id;
            cout << "Enter car ID to delete: ";
            cin >> id;
            manager.deleteCarById(id);
            break;
        }
        case 6:
            return;
        case 7:
            cout << "Exiting the program." << endl;
            exit(0);
        default:
            cout << "Invalid option. Please try again." << endl;
        }
    } while (choice != 7);
}

void allMenu(ContactManager &contactManager, BookManager &bookManager, CarManager &carManager)
{
    int choice;
    do
    {
        showMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            contactMenu(contactManager);
            break;
        case 2:
            bookMenu(bookManager);
            break;
        case 3:
            carMenu(carManager);
            break;
        case 4:
            cout << "Exiting program..." << endl;
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 4);
}

#endif
