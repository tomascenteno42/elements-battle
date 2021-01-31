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

	List *l = new List; // Characters List

	sf::Font font;
	font.loadFromFile(FONT_FILE);

	// ---------------------- TextBox ---------------------------
	Textbox *textbox1 = new Textbox(30, sf::Color::White, true);

	textbox1->setFont(font);
	textbox1->setPosition({30, 750});

	// ---------------------- GameStats -------------------------
	GameStats *statsSegment = new GameStats(400, 0, 400, 400, sf::Color::White);

	// ---------------------- GameMenu --------------------------
	GameMenu *menuSegment = new GameMenu(0, 400, 400, 800, sf::Color::Red, textbox1);
	menuSegment->FillMenuList();

	// ---------------------- GameWorld -------------------------
	GameWorld *world = new GameWorld();
	world->setMap();

	// --------------------- GameWindow -------------------------
	GameWindow *window = new GameWindow(sf::VideoMode(800, 800), "Battle of the Elements", world, menuSegment, statsSegment);
	window->setKeyRepeatEnabled(true);

	Stack<sf::Vector2f> *movStack = new Stack<sf::Vector2f>();

	sf::Text text("1) OPCION:", font, 26);
	text.setPosition(sf::Vector2f(10, 410));
	text.setFillColor(sf::Color::Blue);
	sf::String playerInput;


	// Adding some characters
	Character *character1 = new WaterCharacter("WaterChr", WATER, 80, 2);
	character1->setPos(sf::Vector2f(0, 0));
	world->addCharacter(character1, 1);

	Character *character2 = new AirCharacter("AirChr", AIR, 50, 1);
	character2->setPos(sf::Vector2f(1, 0));
	world->addCharacter(character2, 1);

	Character *character3 = new FireCharacter("FireChr", FIRE, 50, 1);
	character3->setPos(sf::Vector2f(7, 0));
	world->addCharacter(character3, 2);

	Character *character4 = new EarthCharacter("EarthChr", EARTH, 80, 2);
	character4->setPos(sf::Vector2f(6, 2));
	world->addCharacter(character4, 2);

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
				window->menu->textbox->typedOn(event);
				string input = window->menu->textbox->getText();
				cout << input << endl;
				if (event.text.unicode == ENTER_KEY)
				{
					if (input.size() == 1)
					{
						renderMenu(l, window);
					}
				}
				break;
			}
			default:
				break;
			}
		}

		window->clear();
		drawScreen(window);
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
			for (int i = 0; i < 2; i ++)
			{
				world->player1Characters[i]->setEnergy(20);
				processMoveChoice(movStack, window, world->player1Characters[i]);
				processAttackChoice(world, world->player1Characters[i], world->player2Characters);
			}
		}
		else
		{
			for (int i = 0; i < 2; i ++)
			{
				world->player2Characters[i]->setEnergy(20);
				processMoveChoice(movStack, window, world->player2Characters[i]);
				processAttackChoice(world, world->player2Characters[i], world->player1Characters);
			}
		} 
		turn ++; */
	}

	delete movStack;
	delete window;
	delete l;         // Characters list
	return 0;
}
