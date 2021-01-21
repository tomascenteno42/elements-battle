#include "main.h"

int main() {

	GameWorld world;
	world.setMap();

	sf::RenderWindow mapWindow(sf::VideoMode(800, 800),
			"Battle of the Elements");
	GameCell test(400, 0, 400, 400, sf::Color::White);
	GameCell test2(0, 400, 400, 800, sf::Color::Red);

	sf::Font font;
	font.loadFromFile("arial.ttf");

	sf::Text texto("1) OPCION:", font, 26);
	texto.setPosition(sf::Vector2f(10, 410));
	texto.setFillColor(sf::Color::Blue);
	sf::String playerInput;

// -----------------SHORTEST PATHS TESTS
	int distances[64][64] = {0};
	sf::Vector2f paths[64][64];
	shortestPathsFW(world, distances, paths, water);

	Stack* movStack = new Stack();
	sf::Vector2f startingPos = sf::Vector2f(1,1);
	sf::Vector2f endingPos = sf::Vector2f(4,7);
	loadMovementsStack(movStack, startingPos, endingPos, paths);
	while(!movStack -> isEmpty()) {
		sf::Vector2f pos = movStack -> peek();
		std::cout << "[" << pos.x << "," << pos.y << "]" << ", ";
		movStack -> pop();
	}
	delete movStack;
// ---------------------------------------------------

	while (mapWindow.isOpen()) {
		// SOLO PARA CERRAR LA VENTANA
		sf::Event event;
		while (mapWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
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

		}

		//limpia todo lo que haya antes
		mapWindow.clear();

		// Arregle un Werror de comparacion entre int y size_t
		int size = world.tiles.size();
		for (int i = 0; i < size; ++i) {
			mapWindow.draw(world.tiles[i]->cell);
		}
		// dibujas lo que tenes dibujar
		mapWindow.draw(test.cell);
		mapWindow.draw(test2.cell);
		mapWindow.draw(texto);
		//MOSTRA LO DIBUJADO
		mapWindow.display();
	}

	return 0;
}
