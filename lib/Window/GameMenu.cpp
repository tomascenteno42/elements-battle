#include "../../src/main.h"

void GameMenu::FillMenuList()
{
    int menuLength1 = getAmountOfOptions(OPTIONS_FILE_1);
    int menuLength2 = getAmountOfOptions(OPTIONS_FILE_2);
    int menuLength3 = getAmountOfOptions(OPTIONS_FILE_3);
    int menuLength4 = getAmountOfOptions(OPTIONS_FILE_4);

    Menu* m1 = new Menu(menuLength1);
    Menu* m2 = new Menu(menuLength2);
    Menu* m3 = new Menu(menuLength3);
    Menu* m4 = new Menu(menuLength4);

    fillMenu(m1, OPTIONS_FILE_1);
    fillMenu(m2, OPTIONS_FILE_2);
    fillMenu(m3, OPTIONS_FILE_3);
    fillMenu(m4, OPTIONS_FILE_4);

    MenuList->add(m1, 1);
    MenuList->add(m2, 2);
    MenuList->add(m3, 3);
    MenuList->add(m4, 4);

    ChosenMenu = MenuList->get(1);
}

void GameMenu::ChangeChosen(size_t pos)
{
    ChosenMenu = MenuList->get(pos);
    cout << ChosenMenu->getLength() << endl;
    cout << "Chosen changed" << endl;
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
