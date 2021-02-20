#include "main.h"

int main()
{
	srand(time(NULL));
	GameWindow *window = new GameWindow(sf::VideoMode(800, 800), "Battle of the Elements");
	BST<string, Character*>* characterMap = new BST<string, Character*>();
	loadCharacterData(characterMap);

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
					window->menu->render(characterMap);
				break;

			default:
				break;
			}
		}

		window->clear();
		drawScreen(window);
		window->display();
	}

	saveChangesToCharFile(characterMap);

	delete window;
	delete characterMap;
	
	return 0;
}
