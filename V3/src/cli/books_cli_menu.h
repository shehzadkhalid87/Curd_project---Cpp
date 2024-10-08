#ifndef BOOK_CLI_HEADER
#define BOOK_CLI_HEADER

#include "iostream"
#include "../models/books_model.h"
#include "../validation/validation_manager.h"
using namespace std;
void BookCli(Books &book)
{
    int choice;
    string title, author, genre;
    int publish_year;
    double price;

    do
    {
        cout << "\n**********************************************\n";
        cout << "       WELCOME TO BOOK MANAGEMENT SYSTEM\n";
        cout << "**********************************************\n";
        cout << "1. Insert New Book Data:\n";
        cout << "2. Delete Book:\n";
        cout << "3. Update Book By ID:\n";
        cout << "4. Find Book By ID:\n";
        cout << "5. View All Books:\n";
        cout << "6. Return Back:\n";
        cout << "7. Exit Program (0):\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            // Insert a new book
            title = validateName("Enter book title: ");
            author = validateName("Enter author name: ");
            publish_year = validateIntegers("Enter publication year: ");
            genre = validateName("Enter genre: ");
            price = validateFloat("Enter price: ");
            Books newBook(0, title, author, publish_year, price, genre, "", "");
            book.insert_book(newBook);
            break;
        }

        case 2:
        {
            // Delete a book by ID
            int id;
            if (Books::isDatabaseEmpty())
            {
                cout << "Database is empty!\n";
                break;
            }

            cout << "Enter Book ID to delete: ";
            cin >> id;

            if (Books::deleteBook(id))
            {
                cout << "Book deleted successfully.\n";
            }
            else
            {
                cout << "Book ID not found!\n";
            }
            break;
        }

        case 3:
        {
            // Update a book by ID
            int id;
            cout << "Enter the ID of the book to update: ";
            cin >> id;

            cout << "Enter updated values for the book:\n";
            cout << "**************************************\n";
            title = validateName("Enter book title: ");
            author = validateName("Enter author name: ");
            publish_year = validateIntegers("Enter publication year: ");
            genre = validateName("Enter genre: ");
            price = validateFloat("Enter price: ");
            Books updatedBook(id, title, author, publish_year, price, genre, "", "");
            book.updateBook(id, updatedBook);
            break;
        }

        case 4:
        {
            int id;
            cout << "Enter book ID to find: ";
            cin >> id;
            try
            {
                Books foundBook = book.findBookById(id);
                cout << "\nBook found:\n";
                cout << "ID: " << foundBook.id << "\n"
                     << "Title: " << foundBook.title << "\n"
                     << "Author: " << foundBook.author << "\n"
                     << "Year: " << foundBook.publish_year << "\n"
                     << "Genre: " << foundBook.genre << "\n"
                     << "Price: " << foundBook.price << "\n"
                     << "Created At: " << foundBook.created_at << "\n"
                     << "Updated At: " << foundBook.updated_at << endl;
            }
            catch (const exception &e)
            {
                cerr << "Error: " << e.what() << endl;
            }
            break;
        }

        case 5:
        {
            // View all books
            vector<Books> books = Books::findAllBook();
            for (const auto &book : books)
            {
                cout << "ID: " << book.id << ", Book Title: " << book.title
                     << ", Author: " << book.author << ", Year: " << book.publish_year
                     << ", Price: " << book.price << ", Genre: " << book.genre << endl;
            }
            break;
        }

        case 6:
        {
            return;
        }

        case 7:
        {
            cout << "Exiting the program." << endl;
            exit(0);
        }

        default:
        {
            cout << "Invalid option. Please try again." << endl;
        }
        }
    } while (choice != 7);
}

#endif
