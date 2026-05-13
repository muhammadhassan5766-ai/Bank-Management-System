#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
#include <string>
using namespace std;

// 2. TRANSACTION CLASS
// Stores details of every deposit or withdrawal
class Transaction {
public:
    string accNo;
    string type;
    double amount;

    Transaction() : accNo(""), type(""), amount(0) {}
    Transaction(string a, string t, double am) : accNo(a), type(t), amount(am) {}

    void showTransaction() const {
        cout << "[" << type << "] Acc: " << accNo << " | Amount: " << amount << endl;
    }
};

#endif
