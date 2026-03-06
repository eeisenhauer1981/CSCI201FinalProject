#include <iostream>
#include <string>


#include "book.h"
#include "patron.h"
#include "library.h"
#include "transaction.h"

using namespace std;

int LibraryMenu ();
void GetTransactionInfo(int& patronID, string& title);

int main () {
    Library library;

    int choice;
    int patronID = 0;
    string bookTitle = "Not Assigned";

    choice = LibraryMenu();
    while (choice != 0) {
        if (choice == 1){
            try {
                library.loadBookData();
            }
            catch(runtime_error& excpt) {
                cout << excpt.what() << endl;
            }
        }
        else if (choice == 2){
            library.displayBooks();
        }
        else if (choice == 3){
            try{
                library.loadPatronData();
            }
            catch(runtime_error& excpt) {
                cout << excpt.what() << endl;
            }
        }
        else if (choice == 4){
            library.displayPatrons();
        }
        else if (choice == 5){
            //prompts user to enter patron ID and book title to pass to checkoutBook()
            GetTransactionInfo(patronID, bookTitle);
            
            try {
                library.checkoutBook(patronID, bookTitle);
            }
            catch(const std::exception& e) {
                std::cerr << "Error: " << e.what() << endl;
            }
        }
        else if (choice == 6){
            //prompts user to enter patron ID and book title to pass to returnBook()
            GetTransactionInfo(patronID, bookTitle);

            library.returnBook(patronID, bookTitle);
        }
        else if (choice == 7){
            library.displayTransactions();
        }
        else if (choice == 8){
            library.genreSearch();
        }
        else if (choice == 9){
            library.saveBooks();
        }
        else if (choice == 10){
            library.savePatrons();
        }

        choice = LibraryMenu();
    }

}

int LibraryMenu() {
    int choice;

    cout << "What would you like to do? Select from the following:" << endl;
    cout << "   1. Add books to the collection" << endl;
    cout << "   2. See a list of library books" << endl;
    cout << "   3. Add library patrons" << endl;
    cout << "   4. See a list of library patrons" << endl;
    cout << "   5. Checkout a book" << endl;
    cout << "   6. Return a book" << endl;
    cout << "   7. See a list of transactions" << endl;
    cout << "   8. Search for book by genre" << endl;
    cout << "   9. Save book list" << endl;
    cout << "   10. Save patron list" << endl;
    cout << "   0. Exit" << endl;
    cout << "Enter your selection: " << endl;
    cin >> choice;
    cout << endl;

    return choice;
}

void GetTransactionInfo(int &patronID, string &bookTitle) {
    cout << "Enter your ID: ";
    cin >> patronID;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter the book title: ";
    getline(cin, bookTitle);
    cout << endl;
}