#ifndef USER_MODEL_H
#define USER_MODEL_H

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <iostream>
#include <vector>
#include "../db/db.h"

using namespace std;

class User
{
public:
    int id;
    string first_name;
    string last_name;
    string email;
    string phone;
    string password;
    vector<int> books;
    string created_at;
    string updated_at;

    // Constructor for existing users
    User(int _id, const string &_first_name, const string &_last_name, const string &_email,
         const string &_phone, const string &_password, const string &_created_at, const string &_updated_at)
        : id(_id), first_name(_first_name), last_name(_last_name), email(_email),
          phone(_phone), password(_password), created_at(_created_at), updated_at(_updated_at) {}

    User(const string &_first_name, const string &_last_name, const string &_email,
         const string &_phone, const string &_password)
        : id(0), first_name(_first_name), last_name(_last_name), email(_email),
          phone(_phone), password(_password), created_at("NOW()"), updated_at("NOW()") {}

    User() : id(0), first_name(""), last_name(""), email(""), phone(""), password(""), created_at(""), updated_at("") {}

    // Insert new user into the database
    static void InsertUser(const User &user)
    {
        try
        {
            auto con = DBconnection::getConnection();
            unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement(
                "INSERT INTO users (first_name, last_name, email, phone, password, created_at) VALUES (?, ?, ?, ?, ?, NOW())"));
            pstmt->setString(1, user.first_name);
            pstmt->setString(2, user.last_name);
            pstmt->setString(3, user.email);
            pstmt->setString(4, user.phone);
            pstmt->setString(5, user.password);
            pstmt->execute();
        }
        catch (sql::SQLException &e)
        {
            cerr << "SQL Error: " << e.what() << endl;
        }
        catch (const exception &e)
        {
            cerr << "Error: " << e.what() << endl;
        }
    }

    static void updateUser(int userId, const User &updateUser)
    {
        try
        {
            auto con = DBconnection::getConnection();
            unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement(
                "UPDATE users SET first_name = ?, last_name = ?, email = ?, phone = ?, password = ?, updated_at = NOW() WHERE id = ?"));
            pstmt->setString(1, updateUser.first_name);
            pstmt->setString(2, updateUser.last_name);
            pstmt->setString(3, updateUser.email);
            pstmt->setString(4, updateUser.phone);
            pstmt->setString(5, updateUser.password);
            pstmt->setInt(6, userId);
            pstmt->execute();
        }
        catch (sql::SQLException &e)
        {
            cerr << "SQL Error: " << e.what() << endl;
        }
        catch (const exception &e)
        {
            cerr << "Error: " << e.what() << endl;
        }
    }

    static bool deleteUser(int userId)
    {
        try
        {
            auto con = DBconnection::getConnection();
            unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("DELETE FROM users WHERE id = ?"));
            pstmt->setInt(1, userId);
            pstmt->execute();
            cout << "User Deleted Successfully" << endl;
        }
        catch (sql::SQLException &e)
        {
            cerr << "SQL Error: " << e.what() << endl;
        }
        catch (const exception &e)
        {
            cerr << "Error: " << e.what() << endl;
        }
        return true;
    }

    static vector<User> findAllUsers()
    {
        vector<User> users;
        try
        {
            auto con = DBconnection::getConnection();
            unique_ptr<sql::PreparedStatement> stmt(con->prepareStatement("SELECT * FROM users"));
            unique_ptr<sql::ResultSet> res(stmt->executeQuery());

            while (res->next())
            {
                users.emplace_back(res->getInt("id"), res->getString("first_name"), res->getString("last_name"),
                                   res->getString("email"), res->getString("phone"), res->getString("password"),
                                   res->getString("created_at"), res->getString("updated_at"));
            }
        }
        catch (sql::SQLException &e)
        {
            cerr << "SQL Error: " << e.what() << endl;
        }
        catch (const exception &e)
        {
            cerr << "Error: " << e.what() << endl;
        }
        return users;
    }

    static User findUserById(int userId)
    {
        try
        {
            auto con = DBconnection::getConnection();
            unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT * FROM users WHERE id = ?"));
            pstmt->setInt(1, userId);
            unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

            if (res->next())
            {
                return User(res->getInt("id"), res->getString("first_name"), res->getString("last_name"),
                            res->getString("email"), res->getString("phone"), res->getString("password"),
                            res->getString("created_at"), res->getString("updated_at"));
            }
            else
            {
                throw runtime_error("User not found.");
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
        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT COUNT(*) AS userCount FROM users"));
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        if (res->next())
        {
            int userCount = res->getInt("userCount");
            return userCount == 0;
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
