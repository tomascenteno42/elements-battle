#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
//#include <SFML/>
#include "../GameCell.h"
#include <iostream>
#include <math.h>
#include <string.h>

int main()
{

	//x, y, h, w, color
    GameCell cell1(0, 0, 50, 50, sf::Color::Cyan);
    GameCell cell2(50, 0, 50, 50, sf::Color::Cyan);
    GameCell cell3(100, 0, 50, 50, sf::Color::White);
    GameCell cell4(150, 0, 50, 50, sf::Color::White);
    GameCell cell5(50, 0, 50, 50, sf::Color::Cyan);

    GameCell enemy(12.5, 12.5, 25, 25, sf::Color::Red);


    sf::RenderWindow mapWindow(sf::VideoMode(800,800), "Battle of the Elements");

    GameCell test(400, 0, 400, 400, sf::Color::White);
    GameCell test2(0, 400, 400, 800, sf::Color::Red);

    sf::Font font;
    font.loadFromFile("arial.ttf");

    sf::Text texto("1) OPCION:", font, 26);
    texto.setPosition(sf::Vector2f(10, 410));
    texto.setColor(sf::Color::Blue);
    sf::String playerInput;

    while (mapWindow.isOpen())
    {
    	// SOLO PARA CERRAR LA VENTANA
        sf::Event event;
        while (mapWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                mapWindow.close();
            if (event.type == sf::Event::TextEntered) {
            	if(event.text.unicode != '\r') {
					if (event.text.unicode == '\b') { // handle backspace explicitly
						if(playerInput.getSize() != 0) {
							playerInput.erase(playerInput.getSize() - 1, 1);
						}
					} else { // all other keypresses
						playerInput += static_cast<char>(event.text.unicode);
					}
            	} else {
            		texto.setString(playerInput);
            	}
            }

        }

        //limpia todo lo que haya antes
        mapWindow.clear();

        // dibujas lo que tenes dibujar
        mapWindow.draw(cell1.cell);
        mapWindow.draw(cell2.cell);
        mapWindow.draw(cell3.cell);
        mapWindow.draw(cell4.cell);
        mapWindow.draw(enemy.cell);
        mapWindow.draw(test.cell);
        mapWindow.draw(test2.cell);
        mapWindow.draw(texto);
        //MOSTRA LO DIBUJADO
        mapWindow.display();
    }

    return 0;
}
