#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
using namespace std;

// 1. PERSON CLASS (Base Class)
// Using Inheritance here: Customer and Employee will use this data
class Person {
public:
    string name;
    int id;

    Person() : name(""), id(0) {}
    Person(string n, int i) : name(n), id(i) {}

    // Method to show basic person info
    void showPerson() const {
        cout << "ID: " << id << " | Name: " << name << endl;
    }
};

#endif
