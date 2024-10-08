#ifndef USER_SERVICES_HPP
#define USER_SERVICES_HPP

#include "users_model.cpp" 

class UserService {
public:
   
    void createUser(const string& firstName, const string& lastName, const string& email,
                    const string& phone, const string& password) {
        User newUser(0, firstName, lastName, email, phone, password, "", "");
        User::InsertUser(newUser);
    }

    
    void updateUser(int userId, const string& firstName, const string& lastName, const string& email,
                    const string& phone, const string& password) {
        User updateUser(userId, firstName, lastName, email, phone, password, "", "");
        User::updateUser(userId, updateUser);
    }

    void deleteUser(int userId) {
        User::deleteUser(userId);
    }

   
    vector<User> getAllUsers() {
        return User::findAllUsers();
    }


    User findUserById(int userId) {
        return User::findUserById(userId);
    }
};

#endif
