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
#define OPTIONS_FILE_2 "files/options2.txt"
#define CHARACTERS_FILE "files/characters.csv"
#define MAPSTATS_FILE "files/mapStats.csv"

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

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
#include "../lib/GenericNode.h"
#include "../lib/List.h"
#include "../lib/GenericList.h"

#include "../lib/Menu.h"
#include "../lib/textBox.h"
#include "../lib/Cell.h"

#include "../lib/GameStats.h"
#include "../lib/GameMenu.h"

#include "../lib/GameCell.h"
#include "../lib/GameWorld.h"

#include "../lib/Stack.h"

#include "../lib/GameWindow.h"
#include "utils/utils.h"

#include "../lib/LakeCell.h"
#include "../lib/VolcanoCell.h"
#include "../lib/CliffCell.h"
#include "../lib/MountainCell.h"
#include "../lib/PathCell.h"
#include "../lib/EmptyCell.h"

#endif /* MAIN_H_ */
