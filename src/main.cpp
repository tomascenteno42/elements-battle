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
	Character* character1 = new WaterCharacter("Juan", WATER, 80, 2);
	character1 -> setPos(sf::Vector2f(0,0));
	Character* character2 = new FireCharacter("Jose", FIRE, 50, 1);
	character2 -> setPos(sf::Vector2f(1,0));
	vector<Character *> characters;
	characters.push_back(character1);
	characters.push_back(character2);

	world -> tiles[character1->getPos().x + 8 * character1->getPos().y] -> setOccupied(true);
	world -> tiles[character2->getPos().x + 8 * character2->getPos().y] -> setOccupied(true);

	Stack *movStack = new Stack();
	int turn = 0;
	// ---------------------------------------------------------

	while (mapWindow.isOpen())
	{
		this_thread::sleep_for(chrono::milliseconds(250));

		// SOLO PARA CERRAR LA VENTANA
		sf::Event event;
		while (mapWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				mapWindow.close();
			}
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
		}
		//limpia todo lo que haya antes
		mapWindow.clear();
		// Arregle un Werror de comparacion entre int y size_t
		for (size_t i = 0; i < world->tiles.size(); i++)
		{
			mapWindow.draw(world->tiles[i]->cell);
		}

		// dibujas lo que tenes dibujar
		mapWindow.draw(statsSegment->cell);
		mapWindow.draw(optionsSegment->cell);
		mapWindow.draw(characters[0]->getCell());
		mapWindow.draw(characters[1]->getCell());
		mapWindow.draw(texto);
		//MOSTRA LO DIBUJADO
		mapWindow.display();

		if (movStack -> isEmpty())
		{
			turn ++;
			sf::Vector2f playerPos = characters[turn%2] -> getPos();
			bool canMove;
			sf::Vector2f destination = askDestination();
			canMove = validDestination(world, destination);
			while (!canMove)
			{
				std::cout << "You can't move there, the cell is occupied" << std::endl;
				destination = askDestination();
				canMove = validDestination(world, destination);
			}
			world -> tiles[playerPos.x + 8 * playerPos.y] -> setOccupied(false);
			world -> tiles[destination.x + 8 * destination.y] -> setOccupied(true);
			std::cout << "Energy consumed: " << world->distances[static_cast<int>(characters[turn%2] -> getElement()) - 1][int(playerPos.x + 8 * playerPos.y)][int(destination.x + 8 * destination.y)] << std::endl;

			loadMovementsStack(movStack, playerPos, destination, world->paths[static_cast<int>(characters[turn%2] -> getElement()) - 1]);
			movStack->push(playerPos);
		}

		moveCharacter(characters[turn%2], movStack);


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

	delete character1;
	delete character2;

	delete statsSegment;
	delete optionsSegment;
	delete movStack;
	delete world;

	return 0;
}
