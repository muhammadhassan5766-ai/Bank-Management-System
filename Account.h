#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string>
using namespace std;

// 4. ACCOUNT CLASS (Abstract Class)
// this class is abstract, means we cannot make object directly from it
// i use pure virtual function to make it abstract
// savings and current account class will inherit from this
// teacher told us abstract class is important in OOP so i implement it
class Account {
public:
    string accNo;
    double balance;
    static int totalAccounts; // static variable, it count all accounts in whole program not just one object

    Account(string a, double b) : accNo(a), balance(b) {
        totalAccounts++; // every time new account made, increase counter
    }

    // deposit function, add money to balance
    void deposit(double amt) {
        balance += amt;
        cout << "Deposit Successful. Balance: " << balance << endl;
    }

    // pure virtual function - this make class abstract
    // i learn this is called runtime polymorphism, very important topic
    virtual void withdraw(double amt) = 0;
    virtual void showAccount() const = 0;
    virtual ~Account() {} // virtual destructor so memory delete properly when we use pointer
};

// 5. SAVINGS ACCOUNT CLASS (Inherits Account)
// savings account have interest rate feature
// withdraw only allowed if enough balance, no overdraft here
class SavingsAccount : public Account {
public:
    double interest; // interest rate for saving

    SavingsAccount(string a, double b, double r) : Account(a, b), interest(r) {}

    // override withdraw for savings rule (cannot go below zero)
    void withdraw(double amt) override {
        if (amt <= balance) {
            balance -= amt;
            cout << "Withdrawal from Savings Successful.\n";
        } else cout << "Insufficient Savings Balance!\n"; // not enough money
    }

    // show savings account details
    void showAccount() const override {
        cout << "[Savings] Acc: " << accNo << " | Bal: " << balance << " | Interest: " << interest << "%" << endl;
    }
};

// 6. CURRENT ACCOUNT CLASS (Inherits Account)
// current account is different, it have overdraft limit
// overdraft mean you can take out more then balance, up to limit
class CurrentAccount : public Account {
public:
    double overdraft; // extra limit allowed for current account

    CurrentAccount(string a, double b, double o) : Account(a, b), overdraft(o) {}

    // withdraw logic for current account include overdraft check
    void withdraw(double amt) override {
        if (amt <= balance + overdraft) {
            balance -= amt;
            cout << "Withdrawal from Current Successful.\n";
        } else cout << "Overdraft limit exceeded!\n"; // exceed both balance and overdraft
    }

    // show current account info
    void showAccount() const override {
        cout << "[Current] Acc: " << accNo << " | Bal: " << balance << " | Overdraft: " << overdraft << endl;
    }
};

#endif
