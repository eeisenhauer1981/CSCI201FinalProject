#ifndef patron_h
#define patron_h

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "book.h"

class Patron {
    std::string name;
    int id;
    std::vector<Book*> borrowedBooks;
public:
    //--CONSTRUCTORS--
    Patron();
    Patron(std::string n, int i);
    //--TASKS--
    //called in Library::checkoutBook; adds checked out book to patrons borrowedBooks list
    void borrowBook(Book* b);
    //called in Library::returnBook; removes returned book from patrons borrowedBooks list
    void returnBook(Book* b);
    //outputs patron name, ID, and borrowedBooks list
    void displayPatron(std::ostream& os) const;
    //compares new patron input from file to existing patron list
    bool operator==(const Patron& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Patron& p);
    //--GETTERS--
    int getID() const;
    std::string getName() const;
};


#endif