#include "main.h"

int main()
{

	//////////////////////// MAIN TP2 //////////////////////////////

	/*     srand((unsigned int)time(0));

    List *l = new List;
    int menuLength = getAmountOfOptions();
    Menu m(menuLength);

    if (menuLength == 0)
    {
        cout << "THERE IS AN ERROR WITH YOUR options.txt FILE" << endl;
        return 0;
    }

    fillMenu(&m);
    fillList(l);

    if ((*l).getQuantity() == 0)
    {
        cout << "THERE IS SOMETHING WRONG WITH YOUR characters.csv FILE" << endl;
        return 0;
    }

    renderMenu(&m, l);
    delete l; */

	////////////////////////////////////////////////////////////////

	GameWorld world;
	world.setMap();

	sf::RenderWindow mapWindow(sf::VideoMode(800, 800), "Battle of the Elements");

	GameCell *statsSegment = new GameCell(400, 0, 400, 400, sf::Color::White);
	GameCell *optionsSegment = new GameCell(0, 400, 400, 800, sf::Color::Red);

	sf::Font font;
	font.loadFromFile(FONT_FILE);

	sf::Text texto("1) OPCION:", font, 26);
	texto.setPosition(sf::Vector2f(10, 410));
	texto.setFillColor(sf::Color::Blue);
	sf::String playerInput;

	while (mapWindow.isOpen())
	{
		// SOLO PARA CERRAR LA VENTANA
		sf::Event event;

		while (mapWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				mapWindow.close();
			}
		}

		//limpia todo lo que haya antes
		mapWindow.clear();
		// Arregle un Werror de comparacion entre int y size_t
		for (size_t i = 0; i < world.tiles.size(); i++)
		{
			mapWindow.draw(world.tiles[i]->cell);
		}

		// dibujas lo que tenes dibujar
		mapWindow.draw(statsSegment->cell);
		mapWindow.draw(optionsSegment->cell);
		mapWindow.draw(texto);
		//MOSTRA LO DIBUJADO
		mapWindow.display();
	}

	delete statsSegment;
	delete optionsSegment;

	return 0;
}
