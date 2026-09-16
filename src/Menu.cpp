#include "Menu.h"
#include "Stats.h"
#include "InputValidator.h"
#include <iostream>
#include <string>

using namespace std;

Menu::Menu(Wallet& wallet, User& user)
    : wallet_(wallet), user_(user) {}

void Menu::showMainMenu() {
    cout << "\nDigital Wallet Menu" << endl;
    cout << "1. View Transaction History" << endl;
    cout << "2. Add Transaction" << endl;
    cout << "3. View Stats" << endl;
    cout << "4. Delete Transaction" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter choice: ";
}

void Menu::run() {
    char choice = 0;
    bool exitRequested = false;

    while (!exitRequested) {
        showMainMenu();
        cin >> choice;

        switch (choice) {
            case '1':
                handleViewHistory();
                break;
            case '2':
                handleAddTransaction();
                break;
            case '3':
                handleViewStats();
                break;
            case '4':
                handleDeleteTransaction();
                break;
            case '5':
                cout << "Exiting wallet. Goodbye!" << endl;
                exitRequested = true;
                break;
            default:
                cout << "Invalid choice, try again." << endl;
                
        }
    }
}

void Menu::handleAddTransaction() {
    cin.ignore();
    string typeInput;
    cout << "Enter type (credit/debit): ";
    getline(cin, typeInput);

    double amount;
    cout << "Enter amount: ";
    cin >> amount;
    cin.ignore();

    if (amount ==0) {
        cout << "Amount cannot be zero." << endl;
        return;
    }

    string description;
    cout << "Enter description: ";
    getline(cin, description);

    TransactionType type = (typeInput == "credit") ? TransactionType::CREDIT : TransactionType::DEBIT;
    wallet_.addTransaction(type, amount, description);
    cout << "Transaction added successfully." << endl;
}

void Menu::handleViewHistory() {
    const auto& transactions = wallet_.getTransactions();
    if (transactions.empty()) {
        cout << "No transactions yet." << endl;
        return;
    }

    cout << "\n--- Transaction History ---" << endl;
    for (const auto& txn : transactions) {
        cout << "#" << txn.getId() << " | "
                  << (txn.getType() == TransactionType::CREDIT ? "CREDIT" : "DEBIT") << " | "
                  << txn.getAmount() << " | " << txn.getDescription() << endl;
    }
}

void Menu::handleViewStats() {
    Stats::displaySummary(wallet_.getTransactions(), wallet_.getBalance());
}

void Menu::handleDeleteTransaction() {
    int id;
    cout << "Enter transaction ID to delete: ";
    cin >> id;

    if (wallet_.deleteTransaction(id)) {
        cout << "Transaction deleted." << endl;
    } else {
        cout << "Transaction ID not found." << endl;
    }
}
// bug - when takes character input goes in infinite loop
//bug  - in add transaction when we debit (having current amount ==0) it still logs the transaction , it should have  had given an error