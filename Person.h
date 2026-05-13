#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
using namespace std;

// 1. PERSON CLASS (Base Class)
// this is base class i made it first
// customer and employee both will use name and id from here
// i learn inheritance from youtube it is very useful concept
class Person {
public:
    string name;
    int id;

    Person() : name(""), id(0) {} // default constructor, set empty values
    Person(string n, int i) : name(n), id(i) {} // this constructor take name and id

    // this function just print the person info on screen
    void showPerson() const {
        cout << "ID: " << id << " | Name: " << name << endl;
    }
};

#endif
