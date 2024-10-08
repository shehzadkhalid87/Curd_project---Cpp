V3

Database Integration

1. A seperate class to handle database connection
   (Postgres or MySQL)
2. Create a seperate model -> user_mode.cpp
    // table name: users
   attributes:
     id
     first_name
     last_name
     email
     phone
     password
     books -> OneToMany(Book) -> [1,8, 10]
                          -> table -> user_books
                             // user_id: User
                             // book_id: Book
     created_at -> timestamp -> auto managed by database
     update_at -> timestamp
   1. Create new user
     -> sql queries
   2. Find all users
   3. Find one user
   4. update user
   5. delete user

3. Books Model
   table name: books
   -> atributes
   id
   title
   ...

/v3
  /src
    /models
      users_model.cpp
      books_model.cpp
      user_books_model.cpp
    
    /service
      user_service.cpp
      books_service.cpp

    /utils

    /cli
      user_cli_menue.cpp
      books_cli_menue.cpp
    
    /web
    