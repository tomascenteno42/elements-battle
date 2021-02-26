#ifndef MENU_H_
#define MENU_H_

#include "../../src/main.h"

class Menu
{
private:
    string* options;
    int index = 0;
    int length = 0;

public:
    Menu(int length);

    Menu(const Menu &L);            // copy constructor
    Menu &operator=(const Menu &L); // assignment

    string getOption(int i);
    int getLength();

    /*
     * Adds an option to Menu.
     */
    void addOption(string option);

    ~Menu();
};

#endif
