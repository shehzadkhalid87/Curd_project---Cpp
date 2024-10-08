#ifndef STORAGEMANAGER_H
#define STORAGEMANAGER_H

#include "iostream"
#include "fstream"
#include "vector"
#include "nlohmann/json.hpp"

using json = nlohmann::ordered_json;
using namespace std;

class StorageManager
{
private:
    string filepath;

public:
    StorageManager(string filepath) : filepath(filepath) {}
    template <typename T>
    vector<T> loadData()
    {
        ifstream file(filepath);
        if (!file.is_open())
        {
            cout << "File not found" << endl;
            return {};
        }
        json js;
        file >> js;
        vector<T> data;
        for (auto &items : js)
        {
            data.emplace_back(T::fromJson(items));
        }
        return data;
    }
    template <typename T>
    void writeData(vector<T> &data)
    {
        json js;
        for (auto &item : data)
        {
            js.emplace_back(item.to_json());
        }
        ofstream file(filepath);
        if (!file.is_open())
        {
            cout << "Error! could not open file for writting" << endl;
            return;
        }
        file << js.dump(4);
    }
};
#endif