/*
 * main.h
 *
 *  Created on: Jan 18, 2021
 *      Author: kurepa
 */

#ifndef MAIN_H_
#define MAIN_H_

enum elements {
	water,
	fire,
	earth,
	air
};

enum terrains {
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

#include "utils/utils.h"
#include "../GameCell.h"
#include "../GameWorld.h"




#endif /* MAIN_H_ */
