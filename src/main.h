/*
 * main.h
 *
 *  Created on: Jan 18, 2021
 *      Author: kurepa
 */

#ifndef MAIN_H_
#define MAIN_H_

#define FONT_FILE "files/arial.ttf"
#define OPTIONS_FILE "files/options.txt"
#define CHARACTERS_FILE "files/characters.csv"
#define MAPSTATS_FILE "files/mapStats.csv"

const int VALOR_ALIMENTO_FUEGO = 15;
const int VALOR_ALIMENTO_TIERRA = 8;
const int VALOR_ALIMENTO_AGUA = 10;

enum terrains
{
	none,
	lake,
	volcano,
	cliff,
	mountain,
	path,
	empty
};
enum elements
{
	EARTH = 1,
	FIRE = 2,
	WATER = 3,
	AIR = 4
};

using namespace std;

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <fstream>
#include <iostream>
#include <math.h>
#include <string.h>
#include <sstream>
#include <regex>
#include <vector>
#include <unistd.h>
#include <chrono>
#include <thread>

#include "../lib/Character.h"

#include "../lib/WaterCharacter.h"
#include "../lib/EarthCharacter.h"
#include "../lib/FireCharacter.h"
#include "../lib/AirCharacter.h"

#include "../lib/Node.h"
#include "../lib/List.h"

#include "../lib/Menu.h"

#include "../lib/GameCell.h"
#include "../lib/GameWorld.h"

#include "../lib/VectorNode.h"
#include "../lib/Stack.h"

#include "utils/utils.h"

#endif /* MAIN_H_ */
