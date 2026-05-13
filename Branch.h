#ifndef BRANCH_H
#define BRANCH_H

#include "Customer.h"
#include "Account.h"
#include "Transaction.h"
#include "Loan.h"
#include <fstream>
#include <string>
using namespace std;

// Array size limit for our bank database
const int MAX_LIMIT = 50;

// 9. BRANCH CLASS (The main management engine)
// Uses Composition: Branch has Customers, Accounts, Loans, and Transactions
class Branch {
public:
    string branchName;
    Customer customers[MAX_LIMIT];
    Account* accounts[MAX_LIMIT * 2]; // Using Pointers for Dynamic Memory Allocation
    Transaction transactions[MAX_LIMIT * 2];
    Loan loans[MAX_LIMIT];

    int custIdx, accIdx, transIdx, loanIdx;
    static int nextAutoID; // To generate IDs starting from 1001

    Branch(string n) : branchName(n), custIdx(0), accIdx(0), transIdx(0), loanIdx(0) {}

    // --- FILE HANDLING: SAVING DATA ---
    // This saves all bank info to a text file so data is not lost
    void saveToFile() {
        ofstream outFile("bank_data.txt");
        if (outFile.is_open()) {
            outFile << custIdx << " " << accIdx << " " << loanIdx << " " << nextAutoID << endl;
            // Saving Customers
            for (int i = 0; i < custIdx; i++) {
                outFile << customers[i].id << " " << customers[i].name << endl;
            }
            // Saving Accounts
            for (int i = 0; i < accIdx; i++) {
                outFile << accounts[i]->accNo << " " << accounts[i]->balance << endl;
            }
            // Saving Loans
            for (int i = 0; i < loanIdx; i++) {
                outFile << loans[i].customerName << " " << loans[i].amount << " " << loans[i].rate << endl;
            }
            outFile.close();
        }
    }

    // --- FILE HANDLING: LOADING DATA ---
    // Loads previous bank data when the program starts
    void loadFromFile() {
        ifstream inFile("bank_data.txt");
        if (!inFile.is_open()) return;

        int cI, aI, lI, nID;
        if (!(inFile >> cI >> aI >> lI >> nID)) return;
        nextAutoID = nID;

        // Reading Customers from file
        for (int i = 0; i < cI; i++) {
            int id; string name;
            inFile >> id; getline(inFile >> ws, name);
            customers[custIdx++] = Customer(name, id);
        }
        // Reading Accounts and Re-allocating Dynamic Memory
        for (int i = 0; i < aI; i++) {
            string accNo; double bal;
            inFile >> accNo >> bal;
            if (accNo.substr(0, 2) == "SA")
                accounts[accIdx++] = new SavingsAccount(accNo, bal, 5.0);
            else
                accounts[accIdx++] = new CurrentAccount(accNo, bal, 5000.0);

            // Linking loaded accounts back to customers
            int ownerID = stoi(accNo.substr(3));
            for (int j = 0; j < custIdx; j++) {
                if (customers[j].id == ownerID) customers[j].addAccount(accNo);
            }
        }
        // Reading Loans from file
        for (int i = 0; i < lI; i++) {
            string name; double amt, rt;
            inFile >> name >> amt >> rt;
            loans[loanIdx++] = Loan(name, amt, rt);
        }
        inFile.close();
    }

    // Function for Employee to create new customer
    void createCustomerRecord(string name) {
        if (custIdx < MAX_LIMIT) {
            int id = nextAutoID++;
            customers[custIdx] = Customer(name, id);
            string saID = "SA-" + to_string(id);
            string caID = "CA-" + to_string(id);

            customers[custIdx].addAccount(saID);
            customers[custIdx].addAccount(caID);

            // Using Dynamic Memory (DMA) for polymorphism
            accounts[accIdx++] = new SavingsAccount(saID, 0.0, 5.0);
            accounts[accIdx++] = new CurrentAccount(caID, 0.0, 5000.0);

            cout << "Customer added. ID: " << id << endl;
            custIdx++;
            saveToFile(); // Auto-save after creation
        }
    }

    // Function for Employee to delete a record
    void deleteCustomerRecord(int id) {
        int foundIdx = -1;
        for (int i = 0; i < custIdx; i++) {
            if (customers[i].id == id) { foundIdx = i; break; }
        }

        if (foundIdx == -1) {
            cout << "ID not found!\n";
            return;
        }

        // Deleting Dynamic Memory objects from heap
        string saID = "SA-" + to_string(id);
        string caID = "CA-" + to_string(id);
        for (int i = 0; i < accIdx; i++) {
            if (accounts[i]->accNo == saID || accounts[i]->accNo == caID) {
                delete accounts[i]; // Free memory
                for (int j = i; j < accIdx - 1; j++) { accounts[j] = accounts[j + 1]; }
                accIdx--; i--;
            }
        }
        // Removing customer from array and shifting others
        for (int i = foundIdx; i < custIdx - 1; i++) { customers[i] = customers[i + 1]; }
        custIdx--;

        cout << "Record deleted successfully.\n";
        saveToFile(); // Auto-save after deletion
    }

    // Function to add loan only for existing customers
    void addLoan() {
        int id;
        cout << "Enter Customer ID for Loan: "; cin >> id;
        int foundIdx = -1;
        for (int i = 0; i < custIdx; i++) { if (customers[i].id == id) { foundIdx = i; break; } }

        if (foundIdx == -1) {
            cout << "Account Not Found! Only customers can get a loan.\n";
            return;
        }

        double amt, rate;
        cout << "Amount: "; cin >> amt;
        cout << "Rate: "; cin >> rate;
        loans[loanIdx++] = Loan(customers[foundIdx].name, amt, rate);
        cout << "Loan approved for " << customers[foundIdx].name << endl;
        saveToFile();
    }

    // Handles both Deposit and Withdraw logic
    void performTransaction(string acc, double amt, bool isDeposit) {
        for (int i = 0; i < accIdx; i++) {
            if (accounts[i]->accNo == acc) {
                if (isDeposit) accounts[i]->deposit(amt);
                else accounts[i]->withdraw(amt);
                transactions[transIdx++] = Transaction(acc, (isDeposit ? "Deposit" : "Withdraw"), amt);
                saveToFile();
                return;
            }
        }
        cout << "Account not found!\n";
    }

    void showAll() const {
        cout << "\n========== " << branchName << " RECORDS ==========\n";
        for (int i = 0; i < custIdx; i++) { customers[i].showCustomer(); }
        cout << "\n--- ALL LOANS ---\n";
        for (int i = 0; i < loanIdx; i++) { loans[i].showLoan(); }
    }

    // Cleanup memory when program closes
    ~Branch() {
        for (int i = 0; i < accIdx; i++) delete accounts[i];
    }
};

#endif
