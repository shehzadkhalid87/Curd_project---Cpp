#include "storagemanager.h"
#include <string>
#include <vector>
using namespace std;

class Contact
{
public:
    string id;
    string first_name;
    string last_name;
    string phone;
    string email;
    int age;
    string gender;

    Contact(string id, string f_n, string l_n, string ph, string em, int age, string gender)
        : id(id), first_name(f_n), last_name(l_n), phone(ph), email(em), age(age), gender(gender) {}

    json to_json() const
    {
        json js;
        js["id"] = id;
        js["first_name"] = first_name;
        js["last_name"] = last_name;
        js["phone"] = phone;
        js["email"] = email;
        js["age"] = age;
        js["gender"] = gender;
        return js;
    }

    static Contact fromJson(const json &js)
    {
        return Contact(
            js["id"].get<string>(),
            js["first_name"].get<string>(),
            js["last_name"].get<string>(),
            js["phone"].get<string>(),
            js["email"].get<string>(),
            js["age"].get<int>(),
            js["gender"].get<string>());
    }
    string get_id() const
    {
        return id;
    }
};

class ContactManager
{
private:
    vector<Contact> contacts;
    StorageManager storage;
    int uniqueId;

    string generate_id()
    {
        return "C00" + to_string(uniqueId++);
    }
    bool isIdExist(const string &id) const
    {
        return any_of(contacts.begin(), contacts.end(), [&id](const Contact &contact)
                      { return contact.get_id() == id; });
    }

    bool isPhoneExist(const string &ph) const
    {
        return any_of(contacts.begin(), contacts.end(), [&ph](const Contact &contact)
                      { return contact.phone == ph; });
    }

    bool isEmailExist(const string &email) const
    {
        return any_of(contacts.begin(), contacts.end(), [&email](const Contact &contact)
                      { return contact.email == email; });
    }

public:
    ContactManager(string filepath) : storage(filepath), uniqueId(1)
    {
        contacts = storage.loadData<Contact>();
    }

    // new item creation function
    void createNewContact(string f_n, string l_n, string ph, string em, int age, string gender)
    {
        string ID = generate_id();
        if (isIdExist(ID))
        {
            cout << "Contact with ID " << ID << " already exists." << endl;
            return;
        }
        if (isPhoneExist(ph))
        {
            cout << "Contact with phone " << ph << " already exists." << endl;
            return;
        }
        if (isEmailExist(em))
        {
            cout << "Contact with email " << em << " already exists." << endl;
            return;
        }
        Contact new_contact(ID, f_n, l_n, ph, em, age, gender);
        contacts.push_back(new_contact);
        storage.writeData(contacts);
    }
    // displaying all data
    void getAllContacts() const
    {
        for (const auto &contact : contacts)
        {
            cout << contact.to_json().dump(4) << endl;
        }
    }
    // getting contact by id
    Contact *getcontactbyId(const string &id)
    {
        for (auto &items : contacts)
            if (items.get_id() == id)
            {
                cout << "Contact with id " << items.to_json().dump(4);
                return &items;
            }

        cout << "Contact with id " << id << " not found in contact file" << endl;

        return nullptr;
    }
    // updating contact by id
    void updateContactById(string id, string f_n, string l_n, string ph, string em, int age, string gender)
    {
        auto it = find_if(contacts.begin(), contacts.end(), [&id](const Contact &contact)
                          { return contact.get_id() == id; });

        if (it != contacts.end())
        {
            // Update the fields
            it->first_name = f_n;
            it->last_name = l_n;
            it->phone = ph;
            it->email = em;
            it->age = age;
            it->gender = gender;
            storage.writeData(contacts);
        }
        else
        {
            cout << "Contact with ID " << id << " not found." << endl;
        }
    }
    // deleting contact by id
    void deleteContactbyId(const string &id)
    {
        auto it = remove_if(contacts.begin(), contacts.end(), [&id](const Contact &c)
                            { return c.get_id() == id; });
        if (it != contacts.end())
        {
            contacts.erase(it, contacts.end());
            storage.writeData(contacts);
        }
        else
        {
            cout << "contact with id " << id << " delete successfully " << endl;
        }
    }
};

/**
 * ***********************************
 *        WELCOME TO CRUD MANAGER
 * ***********************************
 * Please choose an option
 * 1. Contacts
 * 2. Books
 * 3. Cars
 * 4. Exit
 * ***********************************
 * If user enter 1
 * ***********************************
 *        WELCOME TO CONTACT MANAGER
 * ***********************************
 * Please choose an option
 * 1. Create a contact
 * 2. Print all contacts
 * 3. Update a contact
 * 4. Get contact by ID
 * 5. Delete a contact
 * 6. Return to menue
 * 7. Exit
 *
 * ************************************
 * if user select option 1
 * Please enter the following data for contact
 * *******************************************
 * Please enter the name:
 * *******************************************
 * Please enter email:
 * *******************************************
 * Please enter phone: sdfjwskdf1232
 * // if user enter invalid phone
 * Please enter a valid phone:
 * *******************************************
 * Please enter username:
 * *******************************************
 *
 */