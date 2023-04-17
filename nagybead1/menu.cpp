#include <iostream>
#include "menu.h"
#include <sstream>
#define menudb 6

using namespace std;

bool check(int a) { return a >= 0 && a <= menudb; }

template <typename Item>
Item read( const std::string &msg, const std::string &err, bool valid(Item))
{
    Item n;
    bool wrong;
    do {
        std::cout << msg;
        std::cin >> n;
        if ((wrong = std::cin.fail())) std::cin.clear();
        std::string tmp;
        getline(std::cin, tmp);
        wrong = wrong || tmp.size()!=0 || !valid(n);
        if (wrong) std::cout << err << std::endl;
    } while (wrong);
    return n;
}

void Menu::run() {
    int v;
    do {
        v = printMenu();
        switch(v) {
            case 1:
                getItem();
                printMatrix();
                break;
            case 2:
                setItems();
                printMatrix();
                break;
            case 3:
                setItem();
                printMatrix();
                break;
            case 4:
                sum();
                printMatrix();
                break;
            case 5:
                multiply();
                printMatrix();
                break;
            case 6:
                printMatrix();
                break;
            default:
                cout<<"\nSee you!\n";
                break;
        }
    } while (v != 0);
}

int Menu::printMenu()
{
    int answer;
    cout << "\n****************************************\n";
    cout << "0. Quit\n";
    cout << "1. Get the item at given row and given column\n";
    cout << "2. Set all the non 0 values of the matrix to given value\n";
    cout << "3. Set a specific position of the matrix to given value\n";
    cout << "4. Sum two matrices\n";
    cout << "5. Multiply two matrices\n";
    cout << "6. Print Matrix\n";
    cout << "****************************************\n\n";
    ostringstream s;
    s << "Number should be between 0 and " << menudb << endl;
    string errorMessage = s.str();
    answer = read<int>(">>>", errorMessage, check);
    cout << "\n";
    return answer;
}

void Menu::getItem() {
    int i, j, e;
    bool fail = false;

    cout << "Row and column:\n>>>";
    cin >> i >> j;
    try {
        e = M.getItem(i, j);
    } catch (NMatrix::Exception err) {
        fail = true;
        if (err == NMatrix::OVERINDEXED) {
            cerr << "Can't get item, index out of range!\n";
        }
        else {
            cerr << "The program doesn't work as intended, report to the writer\n";
        }
    }
    if(!fail) {
        cout << "Item at " << i << ". row and " << j << ". column: " << e << "\n\n";
    }
}

void Menu::setItems() {
    int e;
    cout << "Value to set:\n>>>";
    cin >> e;
    M.setItem(e);
    cout << "\n";
}

void Menu::setItem() {
    int i, j, e;
    bool fail = false;

    cout << "Row, column and value to set:\n>>>";
    cin >> i >> j >> e;
    try {
        M.setItem(i, j, e);
    } catch (NMatrix::Exception err) {
        fail = true;
        if (err == NMatrix::OVERINDEXED) {
            cerr << "Can't set item, index out of range!\n";
        }
        else if (err == NMatrix::NULLPART) {
            cerr << "Can't set value to this position!\n";
        }
        else {
            cerr << "The program doesn't work as intended, report to the writer\n";
        }
    }
    if(!fail) {
        cout << "Position value set\n\n";
    }
}

void Menu::sum() {
    NMatrix a(5);
    int a_val;
    bool fail = false;

    cout << "Give value to the matrix: ";
    cin >> a_val;
    a.setItem(a_val);

    try {
        a+M;
    } catch (NMatrix::Exception err) {
        fail = true;
        if (err == NMatrix::NOT_MATCHING_SIZE) {
            cerr << "Matrix sizes do not match!\n******************************************************\n";
        }
        else {
            cerr << "The program doesn't work as intended, report to the writer\n";
        }
    }
    if(!fail) {
        cout << "\nSum of our and the given matrix:\n"; 
        cout << a+M << "\n";
    }
    
}

void Menu::multiply() {
    NMatrix a(5);
    int a_val;
    bool fail = false;

    cout << "Give value to the matrix: ";
    cin >> a_val;
    a.setItem(a_val);

    try {
        a+M;
    } catch (NMatrix::Exception err) {
        fail = true;
        if (err == NMatrix::NOT_MATCHING_SIZE) {
            cerr << "Matrix sizes do not match!\n******************************************************\n";
        }
        else {
            cerr << "The program doesn't work as intended, report to the writer\n";
        }
    }
    if(!fail) {
        cout << "\nOur matrix multiplied by given matrix:\n";
        cout << a*M << "\n";
    }

    
}

void Menu::printMatrix() {
    cout << M << "\n";
}