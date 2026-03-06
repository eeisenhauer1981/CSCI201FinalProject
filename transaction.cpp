#include <iostream>
#include <string>
#include <ctime>

#include "transaction.h"

using namespace std;

Transaction::Transaction(int pid, string bt, string t) {
    time_t dateTime;
    time(&dateTime);
    patronId = pid;
    bookTitle = bt;
    transactionDate = ctime(&dateTime);
    transactionType = t;
}

void Transaction::displayTransaction() const{
    cout << "Patron: " << patronId << endl;
    cout << "Book: " << bookTitle << endl;
    cout << "Date: " << transactionDate << endl;
    cout << "Transaction Type: " << transactionType << endl;
}