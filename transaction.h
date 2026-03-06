#ifndef transaction_H
#define transaction_H

#include <iostream>
#include <string>
#include <ctime>

class Transaction {
    int patronId;
    std::string bookTitle;
    std::string transactionDate;
    std::string transactionType;
public:
    Transaction(int pid, std::string bt, std::string t);
    void displayTransaction() const;

};

#endif