#ifndef BOOK_MODEL_H
#define BOOK_MODEL_H

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include "../db/db.h"
#include <iostream>
using namespace std;

class Books
{
public:
    int id;
    string title;
    string author;
    int publish_year;
    double price;
    string genre;
    string created_at;
    string updated_at;

    Books(int _id, const string &_title, const string &_author, const int &_publish_year,
          const double &_price, const string &_genre, const string &_created_at, const string &_updated_at)
        : id(_id), title(_title), author(_author), publish_year(_publish_year), price(_price), genre(_genre), created_at(_created_at), updated_at(_updated_at) {}

    Books() : id(0), title(""), author(""), publish_year(0), price(0.0), genre(""), created_at(""), updated_at("") {}

static void insert_book(Books &book)
{
    try
    {
        auto con = DBconnection::getConnection();
        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement(
            "INSERT INTO book (title, author, publish_year, price, genre, created_at) VALUES (?, ?, ?, ?, ?, NOW())"));
        pstmt->setString(1, book.title);
        pstmt->setString(2, book.author);
        pstmt->setInt(3, book.publish_year);
        pstmt->setDouble(4, book.price);
        pstmt->setString(5, book.genre);
        pstmt->execute();
        cout << "Book inserted successfully." << endl;
    }
    catch (sql::SQLException &e)
    {
        cerr << "SQL Error: " << e.what() << endl;
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << '\n';
    }
}

    static bool deleteBook(int bookID)
    {
        try
        {
            auto con = DBconnection::getConnection();
            unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement(
                "DELETE FROM book WHERE id = ?"));
            pstmt->setInt(1, bookID);
            pstmt->execute();
            cout << "Book Deleted Successfully" << endl;
        }
        catch (sql::SQLException &e)
        {
            cerr << "SQL Error " << e.what() << endl;
        }
        catch (const exception &e)
        {
            cerr << " ERROR :)" << e.what() << '\n';
        }
        return true;
    }

    static void updateBook(int bookId, Books &updateBook)
    {
        try
        {
            auto con = DBconnection ::getConnection();
            unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement(
                "UPDATE book SET title = ?, author = ?, publish_year =?, price =?,genre =?, updated_at = NOW() WHERE id = ?"));
            pstmt->setString(1, updateBook.title);
            pstmt->setString(2, updateBook.author);
            pstmt->setInt(3, updateBook.publish_year);
            pstmt->setDouble(4, updateBook.price);
            pstmt->setString(5, updateBook.genre);
            pstmt->setInt(6, bookId);
            pstmt->execute();
            cout << "Book updated Successfully";
        }
        catch (sql::SQLException &e)
        {
            cerr << "SQL Error :)" << e.what() << endl;
        }
        catch (const exception &e)
        {
            cerr << e.what() << '\n';
        }
    }

    // fetch all books
    static vector<Books> findAllBook()
    {
        vector<Books> books;
        try
        {
            auto con = DBconnection::getConnection();
            unique_ptr<sql::PreparedStatement> stmt(con->prepareStatement("SELECT * FROM book"));
            unique_ptr<sql::ResultSet> res(stmt->executeQuery());

            while (res->next())
            {
                books.emplace_back(res->getInt("id"), res->getString("title"), res->getString("author"),
                                   res->getInt("publish_year"), res->getDouble("price"), res->getString("genre"),
                                   res->getString("created_at"), res->getString("updated_at"));
            }
        }
        catch (sql::SQLException &e)
        {
            cerr << "SQL Error : " << e.what() << endl;
        }
        catch (const exception &e)
        {
            cerr << "Error : " << e.what() << '\n';
        }
        return books;
    }

    // Find a Book by ID
    static Books findBookById(int bookId)
    {
        try
        {
            auto con = DBconnection::getConnection();
            unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement(
                "SELECT * FROM book WHERE id = ?"));
            pstmt->setInt(1, bookId);
            unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

            if (res->next())
            {
                return Books(res->getInt("id"), res->getString("author"), res->getString("title"),
                             res->getInt("publish_year"), res->getDouble("price"), res->getString("genre"),
                             res->getString("created_at"), res->getString("updated_at"));
            }
            else
            {
                throw runtime_error("Book not found.");
            }
        }
        catch (const sql::SQLException &e)
        {
            cerr << "SQL Error: " << e.what() << endl;
            throw;
        }
        catch (const exception &e)
        {
            cerr << "Error: " << e.what() << endl;
            throw;
        }
    }
    static bool isDatabaseEmpty()
    {
        try
        {
            auto con = DBconnection::getConnection();
            unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT COUNT(*) AS userCount FROM book"));
            unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

            if (res->next())
            {
                int bookCount = res->getInt("bookCount");
                return bookCount == 0;
            }
        }
        catch (const sql::SQLException &e)
        {
            cerr << "SQL Error: " << e.what() << endl;
        }
        catch (const exception &e)
        {
            cerr << "Error: " << e.what() << endl;
        }
        return true;
    }
};
#endif