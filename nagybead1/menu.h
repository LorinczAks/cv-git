#ifndef MENU_H
#define MENU_H
#include "nMatrix.h"

class Menu {
    public:
        Menu() {};
        void run();
    private:
        int printMenu();
        void getItem();
        void setItem();
        void setItems();
        void sum();
        void multiply();
        void printMatrix();
        NMatrix M;
};

#endif