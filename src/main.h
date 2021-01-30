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

#include "../lib/Characters/Character.h"

#include "../lib/Characters/WaterCharacter.h"
#include "../lib/Characters/EarthCharacter.h"
#include "../lib/Characters/FireCharacter.h"
#include "../lib/Characters/AirCharacter.h"

#include "../lib/DataStructures/Node.h"
#include "../lib/DataStructures/GenericNode.h"
#include "../lib/DataStructures/List.h"
#include "../lib/DataStructures/GenericList.h"

#include "../lib/Window/Menu.h"
#include "../lib/Window/textBox.h"
#include "../lib/Window/Cell.h"

#include "../lib/Window/GameStats.h"
#include "../lib/Window/GameMenu.h"

#include "../lib/GameCells/GameCell.h"
#include "../lib/Window/GameWorld.h"

#include "../lib/DataStructures/Stack.h"

#include "../lib/Window/GameWindow.h"
#include "utils/utils.h"

#include "../lib/GameCells/LakeCell.h"
#include "../lib/GameCells/VolcanoCell.h"
#include "../lib/GameCells/CliffCell.h"
#include "../lib/GameCells/MountainCell.h"
#include "../lib/GameCells/PathCell.h"
#include "../lib/GameCells/EmptyCell.h"

#endif /* MAIN_H_ */
