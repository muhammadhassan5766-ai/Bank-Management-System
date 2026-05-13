#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string>
using namespace std;

// 4. ACCOUNT CLASS (Abstract Class)
// We cannot create objects of this class because it's a template for SA and CA
class Account {
public:
    string accNo;
    double balance;
    static int totalAccounts; // Static member to count all accounts

    Account(string a, double b) : accNo(a), balance(b) {
        totalAccounts++;
    }

    void deposit(double amt) {
        balance += amt;
        cout << "Deposit Successful. Balance: " << balance << endl;
    }

    // Pure Virtual Function: Makes this class Abstract
    virtual void withdraw(double amt) = 0;
    virtual void showAccount() const = 0;
    virtual ~Account() {} // Virtual Destructor for safe memory cleanup
};

// 5. SAVINGS ACCOUNT CLASS (Inherits Account)
class SavingsAccount : public Account {
public:
    double interest;
    SavingsAccount(string a, double b, double r) : Account(a, b), interest(r) {}

    // Overriding withdraw function for Savings logic
    void withdraw(double amt) override {
        if (amt <= balance) {
            balance -= amt;
            cout << "Withdrawal from Savings Successful.\n";
        } else cout << "Insufficient Savings Balance!\n";
    }

    void showAccount() const override {
        cout << "[Savings] Acc: " << accNo << " | Bal: " << balance << " | Interest: " << interest << "%" << endl;
    }
};

// 6. CURRENT ACCOUNT CLASS (Inherits Account)
class CurrentAccount : public Account {
public:
    double overdraft; // Extra limit for Current account
    CurrentAccount(string a, double b, double o) : Account(a, b), overdraft(o) {}

    void withdraw(double amt) override {
        if (amt <= balance + overdraft) {
            balance -= amt;
            cout << "Withdrawal from Current Successful.\n";
        } else cout << "Overdraft limit exceeded!\n";
    }

    void showAccount() const override {
        cout << "[Current] Acc: " << accNo << " | Bal: " << balance << " | Overdraft: " << overdraft << endl;
    }
};

#endif
