#include <iostream>
#include "Bank.h"
using namespace std;

// Static member definitions (must be in a .cpp, not in header)
int Account::totalAccounts = 0;
int Branch::nextAutoID = 1001;

// ---------------- MAIN PROGRAM ----------------
int main() {
    Branch b("Blue Area Islamabad Branch");
    b.loadFromFile(); // Initial load when program starts

    Bank myBank("Bahria Bank", &b);

    int mainChoice;
    while (true) {
        system("cls"); // Clear screen before showing main menu
        cout << "\n===== " << myBank.bankName << " MANAGEMENT SYSTEM =====\n";
        cout << "1. Employee Portal (Admin)\n2. Customer Portal (User)\n3. Exit\nChoice: ";
        cin >> mainChoice;

        if (mainChoice == 1) { // EMPLOYEE LOGIC
            int empChoice;
            while (true) {
                system("cls"); // Clear screen before showing employee menu
                cout << "\n-- EMPLOYEE MENU --\n1. Add Customer\n2. Add Loan\n3. View Records\n4. Delete Account\n5. Logout\nChoice: ";
                cin >> empChoice;
                if (empChoice == 1) {
                    string n; cout << "Customer Name: "; cin.ignore(); getline(cin, n);
                    b.createCustomerRecord(n);
                } else if (empChoice == 2) b.addLoan();
                else if (empChoice == 3) b.showAll();
                else if (empChoice == 4) {
                    int id; cout << "Enter ID to delete: "; cin >> id;
                    b.deleteCustomerRecord(id);
                } else break;

                // Pause so user can read output before screen clears
                cout << "\nPress Enter to continue...";
                cin.ignore(); cin.get();
            }
        }
        else if (mainChoice == 2) { // CUSTOMER LOGIC
            system("cls");
            int id; cout << "Enter your ID to login: "; cin >> id;
            bool found = false;
            for (int i = 0; i < b.custIdx; i++) {
                if (b.customers[i].id == id) {
                    found = true;
                    int cChoice;
                    while (true) {
                        system("cls"); // Clear screen before customer menu
                        cout << "\n-- Welcome " << b.customers[i].name << " --\n";
                        cout << "1. Deposit\n2. Withdraw\n3. Check Balance\n4. Logout\nChoice: ";
                        cin >> cChoice;
                        if (cChoice == 1 || cChoice == 2) {
                            string acc; double amt;
                            cout << "Account No (SA-" << id << " or CA-" << id << "): "; cin >> acc;
                            cout << "Amount: "; cin >> amt;
                            b.performTransaction(acc, amt, (cChoice == 1));
                        } else if (cChoice == 3) {
                            for (int j = 0; j < b.accIdx; j++) {
                                if (b.accounts[j]->accNo.find(to_string(id)) != string::npos)
                                    b.accounts[j]->showAccount();
                            }
                        } else break;

                        // Pause so user can read output before screen clears
                        cout << "\nPress Enter to continue...";
                        cin.ignore(); cin.get();
                    }
                }
            }
            if (!found) {
                cout << "Invalid Login ID!\n";
                cout << "\nPress Enter to continue...";
                cin.ignore(); cin.get();
            }
        }
        else if (mainChoice == 3) break;
    }
    return 0;
}
