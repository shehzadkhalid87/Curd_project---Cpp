#include "storagemanager.h"
#include <string>
#include <vector>

using namespace std;

class Book
{
public:
    string id;
    string author;
    string title;
    int publish_year;
    float price;

    Book(string id, string author, string title, int publish_year, float price)
        : id(id), author(author), title(title), publish_year(publish_year), price(price) {}

    json to_json() const
    {
        json js;
        js["id"] = id;
        js["author"] = author;
        js["title"] = title;
        js["publish_year"] = publish_year;
        js["price"] = price;
        return js;
    }

    static Book fromJson(const json &js)
    {
        return Book(
            js["id"].get<string>(),
            js["author"].get<string>(),
            js["title"].get<string>(),
            js["publish_year"].get<int>(),
            js["price"].get<float>());
    }

    string getid() const
    {
        return id;
    }
};

class BookManager
{
private:
    vector<Book> books;
    StorageManager storage;
    int uniqueId;

    string generate_id()
    {
        return "BK" + to_string(uniqueId++);
    }
    bool isIdExist(const string &id)
    {
        return any_of(books.begin(), books.end(), [&id](const Book &book)
                      { return book.getid() == id; });
    }

public:
    BookManager(string filepath) : storage(filepath), uniqueId(1)
    {
        books = storage.loadData<Book>();
    }

    void createNewBook(string author, string title, int publish_year, float price)
    {
        string ID = generate_id();
        if (isIdExist(ID))
        {
            cout << "Book with ID " << ID << " already exist" << endl;
            return;
        }
        Book new_book(ID, author, title, publish_year, price);
        books.push_back(new_book);
        storage.writeData(books);
    }
    void deleteBook(const string &id)
    {
        auto it = remove_if(books.begin(), books.end(), [&id](const Book &b)
                            { return b.getid() == id; });
        if (it != books.end())
        {
            books.erase(it, books.end());
            storage.writeData(books);
            cout << "Book with ID: " << id << " deleted successfully." << endl;
        }
        else
        {
            cout << "Book with ID: " << id << " not found." << endl;
        }
    }
    Book *getbookbyId(string id)
    {
        for (auto &book :books)
        {
            if(book.getid() == id)
            {
                cout<< "Book with id : " << book.to_json().dump(4) <<endl;
                return &book;
            }
        }
        cout<< "Book with id " << id << " not found" <<endl;
        return nullptr;
    }

    void getAllBooks() const
    {
        for (const auto &book : books)
        {
            cout << book.to_json().dump(4) << endl;
        }
    }
    void updatebookById(string id,string author, string title, int publish_year, float price)
    {
        auto it = find_if(books.begin(), books.end(), [&id](const Book &book)
                          { return book.getid() == id; });

        if (it != books.end())
        {
            // Update the fields
            it->author = author;
            it->title = title;
            it->publish_year = publish_year;
            it->price = price;
            storage.writeData(books);
        }
        else
        {
            cout << "Book with ID " << id << " not found." << endl;
        }
    }
};
