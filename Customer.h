#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Person.h"
#include <iostream>
#include <string>
using namespace std;

// 7. CUSTOMER CLASS (Inherits Person)
class Customer : public Person {
public:
    string accNumbers[2]; // Index 0 for SA, Index 1 for CA
    int accCount;

    Customer() : Person(), accCount(0) {}
    Customer(string n, int i) : Person(n, i), accCount(0) {}

    void addAccount(string acc) {
        if (accCount < 2) accNumbers[accCount++] = acc;
    }

    void showCustomer() const {
        showPerson();
        cout << "Linked Accounts: ";
        for (int i = 0; i < accCount; i++) cout << accNumbers[i] << "  ";
        cout << endl;
    }
};

// 8. EMPLOYEE CLASS (Inherits Person)
class Employee : public Person {
public:
    string role;
    Employee() : Person() {}
    Employee(string n, int i, string r) : Person(n, i), role(r) {}
};

#endif
