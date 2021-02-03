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
	GameStats *stats = new GameStats(400, 0, 400, 400, sf::Color::White);
	GameWindow *window = new GameWindow(sf::VideoMode(800, 800), "Battle of the Elements", world, stats);


	// ---------------------- GameMenu --------------------------
	GameMenu *menu = new GameMenu(0, 400, 400, 800, sf::Color::Red, window);

	// --------------------------------------------------------------------Adding all characters (manually for now)
	Character *character1 = new WaterCharacter("WaterChr1", WATER, 100, 2);
	character1->setPos(sf::Vector2f(0, 0));
	world->addCharacter(character1, 1);

	Character *character2 = new AirCharacter("AirChr1", AIR, 100, 2);
	character2->setPos(sf::Vector2f(1, 0));
	world->addCharacter(character2, 1);

	Character *character3 = new FireCharacter("FireChr1", FIRE, 100, 2);
	character3->setPos(sf::Vector2f(0, 1));
	world->addCharacter(character3, 1);

	Character *character4 = new EarthCharacter("EarthChr2", EARTH, 100, 2);
	character4->setPos(sf::Vector2f(7, 7));
	world->addCharacter(character4, 2);

	Character *character5 = new FireCharacter("AirChr2", AIR, 100, 2);
	character5->setPos(sf::Vector2f(6, 7));
	world->addCharacter(character5, 2);

	Character *character6 = new EarthCharacter("WaterChr2", WATER, 100, 2);
	character6->setPos(sf::Vector2f(7, 6));
	world->addCharacter(character6, 2);
	// ------------------------------------------------------------------------------------------------------------

	List *l = new List; // Characters List
	int turn = 1; // for testing purposes
	bool stop = false; 	// para que sea mas facil cerrar la ventana y
	string stopStr;		// que no se cuelgue mientras hacemos pruebas

	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window->close();
				break;

			case sf::Event::TextEntered:
			{
				// ¿if (moving) break;?
				menu->textbox->typedOn(event);
				string input = menu->textbox->getText();
				cout << input << endl;
				if (event.text.unicode == ENTER_KEY)
				{
					// Acá es cuando se hace que avance el menu
					// tendria que hacer algo tipo window->menu->processInput(input)
					// y que depende en qué menú se esté ese input se trate de una manera u otra
					// Y luego del procesado, resetear input a la cadena vacia
					if (input.size() == 1)
					{
						renderMenu(l, menu);
					}
					menu->textbox->setText("");
				}
				break;
			}
			default:
				break;
			}
		}

		window->clear();
		drawScreen(window, menu);
		window->display();

/* 		if (!stop)									// para que sea mas facil cerrar la ventana y
		{											// que no se cuelgue mientras hacemos pruebas
			std::cout << "Keep playing? [Y/N] ";	//
			cin >> stopStr;							//
			if (stopStr == "N") stop = true;		//
		} 											//
		if (stop) continue;							//

		printStats(world); // for testing purposes

		if (turn%2)
		{
			for (int i = 0; i < 3; i ++)
			{
				world->player1Characters[i]->setEnergy(20);
				processMoveChoice(movStack, window, world->player1Characters[i]);
				processAttackChoice(world, world->player1Characters[i], world->player2Characters);
			}
		}
		else
		{
			for (int i = 0; i < 3; i ++)
			{
				world->player2Characters[i]->setEnergy(20);
				processMoveChoice(movStack, window, world->player2Characters[i]);
				processAttackChoice(world, world->player2Characters[i], world->player1Characters);
			}
		} 
		turn ++; */
	}

	delete window;
	delete menu;
	delete l;         // Characters list
	return 0;
}
