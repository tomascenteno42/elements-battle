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

	GameWindow *window = new GameWindow(sf::VideoMode(800, 800), "Battle of the Elements");

	// Adding all characters
	Character *character1 = new WaterCharacter("WaterChr1", 100, 2);
	character1->setPos(sf::Vector2f(0, 0));
	window->world->addCharacter(character1, 1);

	Character *character2 = new AirCharacter("AirChr1", 100, 2);
	character2->setPos(sf::Vector2f(1, 0));
	window->world->addCharacter(character2, 1);

	Character *character3 = new FireCharacter("FireChr1", 100, 2);
	character3->setPos(sf::Vector2f(0, 1));
	window->world->addCharacter(character3, 1);

	Character *character4 = new WaterCharacter("WaterChr2", 100, 2);
	character4->setPos(sf::Vector2f(6, 7));
	window->world->addCharacter(character4, 2);

	Character *character5 = new FireCharacter("FireChr2", 100, 2);
	character5->setPos(sf::Vector2f(7, 6));
	window->world->addCharacter(character5, 2);

	Character *character6 = new EarthCharacter("EarthChr2", 100, 2);
	character6->setPos(sf::Vector2f(7, 7));
	window->world->addCharacter(character6, 2);

	window->world->currentCharacter = character1;


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
				if (event.text.unicode == ENTER_KEY)
					window->menu->render();
				break;

			default:
				break;
			}
		}

		window->clear();
		drawScreen(window);
		window->display();
	}

	delete window;
	return 0;
}
