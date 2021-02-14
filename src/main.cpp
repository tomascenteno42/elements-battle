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

/* 	BST<string, int>* d = new BST<string, int>();

	string A = "A";
	string B = "B";
	string C = "C";
	string D = "D";
	string E = "E";

	d->insert(D, 4);
	d->insert(A, 1);
	d->insert(C, 3);
	d->insert(B, 2);
	d->insert(E, 5);
	cout << "Inserted 5 nodes" << endl;

	d->showInOrder();

	d->erase(C);
	cout << "Erased 3" << endl;

	d->showInOrder(); 


	delete d;*/

	return 0;
}
