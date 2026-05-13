#ifndef BRANCH_H
#define BRANCH_H

#include "Customer.h"
#include "Account.h"
#include "Transaction.h"
#include "Loan.h"
#include <fstream>
#include <string>
using namespace std;

// array size limit for storing data in branch
// i use fixed size array because dynamic array is more complex
const int MAX_LIMIT = 50;

// 9. BRANCH CLASS (The main management engine)
// this is most important class in my project
// branch manage customer, account, loan and transaction together
// i use composition here: branch HAS customers, accounts, loans, transactions
class Branch {
public:
    string branchName;
    Customer customers[MAX_LIMIT];           // array of all customers
    Account* accounts[MAX_LIMIT * 2];        // pointer array for dynamic memory (polymorphism need pointer)
    Transaction transactions[MAX_LIMIT * 2]; // store all transactions history
    Loan loans[MAX_LIMIT];                   // store all loans

    // index variables to track how many items stored in each array
    int custIdx, accIdx, transIdx, loanIdx;
    static int nextAutoID; // auto generate ID starting from 1001 for all customers

    // constructor, set branch name and all index to zero
    Branch(string n) : branchName(n), custIdx(0), accIdx(0), transIdx(0), loanIdx(0) {}

    // --- FILE HANDLING: SAVING DATA ---
    // this function save all data to text file
    // i add file handling so data not lost when program close
    // without this everything reset every time, teacher want persistent data
    void saveToFile() {
        ofstream outFile("bank_data.txt");
        if (outFile.is_open()) {
            // first line save count of each type and next id value
            outFile << custIdx << " " << accIdx << " " << loanIdx << " " << nextAutoID << endl;

            // saving all customers one by one
            for (int i = 0; i < custIdx; i++) {
                outFile << customers[i].id << " " << customers[i].name << endl;
            }
            // saving all accounts, only accNo and balance needed
            for (int i = 0; i < accIdx; i++) {
                outFile << accounts[i]->accNo << " " << accounts[i]->balance << endl;
            }
            // saving all loans data
            for (int i = 0; i < loanIdx; i++) {
                outFile << loans[i].customerName << " " << loans[i].amount << " " << loans[i].rate << endl;
            }
            outFile.close();
        }
    }

    // --- FILE HANDLING: LOADING DATA ---
    // this function load data from file when program start
    // it re-create all objects from saved text
    // i spend lot of time on this part because re-linking account to customer was tricky
    void loadFromFile() {
        ifstream inFile("bank_data.txt");
        if (!inFile.is_open()) return; // if file not exist just skip, first time running

        int cI, aI, lI, nID;
        if (!(inFile >> cI >> aI >> lI >> nID)) return; // read counts from first line
        nextAutoID = nID; // restore id counter so new ids don't duplicate

        // load customers from file
        for (int i = 0; i < cI; i++) {
            int id; string name;
            inFile >> id; getline(inFile >> ws, name);
            customers[custIdx++] = Customer(name, id);
        }

        // load accounts from file and re-create with new keyword
        // i check first 2 letters to know if SA (savings) or CA (current)
        for (int i = 0; i < aI; i++) {
            string accNo; double bal;
            inFile >> accNo >> bal;
            if (accNo.substr(0, 2) == "SA")
                accounts[accIdx++] = new SavingsAccount(accNo, bal, 5.0);
            else
                accounts[accIdx++] = new CurrentAccount(accNo, bal, 5000.0);

            // now link account back to its owner customer using id in account number
            int ownerID = stoi(accNo.substr(3)); // extract id from "SA-1001" -> get 1001
            for (int j = 0; j < custIdx; j++) {
                if (customers[j].id == ownerID) customers[j].addAccount(accNo);
            }
        }

        // load loans from file
        for (int i = 0; i < lI; i++) {
            string name; double amt, rt;
            inFile >> name >> amt >> rt;
            loans[loanIdx++] = Loan(name, amt, rt);
        }
        inFile.close();
    }

    // employee use this function to add new customer to bank
    // automatically create both SA and CA account for customer
    void createCustomerRecord(string name) {
        if (custIdx < MAX_LIMIT) {
            int id = nextAutoID++; // assign new id and increment for next use
            customers[custIdx] = Customer(name, id);

            // create account number using prefix + id
            string saID = "SA-" + to_string(id);
            string caID = "CA-" + to_string(id);

            customers[custIdx].addAccount(saID);
            customers[custIdx].addAccount(caID);

            // use new keyword for dynamic memory, needed for virtual function (polymorphism)
            accounts[accIdx++] = new SavingsAccount(saID, 0.0, 5.0);
            accounts[accIdx++] = new CurrentAccount(caID, 0.0, 5000.0);

            cout << "Customer added. ID: " << id << endl;
            custIdx++;
            saveToFile(); // save right away so data not lost
        }
    }

    // employee use this to delete customer and their accounts
    // i also free memory with delete keyword so no memory leak
    void deleteCustomerRecord(int id) {
        int foundIdx = -1;
        for (int i = 0; i < custIdx; i++) {
            if (customers[i].id == id) { foundIdx = i; break; }
        }

        if (foundIdx == -1) {
            cout << "ID not found!\n";
            return;
        }

        // delete both accounts of this customer from heap memory
        string saID = "SA-" + to_string(id);
        string caID = "CA-" + to_string(id);
        for (int i = 0; i < accIdx; i++) {
            if (accounts[i]->accNo == saID || accounts[i]->accNo == caID) {
                delete accounts[i]; // free heap memory to avoid memory leak
                // shift remaining accounts left to fill empty space
                for (int j = i; j < accIdx - 1; j++) { accounts[j] = accounts[j + 1]; }
                accIdx--; i--;
            }
        }

        // shift customers array left after removing deleted customer
        for (int i = foundIdx; i < custIdx - 1; i++) { customers[i] = customers[i + 1]; }
        custIdx--;

        cout << "Record deleted successfully.\n";
        saveToFile(); // save again after deletion
    }

    // add loan for existing customer only, new person cannot get loan
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

    // handle deposit and withdraw both in one function
    // isDeposit=true mean deposit, isDeposit=false mean withdraw
    void performTransaction(string acc, double amt, bool isDeposit) {
        for (int i = 0; i < accIdx; i++) {
            if (accounts[i]->accNo == acc) {
                // call virtual function, C++ decide at runtime which class withdraw to call
                if (isDeposit) accounts[i]->deposit(amt);
                else accounts[i]->withdraw(amt);
                transactions[transIdx++] = Transaction(acc, (isDeposit ? "Deposit" : "Withdraw"), amt);
                saveToFile();
                return;
            }
        }
        cout << "Account not found!\n"; // if account number wrong
    }

    // show all customers and loans, employee use this to view records
    void showAll() const {
        cout << "\n========== " << branchName << " RECORDS ==========\n";
        for (int i = 0; i < custIdx; i++) { customers[i].showCustomer(); }
        cout << "\n--- ALL LOANS ---\n";
        for (int i = 0; i < loanIdx; i++) { loans[i].showLoan(); }
    }

    // destructor to free all dynamic memory when branch object destroyed
    // this is important to prevent memory leak, teacher mark us on this
    ~Branch() {
        for (int i = 0; i < accIdx; i++) delete accounts[i];
    }
};

#endif
