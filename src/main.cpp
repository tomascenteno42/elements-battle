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

	sf::Text text("1) OPCION:", font, 26);
	text.setPosition(sf::Vector2f(10, 410));
	text.setFillColor(sf::Color::Blue);
	sf::String playerInput;

	// Adding some characters
	vector<Character *> characters;

	Character* character1 = new WaterCharacter("Juan", WATER, 80, 2);
	character1 -> setPos(sf::Vector2f(0,0));
	world -> addCharacter(character1, 1);

	Character* character2 = new FireCharacter("Jose", FIRE, 50, 1);
	character2 -> setPos(sf::Vector2f(1,0));
	world -> addCharacter(character2, 2);

  Stack<sf::Vector2f> *movStack = new Stack<sf::Vector2f>();
	bool stopMove = false;


	while (mapWindow.isOpen())
	{
		sf::Event event;
		while (mapWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				mapWindow.close();
			}
		}
		mapWindow.clear();
		drawScreen(mapWindow, world, statsSegment, optionsSegment, text);
		mapWindow.display();
		Character* character = world -> player1Characters[0];
		processMoveChoice(world, movStack, mapWindow, character, statsSegment, optionsSegment, text);
	}

	delete character1;
	delete character2;

	delete statsSegment;
	delete optionsSegment;
	delete movStack;
	delete world;

	return 0;
}
