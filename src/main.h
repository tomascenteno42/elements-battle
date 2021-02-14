/*
 * main.h
 *
 *  Created on: Jan 18, 2021
 *      Author: kurepa
 */

#ifndef MAIN_H_
#define MAIN_H_

#define FONT_FILE "files/arial.ttf"
#define OPTIONS_FILE_1 "files/options1.txt"
#define OPTIONS_FILE_2 "files/options2.txt"
#define OPTIONS_FILE_3 "files/options3.txt"
#define OPTIONS_FILE_4 "files/options4.txt"
#define CHARACTERS_FILE "files/characters.csv"
#define MAPSTATS_FILE "files/mapStats.csv"
#define SAVE_FILE "files/partida.csv"

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

const int VALOR_ALIMENTO_FUEGO = 5;
const int VALOR_ALIMENTO_TIERRA = 8;
const int VALOR_ALIMENTO_AGUA = 10;

enum menus
{
	mainMenu = 1,
	charSelectionMenu,
	gameMenu1,
	gameMenu2
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
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <sstream>
#include <regex>
#include <vector>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <algorithm>
#include <cctype>

#include "../lib/Characters/Character.h"

#include "../lib/Characters/WaterCharacter.h"
#include "../lib/Characters/EarthCharacter.h"
#include "../lib/Characters/FireCharacter.h"
#include "../lib/Characters/AirCharacter.h"

#include "../lib/DataStructures/GenericNode.h"
#include "../lib/DataStructures/GenericList.h"
#include "../lib/DataStructures/Stack.h"
#include "../lib/DataStructures/BSTNode.h"
#include "../lib/DataStructures/BST.h"
#include "../lib/DataStructures/Graph.h"

#include "../lib/Window/Menu.h"
#include "../lib/Window/textBox.h"
#include "../lib/Window/Cell.h"
#include "../lib/Window/Player.h"
#include "../lib/GameCells/GameCell.h"
#include "../lib/Window/GameWorld.h"
#include "../lib/Window/GameStats.h"
#include "../lib/Window/GameMenu.h"
#include "../lib/Window/GameWindow.h"

#include "utils/utils.h"

#include "../lib/GameCells/LakeCell.h"
#include "../lib/GameCells/VolcanoCell.h"
#include "../lib/GameCells/CliffCell.h"
#include "../lib/GameCells/MountainCell.h"
#include "../lib/GameCells/PathCell.h"
#include "../lib/GameCells/EmptyCell.h"

#endif /* MAIN_H_ */
