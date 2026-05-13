#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Person.h"
#include <iostream>
#include <string>
using namespace std;

// 7. CUSTOMER CLASS (Inherits Person)
// customer is person who use bank
// i inherit from person class so i dont have to rewrite name and id
// every customer have 2 accounts, one saving one current
class Customer : public Person {
public:
    string accNumbers[2]; // store account numbers, index 0 is SA, index 1 is CA
    int accCount;         // how many account linked so far

    Customer() : Person(), accCount(0) {}             // default empty customer
    Customer(string n, int i) : Person(n, i), accCount(0) {} // customer with name and id

    // link account number to this customer
    // maximum 2 account only (SA and CA)
    void addAccount(string acc) {
        if (accCount < 2) accNumbers[accCount++] = acc;
    }

    // print customer info and their account numbers
    void showCustomer() const {
        showPerson(); // call parent class function to show name and id
        cout << "Linked Accounts: ";
        for (int i = 0; i < accCount; i++) cout << accNumbers[i] << "  ";
        cout << endl;
    }
};

// 8. EMPLOYEE CLASS (Inherits Person)
// employee is bank worker, also inherit from person
// i made this class but not fully use it in main yet
// maybe in future i add login for employee also
class Employee : public Person {
public:
    string role; // what is job of employee
    Employee() : Person() {}
    Employee(string n, int i, string r) : Person(n, i), role(r) {}
};

#endif
