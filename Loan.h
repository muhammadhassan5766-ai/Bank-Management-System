#ifndef LOAN_H
#define LOAN_H

#include <iostream>
#include <string>
using namespace std;

// 3. LOAN CLASS
// Stores loan details for customers
class Loan {
public:
    string customerName;
    double amount;
    double rate;

    Loan() : customerName(""), amount(0), rate(0) {}
    Loan(string n, double a, double r) : customerName(n), amount(a), rate(r) {}

    void showLoan() const {
        cout << "Customer: " << customerName << " | Loan: " << amount << " | Rate: " << rate << "%" << endl;
    }
};

#endif
