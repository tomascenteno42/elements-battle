#ifndef UTILS_H_
#define UTILS_H_

#include "../main.h"

/* MENU */

/**
   Retrieves options from OPTIONS_FILE and fills the Menu object
   @param m Object menu.
*/
void fillMenu(Menu *m);

/**
    Nucleus of menu logic, it renders menu options.
    @param m Menu object.
    @param l List object.
*/
void renderMenu(Menu *m, List *l);

/**
   Renders the user options choice.
   @param l List object.
   @param option Option to execute.
*/
void renderMenuOption(List *l, int option);

/**
    Display through terminal the options inside Menu object.
    @param m Menu object.
*/
void showMenuOptions(Menu *m);

/**
    Calculates amount of lines(options) in OPTIONS_FILE.
    @return Amount of options (int).
*/
int getAmountOfOptions();

/**
   Stores and returns user options choice.
   @return User choice as integer.
*/
int getUserChoice();

/**
   Validates user choice to be in between of menu length and 1.  
   It shows ui incorrect untils it is correct. 
   @param option Options passed by reference.
   @param menuLength Amount of options that Menu object contain.
*/
void validateUserChoice(int &option, int menuLength);

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

/* UTILS */

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
   Throws an error message in screen when a character with a specific name was not found.
*/
void notFoundCharacterNameError();

/**
 * Makes terminal stop and wait for user to enter a character, displaying this information.
*/
void waitForEnter();

/**
 * Cleans the terminal.
*/
void clearScreen();

/**
 * Renders "WELCOME TO BATTLE OF THE ELEMENTS".
*/
void renderGameTitle();

/**
 * Prints a blank linea in terminal
*/
void printBlankLine();

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

/*
 * Setea dos matrices (distances y paths) que van a ser tomadas por el algoritmo de caminos mínimos.
 * Una matriz es la de distancias, la otra de recorridos. Por ahora solo estoy seteando la de distancias.
 * La matriz de recorridos no sé cuales tendrían que ser sus elementos ¿GameCell, GameCell*, string, vector con la posicion?
 * La matriz de distancias es de dimension cantidadNodos x cantidadNodos.
 * distancias[i][j] = coste de ir del nodo i al nodo j (en un solo movimiento).
 * Si no se puede llegar en un solo movimiento, se pone distancia "infinita" (100 por ahora para ver nomas).
 */
void setInitialMatrixes(GameWorld *world, int distances[64][64], sf::Vector2f paths[64][64], elements element);

/*
 * Determina si dos celdas rectangulares son adyacentes horizontal o verticalmente
 * (Seguro hay una mejor manera de hacerlo usando la biblioteca, por ahora lo hice asi para ir probando).
 */
bool intersects(sf::RectangleShape cell1, sf::RectangleShape cell2);

/*
 * Implementación del algoritmo de FloydWarshall
 */
void shortestPathsFW(GameWorld *world, int distances[64][64], sf::Vector2f paths[64][64], elements element);

void printDistances(int distances[64][64]);
void printPaths(sf::Vector2f paths[64][64]);

/*
 * Carga en una pila la serie de celdas adyacentes a las que el personaje se tiene que ir moviendo para llegar
 * de startingPos a endingPos
 */
void loadMovementsStack(Stack *movStack, sf::Vector2f startingPos, sf::Vector2f endingPos, sf::Vector2f paths[64][64]);

sf::Vector2f askDestination();
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