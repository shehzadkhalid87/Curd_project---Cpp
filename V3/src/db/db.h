#ifndef DB_H
#define DB_H

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <memory>

using namespace std;

class DBconnection {
public:
    static shared_ptr<sql::Connection> getConnection() {
        static sql::mysql::MySQL_Driver *driver = sql::mysql::get_mysql_driver_instance();
        
        shared_ptr<sql::Connection> con(driver->connect("tcp://127.0.0.1:3306", "root", "root"));
        con->setSchema("Users");
        return con;
    }
};

#endif