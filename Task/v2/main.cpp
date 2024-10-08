#include "main_menu.h"

int main()
{
    ContactManager contactManager("contacts.json");
    BookManager bookManager("books.json");
    CarManager carManager("cars.json");

    allMenu(contactManager, bookManager,carManager);
   
    return 0;
}
