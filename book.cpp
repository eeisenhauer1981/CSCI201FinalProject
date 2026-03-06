#include <iostream>
#include <string>

#include "book.h"

using namespace std;

//Book definitions
Book::Book() {
    title = "Unknown";
    author = "Unknown";
    genre = Genre::Undefined;
    status = BookStatus::Available;
}

Book::Book(string t, string a, string g, string tp) {
    title = t;
    author = a;
    genre = setGenre(g);
    type = tp;
    status = BookStatus::Available;
}

//this function takes a string variable from file and converts to Genre to set book object genre
Book::Genre Book::setGenre(string g) {
    if (g == "Fiction"){
        return Genre::Fiction;
    }
    else if (g == "NonFiction"){
        return Genre::NonFiction;
    }
    else if (g == "Mystery"){
        return Genre::Mystery;
    }
    else if (g == "Science"){
        return Genre::Science;
    }
    else if (g == "Biography"){
        return Genre::Biography;
    }
    else {
        return Genre::Undefined;
    }
}

void Book::setStatus(BookStatus s) {
    status = s;
}

//converts Genre genre to a string for output in displayInfo()
string Book::getGenre() const {
    if (genre == Genre::Fiction) {
        return "Fiction";
    }
    else if (genre == Genre::NonFiction){
        return "NonFiction";
    }
    else if (genre == Genre::Mystery){
        return "Mystery";
    }
    else if (genre == Genre::Science){
        return "Science";
    }
    else if (genre == Genre::Biography){
        return "Biography";
    }
    else {
        return "Undefined";
    }
}

//converts BookStatus status to a string for output in displayInfo()
string Book::getStatus() const {
    if (status == BookStatus::Available) {
        return "Available";
    }
    else if (status == BookStatus::CheckedOut) {
        return "Checked Out";
    }
    else {
        return "Unavailable";
    }
}

string Book::getTitle() const {
    return title;
}

string Book::getAuthor() const {
    return author;
}
    
void Book::displayInfo(ostream& os) const {
    os << title << "\t"
       << author << "\t"
       << getGenre() << "\t"
       << getStatus() << "\t"
       << type << "\t";
}

bool Book::operator==(const Book& other) const {
    return (title == other.title && author == other.author && type == other.type);
}

ostream& operator<<(std::ostream& os, const Book& b) {
    b.displayInfo(os);
    return os;
}

//eBook definitions
EBook::EBook(string t, string a, string g, string tp, double size) 
    : Book(t, a, g, tp),
    fileSizeMB(size){}

void EBook::displayInfo(std::ostream& os) const {
    Book::displayInfo(os);
    os << fileSizeMB << "\t";
}

//PrintedBook definitions
PrintedBook::PrintedBook(string t, string a, string g, string tp, int pages) 
    : Book(t, a, g, tp),
    pageCount(pages){}

void PrintedBook::displayInfo(std::ostream& os) const {
    Book::displayInfo(os);
    os << pageCount << "\t";
}