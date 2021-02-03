#ifndef GAMEMENU_H_
#define GAMEMENU_H_

#include "../../src/main.h"

class GameMenu : public Cell
{
private:
    GenericList<Menu*>* menuList;
    Menu* currentMenu;
    menus currentMenuIndex;
    int currentOption = 0;  // cual fue la ultima opcion que se eligio, por ejemplo la opcion 5
                            // (se sabe qué menú es gracias a ChosenMenu) Entonces cuando se procesa un input,
                            // se procesa según qué opción lo llamó

    sf::Text request; // el pedido de informacion al usuario, por ejemplo "ingrese una opcion" o "ingrese el nombre del personaje"   
    sf::Font font;

public:
    GameWindow* window;
    Textbox *textbox;
    bool waitingForOptionChoice = true; // para diferenciar de cuando el usuario tiene que elegir una opcion del menu
                                        // de cuando tenga que por ejemplo decir a que posicion del mapa moverse
                                        // en ambos casos se ingresa un numero. Si se elige una opcion que no despliega
                                        // un menu nuevo, este atributo cambia a false. Luego de que se termine de procesar
                                        // esa opcion, vuelve a true

    GameMenu(float xPos, float yPos, float ySize, float xSize, sf::Color color, GameWindow* window);

    void fillMenuList();
    void changeCurrentMenu(size_t pos);
    void setRequest(std::string req);

    Menu* getCurrentMenu();

    void drawCurrentMenu();
    void processInput(); // toma el input que haya en la textbox y lo procesa según en qué menú se esté y en qué opción

    ~GameMenu();
};

#endif
