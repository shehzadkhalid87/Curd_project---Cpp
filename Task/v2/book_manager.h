#ifndef BOOKHEADER
#define BOOKHEADER

#include "storage_manager.h"
#include <string>
#include <vector>

using namespace std;

class BookEntity
{
public:
    string id;
    string author;
    string title;
    int publish_year;
    float price;
    string genre;

    BookEntity(string id, string author, string title, int publish_year, float price, string genre)
        : id(id), author(author), title(title), publish_year(publish_year), price(price), genre(genre) {}

    json to_json() const
    {
        json js;
        js["id"] = id;

        js["title"] = title;
        js["author"] = author;
        js["publish_year"] = publish_year;
        js["price"] = price;
        js["genre"] = genre;
        return js;
    }

    static BookEntity fromJson(const json &js)
    {
        return BookEntity(
            js["id"].get<string>(),
            js["title"].get<string>(),
            js["author"].get<string>(),

            js["publish_year"].get<int>(),
            js["price"].get<float>(),
            js["genre"].get<string>());
    }

    string getid() const
    {
        return id;
    }
};

class BookManager
{
private:
    vector<BookEntity> books;
    StorageManager storage;

public:
    BookManager(string filepath) : storage(filepath)
    {
        books = storage.loadData<BookEntity>();
    }
    bool isIdExist(const string &id)
    {
        return any_of(books.begin(), books.end(), [&id](const BookEntity &book)
                      { return book.getid() == id; });
    }

    void createNewBook(string author, string title, int publish_year, float price, string genre)

    {
        string ID = generate_uuid_v4();
        BookEntity new_book(ID, author, title, publish_year, price, genre);
        books.push_back(new_book);
        storage.writeData(books);
    }
    void deleteBook(const string &id)
    {
        auto it = remove_if(books.begin(), books.end(), [&id](const BookEntity &b)
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
    BookEntity *getbookbyId(string id)
    {
        for (auto &book : books)
        {
            if (book.getid() == id)
            {
                cout << "Book with id : " << book.to_json().dump(4) << endl;
                return &book;
            }
        }
        cout << "Book with id " << id << " not found" << endl;
        return nullptr;
    }
    // Update a book by ID
    void updatebookById(string id, string author, string title, string genre, float price, int publish_year)

    {
        auto it = find_if(books.begin(), books.end(), [&id](const BookEntity &book)
                          { return book.getid() == id; });

        if (it != books.end())
        {
            // Update the fields
            it->author = author;
            it->title = title;
            it->publish_year = publish_year;
            it->price = price;
            it->genre = genre; // Include genre
            storage.writeData(books);
        }
        else
        {
            cout << "Book with ID " << id << " not found." << endl;
        }
    }

    void getAllBooks() const
    {
        cout << string(130, '-') << endl;
        cout << left << setw(50) << "ID"
             << setw(30) << "Title"
             << setw(20) << "Author"
             << setw(20) << "Publish_year"
             << setw(18) << "price" << endl;
        cout << string(130, '-') << endl;
        for (const auto &book : books)
        {
            cout << left << setw(50) << book.getid()
                 << setw(30) << book.author
                 << setw(20) << book.title
                 << setw(20) << book.publish_year
                 << setw(20) << fixed << setprecision(2) << book.price << endl;
            cout << string(130, '-') << endl;
            // cout << book.to_json().dump(4) << endl;
        }
    }
};

#endif