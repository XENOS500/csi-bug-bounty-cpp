#ifndef MENU_H
#define MENU_H

#include "Wallet.h"
#include "User.h"

class Menu {
public:
    Menu(Wallet& wallet, User& user);

    void run();

private:
    Wallet& wallet_;
    User& user_;

    void showMainMenu();
    void handleAddTransaction();
    void handleViewHistory();
    void handleViewStats();
    void handleDeleteTransaction();
};

#endif
