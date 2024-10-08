#include "storagemanager.h"
#include <string>
#include <vector>
using namespace std;

class Car
{
public:
    string id;
    string name;
    string brand;
    int publish_year;
    float price;
    string model;
    string color;

    Car(string id, string name, string brand, int publish_year, float price, string model, string color)
        : id(id), name(name), brand(brand), publish_year(publish_year), price(price), model(model), color(color) {}

    json to_json() const
    {
        json js;
        js["id"] = id;
        js["name"] = name;
        js["brand"] = brand;
        js["publish_year"] = publish_year;
        js["price"] = price;
        js["model"] = model;
        js["color"] = color;
        return js;
    }

    static Car fromJson(const json &js)
    {
        return Car(
            js["id"].get<string>(),
            js["name"].get<string>(),
            js["brand"].get<string>(),
            js["publish_year"].get<int>(),
            js["price"].get<float>(),
            js["model"].get<string>(),
            js["color"].get<string>());
    }

    string getid() const
    {
        return id;
    }
};

class CarManager
{
private:
    vector<Car> cars;
    StorageManager storage;
    int uniqueId;

    string generate_id()
    {
        return "CAR" + to_string(uniqueId++);
    }
    bool isIdExists(const string &id) const
    {
        return any_of(cars.begin(), cars.end(), [&id](const Car &car)
                      { return car.getid() == id; });
    }

public:
    CarManager(string filepath) : storage(filepath), uniqueId(1)
    {
        cars = storage.loadData<Car>();
    }

    void createNewCar(string name, string brand, int publish_year, float price, string model, string color)
    {
        string ID = generate_id();
        if(isIdExists(ID)){
            cout<< "Car with id " << ID << "already exists" <<endl;
            return;
        }
        Car new_car(ID, name, brand, publish_year, price, model, color);
        cars.push_back(new_car);
        storage.writeData(cars);
    }
    Car *getCarById(const string &id)
    {
        for (auto &car : cars)
        {
            if (car.getid() == id)
            {
                cout << "Car with Id: " << car.to_json().dump(5) << endl;
                return &car;
            }
        }
        cout << "Car with Id " << id << " not found" << endl;
        return nullptr;
    }
    void deleteCar(const string &id)
    {
        auto it = remove_if(cars.begin(), cars.end(), [&id](const Car &car)
                            { return car.getid() == id; });
        if (it != cars.end())
        {
            cars.erase(it, cars.end());
            storage.writeData(cars);
        }
        else
        {
            cout << "Car with ID " << id << " delete sucessfully :(" << endl;
        }
    }
        void updateCarById(string id,string name, string brand, int publish_year, float price, string model, string color)
    {
        auto it = find_if(cars.begin(), cars.end(), [&id](const Car &car)
                          { return car.getid() == id; });

        if (it != cars.end())
        {
            // Update the fields
            it-> name = name;
            it->brand = brand;
            it->publish_year= publish_year;
            it->price = price;
            it-> model = model;
            it->color = color;
            storage.writeData(cars);
        }
        else
        {
            cout << "Car with ID " << id << " not found." << endl;
        }
    }

    void getAllCars() const
    {
        for (const auto &car : cars)
        {
            cout << car.to_json().dump(4) << endl;
        }
    }

};
