#ifndef BANK_H
#define BANK_H

#include "Branch.h"
#include <string>
using namespace std;

// 10. BANK CLASS (Top level composition)
// bank is highest level class in my project
// it contain branch inside it, this is composition concept
// i learn composition mean "has-a" relationship (bank HAS branch)
class Bank {
public:
    string bankName;
    Branch* branch; // pointer to branch, bank own the branch

    // constructor take bank name and pointer to branch
    Bank(string n, Branch* b) : bankName(n), branch(b) {}
};

#endif
