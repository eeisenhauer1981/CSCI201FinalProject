#ifndef library_H
#define library_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "patron.h"
#include "book.h"
#include "transaction.h"

class Library {
    //list of all library patrons; includes name and ID
    std::vector<Patron> patrons;

    //list of all library books; includes title, author, genre, size, and availability status
    std::vector<Book*> books;

    //list of all check outs and returns
    std::vector<Transaction> transactions;

public:
    //--PATRON TASKS--
    //gets patron data from a file
    void loadPatronData();
    //adds a patron object to the library's list of patrons
    void addPatron(const Patron& p);
    //outputs entire list of library patrons
    void displayPatrons() const;
    //wrapper to call saveData for patrons
    void savePatrons();

    //--BOOK TASKS--
    //gets book data from a file
    void loadBookData();
    //adds a pointer to a book object to the library's list of books
    void addBook(Book* b);
    //outputs entire list of library books
    void displayBooks() const;
    //find/verify patron; find/verify book, then calls functions to verify book status, change book status, add book to patron borrowed book list
    void checkoutBook(int patronId, std::string title);
    //find/verify patron; find/verify book, then calls functions to verify book status, change book status, remove book from patron borrowed book list
    void returnBook(int patronId, std::string title);
    //search for book by genre. user selects genre from list; returns all books with selected genre
    void genreSearch();
    //wrapper to call saveData for books
    void saveBooks();

    //--TASKS--
    //outputs transaction log
    void displayTransactions() const;
    //save books or patrons to file
    //helper functions for pointers vs objects
    template<typename T>
    void printItem(std::ostream& os, const T& item) {
        os << item;
    }

    template<typename T>
    void printItem(std::ostream& os, T* item) {
    os << *item;
    }

    //save template
    template<typename T>
    void saveData(const std::vector<T>& items, const std::string& fileName) {

        std::ofstream outputFile;
        outputFile.exceptions(std::ofstream::failbit);

        try {
            outputFile.open(fileName);

            for (const T& item : items){
                printItem(outputFile, item);
                outputFile << endl;
            }

         outputFile.close();
        }
        catch (ios_base::failure& excpt) {
            cout << "Failed to save to file: " << excpt.what() << endl;
        }
    }
};


#endif