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

enum elements
{
	water,
	fire,
	earth,
	air
};

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

using namespace std;

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <fstream>
#include <iostream>
#include <math.h>
#include <string.h>
#include <sstream>

#include "../lib/GameCell.h"
#include "../lib/GameWorld.h"
#include "../lib/VectorNode.h"
#include "../lib/Stack.h"

#include "utils/utils.h"

#include <unistd.h>
#include <chrono>
#include <thread>

#endif /* MAIN_H_ */
