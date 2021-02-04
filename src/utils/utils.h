#ifndef UTILS_H_
#define UTILS_H_

#include "../main.h"

/* MENU */

bool stringIsNumeric(std::string s);

/**
   Retrieves options from OPTIONS_FILE and fills the Menu object
   @param m Object menu.
   @param filename file name.
*/
void fillMenu(Menu *m, const char* filename);

/**
    Nucleus of menu logic, it renders menu options.
    @param l List object.
    @param win game window.
*/
void renderMenu(List *l, GameMenu *menu);

void processOptionChoice(GameMenu *menu, int option);
void processUserInput(GameMenu *menu, std::string input);

void preprocessMainMenuOption(GameMenu *menu, int option);
void preprocessCharMenuOption(GameMenu *menu, int option);
void preprocessGameMenu1Option(GameMenu *menu, int option);
void preprocessGameMenu2Option(GameMenu *menu, int option);

void processMainMenuInput(GameMenu *menu, std::string input);
void processCharMenuInput(GameMenu *menu, std::string input);
void processGameMenu1Input(GameMenu *menu, std::string input);
void processGameMenu2Input(GameMenu *menu, std::string input);


/**
    Calculates amount of lines(options) in OPTIONS_FILE.
    @return Amount of options (int).
    @param filename optionsfile.txt.
*/
int getAmountOfOptions(const char* filename);

/* LIST */

/**
    Main logic for retrieving data from CHARACTERS_FILE and makes use of utility functions.
    @param l List object.
 
*/
void fillList(List *l);

/**
    Creates a character object and store it accordingly to its element inside the list.    
    @param l List object where character object will be stored.
    @param index position where to store character object in `l.
    @param line Data array to construct character object.
    @param element character element.
*/
void addCharacterToList(List *l, int index, string line[], string element);

/**
    Reads and return first element of line, (character element).
    @param position starting position for reading an element of the file.
    @return An element of the file.
*/
string getCharacterElementFromFile(int position);

/**
    Reads 3 elements of file. In this case it reads character's name, life and shield from file. It saves this data in data[].
    @param position starting position for reading elements of the file.
    @param data array passed by reference which will store 3 elements.
*/
void getCharacterDataFromFile(int position, string data[]);

/* MENU OPTIONS FUNCTIONALITY */

/**
 * Interacts with user to specify the data for the character that will be added to the list passed by params.
 * @param l List object where an specific character will be added.
*/
void addCharacter(List *l);

/**
 * Interacts with user to specify which user will be removed from the List object and erase it.
 * @param l List object where and specific chracter will be erased.
*/
void eraseCharacter(List *l);

/**
 * Displays all the names of the characters in list passed by params.
 * @param l List object.
*/
void showAllCharactersNames(List *l);

/**
 * Interacts with user to specify which characters the function must show stats of.
 * @param l List object. 
*/
void searchCharacterStats(List *l);

/**
 * Interacts with user to specify which character the user wants to feed. And executes feed functionality according to the implementation of each Character.
 * @param l List object. 
*/
void feedCharacter(List *l);

/* LIST UTILITY FUNCTIONS */

/**
 * Looks for a List index according to a specific name.
 * @param l List object.
 * @param name Name to be looked in list.
 * @return List index. 0 if not found.
*/
int getIndexByCharacterName(List *l, string name);

/**
 * Display characters stats.
 * @param l List object.
 * @param index List object index.
*/
void showCharacterStatsByIndex(List *l, int index);

/**
 * Executes Character feed functionality
 * @param l List object.
 * @param index List object index.
*/
void feedCharacterByIndex(List *l, int index);

// ---------------------------------------------------- PARSERS & VALIDATORS

/**
 *  Parser from string to Element(default EARTH).
    @param e character element to parse to integer.
    @return elements(integer).
*/
elements parseStringToElement(string stringToParse);

/**
 * Parser from Element to string.
 * @param elementToParse element to be parsed to string
 * @return elements as string.
*/
string parseElementToString(elements elementToParse);

/**
 * Validates a string to be 'Air, air, Water, water, Earth, earth, Fire or fire'. 
 * @param element string to be validated.
*/
void validateElement(string &element);

/**
 * Parse given string to terrains enum.
 * @param colorToParse 
 * @return terrains
*/
terrains parseStringToColor(string colorToParse);

/**
 * Parse from terrains enum to SFML Color class.
 * @param terrain terrain from terrains enum to parse.
 * @return sf::Color
*/
sf::Color parseTerrainToSf(terrains terrain);

terrains parseStringToTerrain(string colorToParse);



// ---------------------------------------------------------------- MAP UTILS (& some others)


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

/*
 * Moves the character to the position designated by the top of the movement stack
 */
void moveCharacter(Character *character, Stack<sf::Vector2f> *movStack);

sf::Vector2f askDestination();
void validateDestination(GameWorld *world, Character *character, sf::Vector2f &destination, int &energyRequired);

void drawScreen(GameWindow *win);

void processMoveChoice(Stack<sf::Vector2f> *movStack, GameWindow *win, Character *character);

void processAttackChoice(GameWorld *world, Character *character, vector<Character*> enemyCharacters);

void printStats(GameWorld* world);

// -------------------------------------------------------------------------

/**
 * Generic function for validating file opening.
*/
template <class T>
void validateFile(const T &file, string fileName)
{
    if (!file)
    {
        cout << "Error opening " << fileName;
        exit(1);
    }
};
#endif
