#include "../../src/main.h"

Menu::Menu(int quantity)
{
    length = quantity;
    options = new string[length];
}

void Menu::addOption(string opcion)
{
    options[index] = opcion;
    index++;
}

string Menu::getOption(int i)
{
    return options[i];
}

int Menu::getLength()
{
    return length;
}

/* void Menu::showAllOptions(GameWindow *window)
{
    sf::Font font;
	font.loadFromFile(FONT_FILE);
    float pos = 410;

    for (int i = 0; i < window->menu->GetChosenMenu()->getLength(); i++)
    {
        sf::Text texto((to_string((i + 1)) + ") " + window->menu->GetChosenMenu()->getOption(i)), font, 20);
        texto.setFillColor(sf::Color::White);
	    texto.setPosition(sf::Vector2f(10, pos));
        pos += 50;
        window->draw(texto);
    }
} */

Menu::~Menu()
{
    delete[] options;
}
