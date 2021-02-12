#ifndef UTILS_H_
#define UTILS_H_

#include "../main.h"

void loadNewGame(GameWorld* world);

// ----------------------------------------------------------- FILES
void openFile(string path, fstream& file);
void loadCharacterData();
void loadMapData(GameWorld* world);
void loadGameData(fstream& file, GameWorld* world);
void saveGameData(GameWorld* world);
Character* createNewCharacterFromStrings(std::string elementStr, std::string name, std::string maxLifeStr, std::string shieldStr);

// ------------------------------------------------ USER INTERACTION

std::string getUserInput(GameWindow* window);
sf::Vector2f getPositionFromUser(GameMenu* menu);
sf::Vector2f getDestinationFromUser(GameMenu* menu);


// ------------------------------------------------------ MENU UTILS

/**
   Retrieves options from OPTIONS_FILE and fills the Menu object
   @param m Object menu.
   @param filename file name.
*/
void fillMenu(Menu *m, const char* filename);
void processAddCharacter(GameMenu *menu);
void processDeleteCharacter(GameMenu *menu);
void processSearchCharacter(GameMenu *menu);
void processShowCharacters(GameMenu *menu);
void processSelectCharacter(GameMenu* menu);
void processPlaceCharacters(GameMenu* menu);
void processLoadGame(GameMenu*menu);
void processSaveGame(GameMenu *menu);
void processFeedOption(GameMenu *menu);
void processMoveOption(GameMenu *menu);
void processAttackOption(GameMenu *menu);
void processDefenseOption(GameMenu *menu);

void endGame(GameMenu *menu);

/**
    Calculates amount of lines(options) in OPTIONS_FILE.
    @return Amount of options (int).
    @param filename optionsfile.txt.
*/
int getAmountOfOptions(const char* filename);


// --------------------------------------------------------- PARSERS

/**
 *  Parser from string to Element(default EARTH).
    @param e character element to parse to integer.
    @return elements(integer).
*/
elements parseStringToElement(std::string stringToParse);
std::string parseElementToString(elements element);

sf::Vector2f parseStringToVector2f(std::string input);

/**
 * Parse from terrains enum to SFML Color class.
 * @param terrain terrain from terrains enum to parse.
 * @return sf::Color
*/
sf::Color parseTerrainToSf(terrains terrain);

terrains parseStringToTerrain(string stringToParse);


// ------------------------------------------------------ VALIDATORS

bool validPosition(std::string input);
bool validDestinationEnergy(GameWorld *world, Character *character, sf::Vector2f destination);
bool positionIsEmpty(GameWorld *world, sf::Vector2f destination);
bool validMoveDestination(GameMenu* menu, Character* character, sf::Vector2f destination);
bool stringIsNumeric(std::string s);


// ------------------------------------------------------- MAP UTILS

/*
 * Sets the distances and paths matrixes to their initial state according to the FW Shortest Paths algorithm.
 */
void setInitialMatrixes(GameWorld *world, int distances[64][64], sf::Vector2f paths[64][64], elements element);

/*
 * Determines whether two cells share an edge. (If two cells share only a corner, it returns false)
 */
bool intersects(sf::RectangleShape cell1, sf::RectangleShape cell2);

/*
 * Floyd-Warshall shortest paths algorithm implementation
 */
void shortestPathsFW(GameWorld *world, int distances[64][64], sf::Vector2f paths[64][64], elements element);

/*
 * Loads a stack with the series of consecutive moves a character must perform to arrive to endingPos from startingPos
 * These consecutive moves are unitary i.e. both cells intersect according to the intersects funcion
 */
void loadMovementsStack(Stack<sf::Vector2f> *movStack, sf::Vector2f startingPos, sf::Vector2f endingPos, sf::Vector2f paths[64][64]);

/*
 * Loads distances and paths matrixes for each element
 */
void loadFWMatrixes(GameWorld *world, int distances[4][64][64], sf::Vector2f paths[4][64][64]);

void drawStats(GameWindow *win);
void drawScreen(GameWindow *win);

#endif