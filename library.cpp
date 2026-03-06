#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "library.h"
#include "patron.h"
#include "book.h"
#include "transaction.h"

using namespace std;

//gets patron data from a file
void Library::loadPatronData() {
    //open patron file
    string fileName;
    cout << "Enter the file to open" << endl;
    cin >> fileName;
    ifstream patronFile;
    
    patronFile.open(fileName);
    if (!patronFile) {
        throw runtime_error("Could not open file");
    }

    //load data from patron file
    string inputString;
    while (getline(patronFile, inputString)){
        string name, idString;
        int id;
        stringstream patronInput(inputString);
        //parse data
        getline(patronInput, name, '\t');
        getline(patronInput, idString, '\t');
        id = stoi(idString);
        //create temporary Patron object
        Patron tempPatron(name, id);
        //check to see if patron already exists
        bool exists = false;
        for (const Patron& p : patrons) {
            if (p == tempPatron) {
                exists = true;
                break;
            }
        }
        if (exists) {
            tempPatron.displayPatron(cout);
            cout << "is already a library patron";
        }
        else {
            addPatron(tempPatron);
        }
    }
}

//adds a patron object to the library's list of patrons
void Library::addPatron(const Patron& p) {
    patrons.push_back(p);
}

//displays list of all library patrons
void Library::displayPatrons() const {
    cout << "Patrons:" << endl;
    for (const Patron& p : patrons) {
        cout << p << endl;
    }
}

//wrapper to call saveData for patrons
void Library::savePatrons() {
    string fileName;
    cout << "Enter name of file for saving patrons: " << endl;
    cin >> fileName;

    saveData(patrons, fileName);
}

//gets book data from a file
void Library::loadBookData() {
    //open book file
    string fileName;
    cout << "Enter the file to open" << endl;
    cin >> fileName;
    ifstream bookFile;

    bookFile.open(fileName);
    if (!bookFile) {
        throw runtime_error("Could not open file");
    }
    cout << "File open" << endl;
    //load data from book file
    string inputString;
    while (getline(bookFile, inputString)){
        string genre, title, author, type, sizeString;
        stringstream bookInput(inputString);
        //parse data
        getline(bookInput, genre, '\t');
        getline(bookInput, title, '\t');
        getline(bookInput, author, '\t');
        getline(bookInput, type, '\t');
        getline(bookInput, sizeString);

        //check to see if book exists
        Book tempBook (title, author, genre, type);
        bool exists = false;
        for (const Book *b : books) {
            if (*b == tempBook) {
                exists = true;
                break;
            }
        }
        if (exists) {
            cout << tempBook.getTitle();
            cout << " is already in the library collection" << endl;
        }

        else {        
            //determine if book is printed or eBook
            if (type == "print") {
                //set page count
                int size = stoi(sizeString);
                //create temporary printedBook and add to book list
                Book* b = new PrintedBook (title, author, genre, type, size);
                addBook(b);
            }
            else {
                //set file size
                double size = stod(sizeString);
                //create temporary EBook and add to book list
                Book* b = new EBook (title, author, genre, type, size);
                addBook(b);
            }
        }
    }
}

//adds a pointer to a book object to the library's list of books
void Library::addBook(Book* b) {
    books.push_back(b);
}

void Library::displayBooks() const {
    cout << "Library Books:" << endl;
    for (Book* b : books) {
        cout << *b << endl;
    }
}

//find/verify patron; find/verify book; calls functions to verify book status, change book status, add book to patron borrowed book list
void Library::checkoutBook(int patronId, std::string title) {
    Patron* foundPatron = nullptr;  //to be passed to Patron::borrowBook() function
    Book* foundBook = nullptr;      //to be passed to Book::setStatus()function

    //looks through patron list for matching ID
    //assigns foundPatron with found patron
    for (Patron& p : patrons) {
        if (patronId == p.getID()) {
            foundPatron = &p;
            break;
        }
    }

    //looks through book list for matching title
    //assigns foundBook with found Book
    for (Book* b : books) {
        if (title == b->getTitle()) {
            foundBook = b;
            break;
        }
    }

    //checks if book and patron exist; if so, checks if book is available
    //if book is available, status is changed to checked out and borrowBook() is called
    if (foundBook && foundPatron) {
        if (foundBook->getStatus() == "Available") {
            foundBook->setStatus(Book::BookStatus::CheckedOut);
            foundPatron->borrowBook(foundBook);
            
            //logs transaction
            Transaction tempTransaction (patronId, title, "Check Out");
            transactions.push_back(tempTransaction);
        }
        else {
            throw logic_error("Book is unavailable for Check Out");
        }
    }
    else {
        throw logic_error("Book or patron not found");
    }
}

//checks if book and patron exist; if so, checks if book is checked out. if book is checked out, status is changed to available and Patron::returnBook() is called
void Library::returnBook(int patronId, std::string title) {
    Patron* foundPatron = nullptr;  //to be passed to Patron::returnBook() function
    Book* foundBook = nullptr;      //to be passed to Book::setStatus()function

    //looks through patron list for matching ID
    //assigns foundPatron with found patron
    for (Patron& p : patrons) {
        if (patronId == p.getID()) {
            foundPatron = &p;
            break;
        }
    }

    //looks through book list for matching title
    //assigns foundBook with found Book
    for (Book* b : books) {
        if (title == b->getTitle()) {
            foundBook = b;
            break;
        }
    }

    //if book and patron exist, checks if book is checked out
    //if book is checked out, status is changed to available and Patron::returnBook() is called
    if (foundBook && foundPatron) {
        if (foundBook->getStatus() == "Checked Out") {
            foundBook->setStatus(Book::BookStatus::Available);
            foundPatron->returnBook(foundBook);

            //logs return transaction
            Transaction tempTransaction (patronId, title, "Return");
            transactions.push_back(tempTransaction);
        }
        else {
            throw logic_error("Book has already been returned");
        }        
    }
    else {
        throw logic_error("Book or patron not found");
    }
}

//searches for books by genre
void Library::genreSearch() {
    string searchGenre;
    vector<Book*> booksByGenre;     //holds all books that match genre

    cout << "Enter a genre to search. Select from: Fiction, NonFiction, Mystery, Science, or Biography" << endl;
    cin >> searchGenre;

    //loops through list of library books and adds any with search genre to booksByGenre list
    for (Book* b : books) {
        if (searchGenre == b->getGenre()) {
            Book* bg = b;
            booksByGenre.push_back(bg);
        }
    }

    //outputs list of books that match search genre
    cout << "These books match your search terms:" << endl;
    for (Book* bg : booksByGenre) {
        cout << *bg << endl;
    }
}

//wrapper to call saveData for books
void Library::saveBooks() {
    string fileName;
    cout << "Enter name of file for saving books: " << endl;
    cin >> fileName;

    saveData(books, fileName);
}

//outputs transaction log
void Library::displayTransactions() const{
    cout << "Library Transactions" << endl;
    for (int i = 0; i < transactions.size(); ++i) {
        transactions.at(i).displayTransaction();
    }
}
