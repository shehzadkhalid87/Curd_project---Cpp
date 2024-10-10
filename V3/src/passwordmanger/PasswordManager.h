#ifndef PASSWORD_MANAGER_H
#define PASSWORD_MANAGER_H

#include <string>
#include "bcrypt/BCrypt.hpp"

class PasswordManager {
public:
    static string hashPassword(const string& password) {
       
        return BCrypt::generateHash(password);
    }

    static bool comparePassword(const string& password, const string& hashedPassword) {
       
        return BCrypt::validatePassword(password, hashedPassword);
    }
};

#endif 
