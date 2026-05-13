#ifndef BANK_H
#define BANK_H

#include "Branch.h"
#include <string>
using namespace std;

// 10. BANK CLASS (Top level composition)
class Bank {
public:
    string bankName;
    Branch* branch;
    Bank(string n, Branch* b) : bankName(n), branch(b) {}
};

#endif
