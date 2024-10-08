#include "contact.cpp"
#include "cars.cpp"
#include "book.cpp"


int main() {
    // Contact Manager
    ContactManager contactManager("contacts.json");
    contactManager.createNewContact("durrah", "khan", "123456789", "durrah.khan@gmail.com", 30, "Male");
    contactManager.createNewContact("baloch","khan","8979098","baloch.khan@gmail.com",50,"male");
    contactManager.getAllContacts();
    string ids = "C002";
    contactManager.deleteContactbyId(ids);
    contactManager.getcontactbyId(ids);
    contactManager.updateContactById("C001","hamid","josh","90808","hamid.josh@gmail.com",45,"male");
    contactManager.getAllContacts();


    // Car Manager
    CarManager carManager("cars.json");
    carManager.createNewCar("BMW", "BMW", 2022, 50000.0, "X5", "Black");
    carManager.getAllCars();
    string id = "CAR1";
    string id2 = "CAR2";
    carManager.deleteCar(id);
    carManager.deleteCar(id2);
    carManager.deleteCar(id);
    carManager.getAllCars();
    

    // Book Manager
    BookManager bookManager("books.json");
    bookManager.createNewBook("Author A", "Book A", 2024, 25.99);
    bookManager.getAllBooks();

    return 0;
}
