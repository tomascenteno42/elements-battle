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
	GameStats *statsSegment = new GameStats(400, 0, 400, 400, sf::Color::White);
	GameMenu *menuSegment = new GameMenu(0, 400, 400, 800, sf::Color::Red);
	GameWorld *world = new GameWorld();
	world->setMap();

	GameWindow *window = new GameWindow(sf::VideoMode(800, 800), "Battle of the Elements", world, menuSegment, statsSegment);

	sf::Font font;
	font.loadFromFile(FONT_FILE);

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
	bool stopMove = false;

	while (window->gameWindow->isOpen())
	{
		sf::Event event;
		while (window->gameWindow->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window->gameWindow->close();
			}
		}
		window->gameWindow->clear();
		drawScreen(window);
		window->gameWindow->display();
		Character *character = world->player1Characters[0];
		processMoveChoice(movStack, window, character);
	}

	delete character1;
	delete character2;

	delete movStack;
	delete window;
	return 0;
}
