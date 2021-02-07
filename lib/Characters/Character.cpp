#include "../../src/main.h"

Character::Character(string n, int l, int s)
{
	energy = 20; //rand() % 20;

	name = n;
	life = l;
	shield = s;
	pos = sf::Vector2f(-1, -1);
	setCell();
}

/* GETTERS */

string Character::getName()
{
	return name;
}

int Character::getLife()
{
	return life;
}

int Character::getShield()
{
	return shield;
}

int Character::getEnergy()
{
	return energy;
}

sf::Vector2f Character::getPos()
{
	return pos;
}

sf::RectangleShape Character::getCell()
{
	return cell;
}

bool Character::isDead()
{
	return (getLife() == 0);
}

/* SETTERS */

void Character::setName(string n)
{
	name = n;
}

void Character::setLife(int l)
{
	life = l;
}

void Character::setShield(int s)
{
	shield = s;
}

void Character::setEnergy(int e)
{
	energy = e;
}

void Character::setPos(sf::Vector2f pos)
{
	this->pos = pos;
	setCell();
}

void Character::setCell()
{
	cell.setPosition(sf::Vector2f(50 * pos.x + 12.5, 50 * pos.y + 12.5));
	cell.setSize(sf::Vector2f(25, 25));
	cell.setOutlineThickness(1);
	cell.setOutlineColor(sf::Color::Black);
}

/* TP3 */

void Character::move(GameWindow *window, sf::Vector2f destination, int energyRequired)
{
	energy -= energyRequired;
	std::cout << "Energy Consumed: " << energyRequired << std::endl;

	Stack<sf::Vector2f> *movStack = window->world->movStack;
	loadMovementsStack(movStack, pos, destination, window->world->paths[static_cast<int>(getElement()) - 1]);
	movStack->push(pos);
	while (!movStack->isEmpty())
	{
		setPos(movStack->peek());
		movStack->pop();
		this_thread::sleep_for(chrono::milliseconds(250));

		window->clear();
		drawScreen(window);
		window->display();
	}
}

Character::~Character() = default;
