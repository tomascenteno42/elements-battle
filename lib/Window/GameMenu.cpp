#include "../../src/main.h"

void GameMenu::FillMenuList()
{
    int menuLength = getAmountOfOptions(OPTIONS_FILE);
    int menuLength2 = getAmountOfOptions(OPTIONS_FILE_2);

    Menu* m1 = new Menu(menuLength);
    Menu* m2 = new Menu(menuLength2);

    fillMenu(m1, OPTIONS_FILE);
    fillMenu(m2, OPTIONS_FILE_2);

    MenuList->add(m1, 1);
    MenuList->add(m2, 2);

    ChosenMenu = MenuList->get(1);
}

void GameMenu::ChangeChosen(size_t pos)
{
    ChosenMenu = MenuList->get(pos);
    cout << ChosenMenu->getLength() << endl;
    cout << "CHosen changed" << endl;
}

Menu* GameMenu::GetChosenMenu()
{
    return ChosenMenu;
}

GameMenu::~GameMenu()
{
    delete textbox;    
    delete MenuList;
}
