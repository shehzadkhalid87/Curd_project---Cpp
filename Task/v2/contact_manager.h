#ifndef CONTACTHEADER
#define CONTACTHEADER

#include "storage_manager.h"
#include "validation_manager.h"
#include <string>
#include <vector>
#include "utility.h"

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



public:
    ContactManager(string filepath) : storage(filepath)
    {
        contacts = storage.loadData<Contact>();
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

// new item creation function
void createNewContact(string f_n, string l_n, string ph, string em, int age, string gender)
{
    string ID = generate_uuid_v4();
    Contact new_contact(ID, f_n, l_n, ph, em, age, gender);
    contacts.push_back(new_contact);
    storage.writeData(contacts);

    cout << "Contact created successfully!" << endl;
}

    // displaying all data
    void getAllContacts() const
    {
        cout << left << setw(10) << "ID"
             << setw(18) << "First_name"
             << setw(18) << "Last_name"
             << setw(18) << "Phone"
             << setw(40) << "Email"
             << setw(38) << "Age"
             << setw(10) << "Gender" << endl;
        cout << string(160, '-') << endl;

        for (const auto &contact : contacts)
        {
            cout << string(160, '-') << endl;
            cout << left << setw(10) << contact.get_id() // Adjusted to match ID width in header
                 << setw(18) << contact.first_name
                 << setw(18) << contact.last_name
                 << setw(18) << contact.phone
                 << setw(40) << contact.email
                 << setw(38) << contact.age // Adjusted width for Age
                 << setw(10) << contact.gender << endl;
            cout << string(160, '-') << endl;
            // cout << contact.to_json().dump(4) << endl;
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

#endif