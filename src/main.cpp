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

	sf::Font font;
	font.loadFromFile(FONT_FILE);

	// ------------------ TextBox ------------------------------

	Textbox *textbox1 = new Textbox(30, sf::Color::White, true);

	textbox1->setFont(font);
	textbox1->setPosition({170, 400});

	// ---------------------------------------------------------

	GameStats *statsSegment = new GameStats(400, 0, 400, 400, sf::Color::White);
	GameMenu *menuSegment = new GameMenu(0, 400, 400, 800, sf::Color::Red, textbox1);
	GameWorld *world = new GameWorld();
	world->setMap();

	GameWindow *window = new GameWindow(sf::VideoMode(800, 800), "Battle of the Elements", world, menuSegment, statsSegment);
	window->setKeyRepeatEnabled(true);

	sf::Text text("1) OPCION:", font, 26);
	text.setPosition(sf::Vector2f(10, 410));
	text.setFillColor(sf::Color::Blue);
	sf::String playerInput;

	// Adding some characters
	vector<Character *> characters;

	Character *character1 = new WaterCharacter("Juan", WATER, 80, 2);
	character1->setPos(sf::Vector2f(0, 0));
	world->addCharacter(character1, 1);

	Character *character2 = new FireCharacter("Jose", FIRE, 50, 1);
	character2->setPos(sf::Vector2f(1, 0));
	world->addCharacter(character2, 2);

	Stack<sf::Vector2f> *movStack = new Stack<sf::Vector2f>();

	int turn = 0; // for testing purposes
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
				window->menu->textbox->typedOn(event);
				break;

			default:
				break;
			}
		}

		window->clear();
		drawScreen(window);
		window->display();
		if (turn%2)
			processMoveChoice(movStack, window, world->player1Characters[0]);
		else
			processMoveChoice(movStack, window, world->player2Characters[0]);
		turn ++;
	}

	delete character1;
	delete character2;

	delete movStack;
	delete window;
	return 0;
}
