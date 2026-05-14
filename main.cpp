#include <iostream>
#include "Bank.h"
using namespace std;

// static member must define outside class in .cpp file, cannot define in header
// i get error before because i put it inside header, teacher help me fix
int Account::totalAccounts = 0;
int Branch::nextAutoID = 1001; // id start from 1001, look more professional

//              MAIN PROGRAM 
// this is main function where everything run
// i made two portal: employee portal and customer portal

void displayBanner() {
    cout << "\n";
    cout << "  ╔════════════════════════════════════════════════════════════╗\n";
    cout << "  ║                                                            ║\n";
    cout << "  ║          / / / BAHRIA BANK MANAGEMENT SYSTEM / / /         ║\n";
    cout << "  ║         / /                                   / /          ║\n";
    cout << "  ║        / /      Professional Banking Portal    / /         ║\n";
    cout << "  ║       / /      Blue Area Islamabad Branch     / /          ║\n";
    cout << "  ║      / / / / / / / / / / / / / / / / / / / / / / /         ║\n";
    cout << "  ║                                                            ║\n";
    cout << "  ╚════════════════════════════════════════════════════════════╝\n";
    cout << "\n";
}

void displayMainMenu() {
    cout << "\n  ┌────────────────────────────────────────────────────────────┐\n";
    cout << "  │              WELCOME TO MAIN MENU                           │\n";
    cout << "  ├────────────────────────────────────────────────────────────┤\n";
    cout << "  │  [1] Employee Portal (Admin)                               │\n";
    cout << "  │  [2] Customer Portal (User)                                │\n";
    cout << "  │  [3] Exit Program                                          │\n";
    cout << "  ├────────────────────────────────────────────────────────────┤\n";
    cout << "  │  Enter your choice: ";
}

void displayEmployeeMenu() {
    cout << "\n  ┌────────────────────────────────────────────────────────────┐\n";
    cout << "  │              EMPLOYEE MENU                                  │\n";
    cout << "  ├────────────────────────────────────────────────────────────┤\n";
    cout << "  │  [1] Add New Customer                                      │\n";
    cout << "  │  [2] Add Loan                                              │\n";
    cout << "  │  [3] View All Records                                      │\n";
    cout << "  │  [4] Delete Account                                        │\n";
    cout << "  │  [5] Logout                                                │\n";
    cout << "  ├────────────────────────────────────────────────────────────┤\n";
    cout << "  │  Enter your choice: ";
}

void displayCustomerMenu(string name) {
    cout << "\n  ┌────────────────────────────────────────────────────────────┐\n";
    cout << "  │              WELCOME " << name << "\n";
    cout << "  ├────────────────────────────────────────────────────────────┤\n";
    cout << "  │  [1] Deposit Money                                         │\n";
    cout << "  │  [2] Withdraw Money                                        │\n";
    cout << "  │  [3] Check Balance                                         │\n";
    cout << "  │  [4] Logout                                                │\n";
    cout << "  ├────────────────────────────────────────────────────────────┤\n";
    cout << "  │  Enter your choice: ";
}

int main() {
    // create branch object with name
    Branch b("Blue Area Islamabad Branch");
    b.loadFromFile(); // load saved data when program start, so old data come back

    // create bank object and give it the branch
    Bank myBank("Bahria Bank", &b);

    int mainChoice;
    while (true) {
        system("cls"); // clear screen before showing menu, look cleaner
        displayBanner();
        displayMainMenu();
        cin >> mainChoice;

        if (mainChoice == 1) { // EMPLOYEE LOGIC
            int empChoice;
            while (true) {
                system("cls"); // clear screen before employee menu
                displayBanner();
                displayEmployeeMenu();
                cin >> empChoice;

                if (empChoice == 1) {
                    // get customer name and create record
                    string n; cout << "\n  Enter Customer Name: "; cin.ignore(); getline(cin, n);
                    b.createCustomerRecord(n);
                } else if (empChoice == 2) b.addLoan();
                else if (empChoice == 3) b.showAll();
                else if (empChoice == 4) {
                    int id; cout << "\n  Enter ID to delete: "; cin >> id;
                    b.deleteCustomerRecord(id);
                } else break; // logout from employee portal

                // pause so user can read output before screen clear again
                cout << "\n  Press Enter to continue...";
                cin.ignore(); cin.get();
            }
        }
        else if (mainChoice == 2) { // CUSTOMER LOGIC
            system("cls");
            cout << "\n  Enter your ID to login: "; 
            int id; cin >> id;
            bool found = false;

            // search customer by id in array
            for (int i = 0; i < b.custIdx; i++) {
                if (b.customers[i].id == id) {
                    found = true;
                    int cChoice;
                    while (true) {
                        system("cls"); // clear screen before customer menu
                        displayBanner();
                        displayCustomerMenu(b.customers[i].name);
                        cin >> cChoice;

                        if (cChoice == 1 || cChoice == 2) {
                            // get account number and amount for transaction
                            string acc; double amt;
                            cout << "\n  Account No (SA-" << id << " or CA-" << id << "): "; cin >> acc;
                            cout << "  Amount: "; cin >> amt;
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
                        cout << "\n  Press Enter to continue...";
                        cin.ignore(); cin.get();
                    }
                }
            }

            // if id not found in array, show error
            if (!found) {
                cout << "\n  ✗ Invalid Login ID!\n";
                cout << "  Press Enter to continue...";
                cin.ignore(); cin.get();
            }
        }
        else if (mainChoice == 3) break; // exit program
    }
    
    system("cls");
    cout << "\n  Thank you for using Bahria Bank Management System!\n";
    cout << "  Have a great day!\n\n";
    return 0;
}
