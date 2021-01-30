#ifndef MENU_H_
#define MENU_H_

#include "../src/main.h"

class Menu
{
private:
    string *options;
    int index = 0;
    int length = 0;

public:
    Menu(int cantidad);
    Menu(const Menu &L);            // copy constructor
    Menu &operator=(const Menu &L); // assignment

    string getOption(int i);
    int getLength();

    /**
     * Adds an option to Menu.
     * @param option Option string to be added to the menu options.
    */
    void addOption(string option);

    /**
     * Prints all menu options.
    */
    void showAllOptions();

    ~Menu();
};

#endif
