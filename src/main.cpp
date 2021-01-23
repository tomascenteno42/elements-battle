#include "main.h"

int main() {

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

	cout << "Se inicio el programa" << endl;

	GameWorld *world;
	world->setMap();

	cout << "Se creo world y setNap" << endl;

	sf::RenderWindow mapWindow(sf::VideoMode(800, 800), "Battle of the Elements");
	GameCell *test = new GameCell(400, 0, 400, 400, sf::Color::White);
	GameCell *test2 = new GameCell(0, 400, 400, 800, sf::Color::Red);

	cout << "Se crearon test1 y test2" << endl;

	sf::Font font;
	font.loadFromFile("arial.ttf");

	sf::Text texto("1) OPCION:", font, 26);
	texto.setPosition(sf::Vector2f(10, 410));
	texto.setFillColor(sf::Color::Blue);
	sf::String playerInput;

	while (mapWindow.isOpen()) {
		// SOLO PARA CERRAR LA VENTANA
		sf::Event event;

		cout << "Entro al while" << endl;

		while (mapWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				cout << "close" << endl;
				mapWindow.close();
		}

		//limpia todo lo que haya antes
		mapWindow.clear();
		cout << "clear" << endl;
		
		// Arregle un Werror de comparacion entre int y size_t
	
		int size = world->tiles.size();

		cout << "Va a entrar al for de size " << size << endl;

		for (int i = 0; i < size; i++) {
			mapWindow.draw(world->tiles[i]->cell);
		}
		cout << "dibujo el mapa" << endl;
		// dibujas lo que tenes dibujar
		mapWindow.draw(test->cell);
		mapWindow.draw(test2->cell);
		mapWindow.draw(texto);
		//MOSTRA LO DIBUJADO
		mapWindow.display();
	}

	cout << "Salio del while" << endl;

/* 	string temp;
	cout << "Press Enter to Continue";
	cin >> temp;
	cin >> temp;

	delete test;
	delete test2;
	delete world; */

	return 0;
}
