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

	GameWorld *world = new GameWorld();
	world->setMap();

	sf::RenderWindow mapWindow(sf::VideoMode(800, 800), "Battle of the Elements");

	GameCell *statsSegment = new GameCell(400, 0, 400, 400, sf::Color::White);
	GameCell *optionsSegment = new GameCell(0, 400, 400, 800, sf::Color::Red);

	sf::Font font;
	font.loadFromFile(FONT_FILE);

	sf::Text texto("1) OPCION:", font, 26);
	texto.setPosition(sf::Vector2f(10, 410));
	texto.setFillColor(sf::Color::Blue);
	sf::String playerInput;

	// -------------------------------------SHORTEST PATHS TESTS
	GameCell player(12.5, 12.5, 25, 25, sf::Color::Green);
	sf::Vector2f playerPos(0, 0);

	int distances[64][64] = {0};
	sf::Vector2f paths[64][64];
	shortestPathsFW(world, distances, paths, WATER);

	Stack *movStack = new Stack();
	bool stopMove = false;
	// ---------------------------------------------------------


	// ------------------ TextBox ------------------------------

	mapWindow.setKeyRepeatEnabled(true);

	Textbox textbox1(30, sf::Color::White, true);

	textbox1.setFont(font);
	textbox1.setPosition({170, 400});

	// ---------------------------------------------------------


	// Main loop
	while (mapWindow.isOpen())
	{
		//this_thread::sleep_for(chrono::milliseconds(250));

		// SOLO PARA CERRAR LA VENTANA
		sf::Event event;
		//Events loop
		while (mapWindow.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				mapWindow.close();
			//            if (event.type == sf::Event::TextEntered) {
			//            	if(event.text.unicode != '\r') {
			//					if (event.text.unicode == '\b') { // handle backspace explicitly
			//						if(playerInput.getSize() != 0) {
			//							playerInput.erase(playerInput.getSize() - 1, 1);
			//						}
			//					} else { // all other keypresses
			//						playerInput += static_cast<char>(event.text.unicode);
			//					}
			//            	} else {
			//            		texto.setString(playerInput);
			//            	}
			//            }

			case sf::Event::TextEntered:
				textbox1.typedOn(event);
			}
		}

		//limpia todo lo que haya antes
		mapWindow.clear();
		
		// dibujas lo que tenes dibujar
		// Arregle un Werror de comparacion entre int y size_t
		for (size_t i = 0; i < world->tiles.size(); i++)
		{
			mapWindow.draw(world->tiles[i]->cell);
		}
		mapWindow.draw(statsSegment->cell);
		mapWindow.draw(optionsSegment->cell);
		mapWindow.draw(player.cell);
		mapWindow.draw(texto);
		textbox1.drawTo(mapWindow);

		//MOSTRA LO DIBUJADO
		mapWindow.display();

		// -------------------------------------SHORTEST PATHS TESTS
		// if (movStack->isEmpty() && !stopMove)
		// {
		// 	string r;
		// 	cout << "Move? [Y/N] ";
		// 	cin >> r;
		// 	if (r == "N")
		// 		stopMove = true;
		// }

		// if (!stopMove)
		// {
		// 	if (movStack->isEmpty())
		// 	{
		// 		sf::Vector2f destination = askDestination();
		// 		loadMovementsStack(movStack, playerPos, destination, paths);
		// 		movStack->push(playerPos);
		// 	}
		// 	else
		// 	{
		// 		playerPos = movStack->peek();
		// 		movStack->pop();
		// 		player.cell.setPosition(sf::Vector2f(playerPos.x * 50 + 12.5, playerPos.y * 50 + 12.5));
		// 	}
		// }
		// ---------------------------------------------------------
	}

	delete statsSegment;
	delete optionsSegment;
	delete movStack;
	delete world;

	return 0;
}
