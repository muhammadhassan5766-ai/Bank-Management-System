#include <iostream>
#include "Bank.h"
using namespace std;

// static member must define outside class in .cpp file, cannot define in header
// i get error before because i put it inside header, teacher help me fix
int Account::totalAccounts = 0;
int Branch::nextAutoID = 1001; // id start from 1001, look more professional

// ---------------- MAIN PROGRAM ----------------
// this is main function where everything run
// i made two portal: employee portal and customer portal
int main() {
    // create branch object with name
    Branch b("Blue Area Islamabad Branch");
    b.loadFromFile(); // load saved data when program start, so old data come back

    // create bank object and give it the branch
    Bank myBank("Bahria Bank", &b);

    int mainChoice;
    while (true) {
        system("cls"); // clear screen before showing menu, look cleaner
        cout << "\n===== " << myBank.bankName << " MANAGEMENT SYSTEM =====\n";
        cout << "1. Employee Portal (Admin)\n2. Customer Portal (User)\n3. Exit\nChoice: ";
        cin >> mainChoice;

        if (mainChoice == 1) { // EMPLOYEE LOGIC
            int empChoice;
            while (true) {
                system("cls"); // clear screen before employee menu
                cout << "\n-- EMPLOYEE MENU --\n1. Add Customer\n2. Add Loan\n3. View Records\n4. Delete Account\n5. Logout\nChoice: ";
                cin >> empChoice;

                if (empChoice == 1) {
                    // get customer name and create record
                    string n; cout << "Customer Name: "; cin.ignore(); getline(cin, n);
                    b.createCustomerRecord(n);
                } else if (empChoice == 2) b.addLoan();
                else if (empChoice == 3) b.showAll();
                else if (empChoice == 4) {
                    int id; cout << "Enter ID to delete: "; cin >> id;
                    b.deleteCustomerRecord(id);
                } else break; // logout from employee portal

                // pause so user can read output before screen clear again
                cout << "\nPress Enter to continue...";
                cin.ignore(); cin.get();
            }
        }
        else if (mainChoice == 2) { // CUSTOMER LOGIC
            system("cls");
            int id; cout << "Enter your ID to login: "; cin >> id;
            bool found = false;

            // search customer by id in array
            for (int i = 0; i < b.custIdx; i++) {
                if (b.customers[i].id == id) {
                    found = true;
                    int cChoice;
                    while (true) {
                        system("cls"); // clear screen before customer menu
                        cout << "\n-- Welcome " << b.customers[i].name << " --\n";
                        cout << "1. Deposit\n2. Withdraw\n3. Check Balance\n4. Logout\nChoice: ";
                        cin >> cChoice;

                        if (cChoice == 1 || cChoice == 2) {
                            // get account number and amount for transaction
                            string acc; double amt;
                            cout << "Account No (SA-" << id << " or CA-" << id << "): "; cin >> acc;
                            cout << "Amount: "; cin >> amt;
                            // pass true for deposit, false for withdraw
                            b.performTransaction(acc, amt, (cChoice == 1));
                        } else if (cChoice == 3) {
                            // find all accounts that belong to this customer by id in account number
                            for (int j = 0; j < b.accIdx; j++) {
                                if (b.accounts[j]->accNo.find(to_string(id)) != string::npos)
                                    b.accounts[j]->showAccount(); // virtual function call, work for both SA and CA
                            }
                        } else break; // logout from customer portal

                        // pause here so output visible before screen clear
                        cout << "\nPress Enter to continue...";
                        cin.ignore(); cin.get();
                    }
                }
            }

            // if id not found in array, show error
            if (!found) {
                cout << "Invalid Login ID!\n";
                cout << "\nPress Enter to continue...";
                cin.ignore(); cin.get();
            }
        }
        else if (mainChoice == 3) break; // exit program
    }
    return 0;
}
