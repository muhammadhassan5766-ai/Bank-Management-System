#ifndef LOAN_H
#define LOAN_H

#include <iostream>
#include <string>
using namespace std;

// 3. LOAN CLASS
// this class store loan information for customer
// bank give loan so i need to save who take loan and how much
// rate is interest rate, teacher told us to include it
class Loan {
public:
    string customerName; // name of person who take loan
    double amount;       // total loan amount
    double rate;         // interest rate in percent

    Loan() : customerName(""), amount(0), rate(0) {} // default empty loan
    Loan(string n, double a, double r) : customerName(n), amount(a), rate(r) {} // loan with all details

    // show loan info, i use this in showAll function in branch
    void showLoan() const {
        cout << "Customer: " << customerName << " | Loan: " << amount << " | Rate: " << rate << "%" << endl;
    }
};

#endif
