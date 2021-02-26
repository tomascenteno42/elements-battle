#ifndef UTILS_H_
#define UTILS_H_

#include "../main.h"

// ------------------------------------------------------------ MISC
/*
 * Creates a new character using dynamic memory and returns a pointer to it
 * The type of character created depends on the element parameter
 * 
 */
Character* createNewCharacter(elements element, std::string name, float maxLife, int shield);

/*
 * Checks whether the data parameter is contained withing the vector parameter
 */
bool dataIsInVector(std::vector<int> vector, int data);


// ----------------------------------------------------------- FILES
/*
 * Opens file located in path. In case the file was not found, a new one is created and opened
 */
void openFile(string path, fstream& file);

/*
 * Reads character data from a file and creates Character objects accordingly
 * These are then inserted into the characterMap
 */
void loadCharacterData(BST<string, Character*>* characterMap);

/*
 * Reads map data from a file and creates GameCell objects accordingly
 * These are then inserted into the GameWorld's tiles graph
 */
void loadMapData(GameWorld* world);

/*
 * Reads game data from a file, loading an existing game in the exact same
 * conditions it was saved in
 */
void loadGameData(fstream& file, GameWorld* world, BST<string, Character*>* characterMap);

/*
 * Saves the game's current state to a file
 */
void saveGameData(GameWorld* world);

/*
 * Saves changes made to the character database (character additions/deletions) to the character file
 */
void saveChangesToCharFile(BST<string, Character*>* characterMap);


// ------------------------------------------------ USER INTERACTION
/*
 * Polls for events on the window and once the ENTER key is pressed,
 * it returns the string that the user entered
 */
std::string getUserInput(GameWindow* window);

/*
 * Asks for user input until they enter a valid character element
 * Returns a string representing said element
 */
std::string getCharElementFromUser(GameMenu* menu);

/*
 * Asks for user input until they enter a valid character name
 * Returns a string representing said name
 */
std::string getCharNameFromUser(GameMenu* menu, BST<string, Character*>* characterMap);

/*
 * Asks for user input until they enter a valid character life
 * Returns a string representing said life
 */
std::string getCharLifeFromUser(GameMenu* menu);

/*
 * Asks for user input until they enter a valid character shield
 * Returns a string representing said shield
 */
std::string getCharShieldFromUser(GameMenu* menu);

/*
 * Asks for user input until they enter a valid position
 * Returns an sf::Vector2f representing said position
 */
sf::Vector2f getPositionFromUser(GameMenu* menu);

/*
 * Asks for user input until they enter a valid destination, checking for occupied
 * state and required energy.
 * Returns an sf::Vector2f representing said destination
 */
sf::Vector2f getDestinationFromUser(GameMenu* menu);


// ------------------------------------------------------ MENU UTILS
/*
 * Retrieves options from OPTIONS_FILE and fills the Menu object
 */
void fillMenu(Menu* menu, const char* filename);

/*
 * Requests character data from the user, creates a new character from said data,
 * and adds the character to characterMap
 */
void processAddCharacter(GameMenu* menu, BST<string, Character*>* characterMap);

/*
 * Requests a character name from the user and deletes the character with that
 * name from characterMap in case it exists.
 */
void processDeleteCharacter(GameMenu* menu, BST<string, Character*>* characterMap);

/*
 * Requests a character name from the user and displays its details on screen,
 * in case it exists
 */
void processSearchCharacter(GameMenu* menu, BST<string, Character*>* characterMap);

/*
 * Displays a list of all the characters' names on the screen
 */
void processShowCharacters(GameMenu* menu, BST<string, Character*>* characterMap);

/*
 * Requests a character name from the user and, in case of it being a valid character,
 * it is added to the current player's characters. The current player depends on how
 * many characters have been selected so far
 */
void processCharacterSelection(GameMenu* menu, BST<string, Character*>* characterMap);

/*
 * Starting from any player out of the 2 randomly, it requests the player to position their
 * first character. Then it does the same with the other player. Repeats until both players
 * have positioned all their characters
 */
void processCharacterPositioning(GameMenu* menu);

/*
 * Sets game state to the one specified by the save file.
 * If there is no saved game, it loads a brand new game.
 */
void processLoadGame(GameMenu* menu, BST<string, Character*>* characterMap);

/*
 * Saves game data to a file and exits to main menu, if saving is available at the time
 */
void processSaveGame(GameMenu* menu);

/*
 * Calls feed method on current character and advances to next menu,
 * unless the character's element is air
 */
void processFeedOption(GameMenu* menu);

/*
 * Requests position from user and calls move method on current character,
 * then it advances to the next menu
 */
void processMoveOption(GameMenu* menu);

/*
 * Calls attack method on current character
 */
void processAttackOption(GameMenu* menu);

/*
 * Calls defense method on current character
 */
void processDefenseOption(GameMenu* menu);

/*
 * Deletes save file, displays winner text on screen and returns to main menu
 */
void endGame(GameMenu* menu);

/*
 * Calculates amount of lines(options) in OPTIONS_FILE.
 */
int getAmountOfOptions(const char* filename);


// --------------------------------------------------------- PARSERS
/*
 * Takes a string and returns the correponding element to that string
 * (case un-sensitive)
 */
elements parseStringToElement(std::string stringToParse);

/*
 * Takes an element and returns a string containing that element
 */
std::string parseElementToString(elements element);

/*
 * Takes a string representing a position (it must be already
 * properly formatted) and returns an sf::Vector2f with that position
 */
sf::Vector2f parseStringToVector2f(std::string input);

/*
 * Returns sf::Color correponding to the terrain parameter
 */
sf::Color parseTerrainToSf(terrains terrain);

/*
 * Takes a string and returns the corresponding terrain to that string
 */
terrains parseStringToTerrain(string stringToParse);


// ------------------------------------------------------ VALIDATORS
/*
 * Takes a string and checks whether it is formatted properly (number comma number)
 * validPosition("3,9") returns true
 * validPosition("-3,9") returns false
 * validPosition("39") returns false
 */
bool validPosition(std::string input);

/*
 * Checks whether character has enough energy to move to destination
 */
bool validDestinationEnergy(GameWorld* world, Character* character, sf::Vector2f destination);

/*
 * Checks whether a position is occupied or not
 */
bool positionIsEmpty(GameWorld* world, sf::Vector2f destination);

/*
 * Returns true if both validDestinationEnergy and positionIsEmpty return true
 */
bool validMoveDestination(GameMenu* menu, Character* character, sf::Vector2f destination);

/*
 * Returns true if a string has only numbers
 */
bool stringIsNumeric(std::string s);


// ------------------------------------------------------- MAP UTILS
/*
 * Sets the distances and paths matrixes to their initial states according to the FW Shortest Paths algorithm
 * and the provided element
 */
void setInitialMatrixes(Graph<GameCell*>* tilesGraph, int distances[64][64], sf::Vector2f paths[64][64], elements element);

/*
 * Floyd-Warshall shortest paths algorithm implementation
 */
void shortestPathsFW(GameWorld* world, int distances[64][64], sf::Vector2f paths[64][64], elements element);

/*
 * Loads a stack with the series of consecutive moves a character must perform to arrive to endingPos from startingPos
 * These consecutive moves are between cells that are immediately connected to each other
 */
void loadMovementsStack(Stack<sf::Vector2f>* movStack, sf::Vector2f startingPos, sf::Vector2f endingPos, sf::Vector2f paths[64][64]);

/*
 * Loads distances and paths matrixes for each element
 */
void loadFWMatrixes(GameWorld* world, int distances[4][64][64], sf::Vector2f paths[4][64][64]);

/*
 * Draws stats on screen accordingly
 */
void drawStats(GameWindow* window);

/*
 * Draws all elements on screen accordingly
 */
void drawScreen(GameWindow* window);

#endif