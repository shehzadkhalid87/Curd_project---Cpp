#ifndef BOOK_SERVICES_H
#define BOOK_SERVICES_H

#include "books_model.h" 

class BookService {
public:
   
    void createBook(const string& title, const string& author, int publishYear,
                    double price, const string& genre) {
        Books newBook(0, title, author, publishYear, price, genre, "", "");
        Books::insert_book(newBook);
    }


    void updateBook(int bookId, const string& title, const string& author, int publishYear,
                    double price, const string& genre) {
        Books updateBook(bookId, title, author, publishYear, price, genre, "", "");
        Books::updateBook(bookId, updateBook);
    }


    void deleteBook(int bookId) {
        Books::deleteBook(bookId);
    }


    vector<Books> getAllBooks() {
        return Books::findAllBook();
    }

    Books findBookById(int bookId) {
        return Books::findBookById(bookId);
    }
};

#endif
