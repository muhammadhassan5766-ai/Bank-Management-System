#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
#include <string>
using namespace std;

// 2. TRANSACTION CLASS
// this class is for saving transaction history
// every time deposit or withdraw happen i store it here
// teacher said always keep record of transactions so i made this
class Transaction {
public:
    string accNo;  // which account did transaction
    string type;   // deposit or withdraw
    double amount; // how much money

    Transaction() : accNo(""), type(""), amount(0) {} // empty transaction
    Transaction(string a, string t, double am) : accNo(a), type(t), amount(am) {} // real transaction

    // print the transaction detail
    void showTransaction() const {
        cout << "[" << type << "] Acc: " << accNo << " | Amount: " << amount << endl;
    }
};

#endif
