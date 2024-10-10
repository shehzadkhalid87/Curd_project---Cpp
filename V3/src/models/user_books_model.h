#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include "../db/db.h"
#include <iostream>
using namespace std;

class UserBook
{
public:
    int user_id;
    int book_id;
    UserBook(int _user_id, int _book_id) : user_id(_user_id), book_id(_book_id) {}

    static void createUserBook(int userId, int bookId)
    {
        try
        {
            auto con = DBconnection::getConnection();
            unique_ptr<sql ::PreparedStatement> pstmt(con->prepareStatement(
                "INSERT INTO user_books (user_id, book_id) VALUE(?,?,NOW())"

                ));
            pstmt->setInt(1, userId);
            pstmt->setInt(2, bookId);
            pstmt->execute();
            cout << "User_Book realtionship created sucessfully" << endl;
        }
        // display sql error
        catch (sql::SQLException &e)
        {
            cerr << "SQL ERROR!" << e.what() << '\n';
        }
        // handle other error
        catch (const exception &e)
        {
            cerr << "Error: " << e.what() << endl;
        }
    }

    // delete a user-book relation
    static void deleteUserBook(int userId, int bookId)
    {
        try
        {
            auto con = DBconnection::getConnection();
            unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement(
                "DELETE FROM user_books WHERE user_id =? AND book_id =?"));
            pstmt->setInt(1, userId);
            pstmt->setInt(2, bookId);
            pstmt->execute();
            cout << "User_Book realtionship deleted successfully" << endl;
        }
        catch (sql::SQLException &e)
        {
            cerr << "SQL Error" << e.what() << endl;
        }
        catch (const exception &e)
        {
            cerr << " ERORR" << e.what() << '\n';
        }
    }

    // method to update
    static void updateUserBook(int oldUserId, int oldBookId, int newUserId, int newBookId)
    {
        try
        {
            auto con = DBconnection::getConnection();
            unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement(
                "UPDATE user_books SET user_id =?, book_id SET book_id =? WHERE user_id =? AND book_id =?"));
            pstmt->setInt(1, newUserId);
            pstmt->setInt(2, newBookId);
            pstmt->setInt(3, oldUserId);
            pstmt->setInt(4, oldBookId);
            cout << "User - Book realtionship Upadted Successfully " << endl;
        }
        catch (sql::SQLException &e)
        {
            cerr << "SQL Error :)" << e.what() << endl;
        }
        catch (const exception &e)
        {
            cerr << "Error :)" << e.what() << '\n';
        }
    }

};