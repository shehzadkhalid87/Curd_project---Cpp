#ifndef CARHEADER
#define CARHEADER

#include "storage_manager.h"
#include "validation_manager.h"
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

class Car
{
public:
    string id, make, model, color;
    int year;
    float price;

    // Constructor
    Car(string id, string make, string model, int year, float price, string color)
        : id(id), make(make), model(model), year(year), price(price), color(color) {}

    // Convert object to JSON
    json to_json() const
    {
        json js;
        js["id"] = id;
        js["make"] = make;
        js["model"] = model;
        js["year"] = year;
        js["price"] = price;
        js["color"] = color;
        return js;
    }

    // Create object from JSON
    static Car fromJson(const json &js)
    {
        return Car(
            js["id"].get<string>(),
            js["make"].get<string>(),
            js["model"].get<string>(),
            js["year"].get<int>(),
            js["price"].get<float>(),
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
public:
    CarManager(string filepath) : storage(filepath)
    {
        cars = storage.loadData<Car>();
    }
    bool isIdExists(const string &id) const
    {
        return any_of(cars.begin(), cars.end(), [&id](const Car &car)
                      { return car.getid() == id; });
    }
    // Create a new car
void createNewCar(string make, string model, int year, float price, string color)

    {
        string ID = generate_uuid_v4();

        Car new_car(ID, make, model, year, price, color);
        cars.push_back(new_car);
        storage.writeData(cars);
    }

    // Retrieve a car by ID
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

    // Delete a car by ID
    void deleteCarById(const string &id)
    {
        auto it = remove_if(cars.begin(), cars.end(), [&id](const Car &car)
                            { return car.getid() == id; });
        if (it != cars.end())
        {
            cars.erase(it, cars.end());
            storage.writeData(cars);
            cout << "Car with ID " << id << " deleted successfully." << endl;
        }
        else
        {
            cout << "Car with ID " << id << " not found." << endl;
        }
    }

    // Update a car by ID
    void updateCarById(string id, string make, string model, int year, float price, string color)
    {
        auto it = find_if(cars.begin(), cars.end(), [&id](const Car &car)
                          { return car.getid() == id; });

        if (it != cars.end())
        {
            // Update the fields
            it->make = make;
            it->model = model;
            it->year = year;
            it->price = price;
            it->color = color;
            storage.writeData(cars);
        }
        else
        {
            cout << "Car with ID " << id << " not found." << endl;
        }
    }

    // Print all cars
    void getAllCars() const
    {
        cout << string(100, '-') << endl;
        cout << left << setw(10) << "ID"
             << setw(20) << "Make"
             << setw(15) << "Model"
             << setw(15) << "Year"
             << setw(10) << "Price"
             << setw(10) << "Color" << endl;
        cout << string(100, '-') << endl;

        for (const auto &car : cars)
        {
            cout << left << setw(10) << car.getid()
                 << setw(20) << car.make
                 << setw(15) << car.model
                 << setw(15) << car.year
                 << setw(10) << fixed << setprecision(2) << car.price
                 << setw(10) << car.color << endl;
            cout << string(100, '-') << endl;
        }
    }
};

#endif
