#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "patron.h"
#include "book.h"

using namespace std;

Patron::Patron() {
    name = "Unknown";
    id = 0;
}

Patron::Patron(string n, int i) {
    name = n;
    id = i;
}

//called in Library::checkoutBook; adds checked out book to patrons borrowedBooks list
void Patron::borrowBook(Book* b) {
    borrowedBooks.push_back(b);
}

//called in Library::returnBook; removes returned book from patrons borrowedBooks list
void Patron::returnBook(Book* b) {
    borrowedBooks.erase(find(borrowedBooks.begin(), borrowedBooks.end(), b));
}

//outputs patron name, ID, and borrowedBooks list
void Patron::displayPatron(ostream& os) const {
    os << id << "\t"
    << name << "\t";
    for (Book* b : borrowedBooks){
        os << *b << endl;
    }
}

//compares new patron input from file to existing patron list
bool Patron::operator==(const Patron& other) const {
    return (name == other.name && id == other.id);
}

ostream& operator<<(std::ostream& os, const Patron& p) {
    p.displayPatron(os);
    return os;
}

int Patron::getID() const {
    return id;
}

std::string Patron::getName() const {
    return name;
}