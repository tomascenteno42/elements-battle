/*
 * utils.h
 *
 *  Created on: Jan 18, 2021
 *      Author: kurepa
 */

#ifndef UTILS_UTILS_H_
#define UTILS_UTILS_H_

#include "../main.h"
#include "../../GameWorld.h"

terrains parseStringToTerrain(std::string colorToParse);
sf::Color parseTerrainToSf(terrains terrain);

/*
 * Setea dos matrices (distances y paths) que van a ser tomadas por el algoritmo de caminos mínimos.
 * Una matriz es la de distancias, la otra de recorridos. Por ahora solo estoy seteando la de distancias.
 * La matriz de recorridos no sé cuales tendrían que ser sus elementos ¿GameCell, GameCell*, string, vector con la posicion?
 * La matriz de distancias es de dimension cantidadNodos x cantidadNodos.
 * distancias[i][j] = coste de ir del nodo i al nodo j (en un solo movimiento).
 * Si no se puede llegar en un solo movimiento, se pone distancia "infinita" (100 por ahora para ver nomas).
 */
void setInitialMatrixes(GameWorld world, int distances[64][64], sf::Vector2f paths[64][64], elements element);

/*
 * Determina si dos celdas rectangulares son adyacentes horizontal o verticalmente
 * (Seguro hay una mejor manera de hacerlo usando la biblioteca, por ahora lo hice asi para ir probando).
 */
bool intersects (sf::RectangleShape cell1, sf::RectangleShape cell2);

void shortestPathsFW(GameWorld world, int distances[64][64], sf::Vector2f paths[64][64], elements element);

#endif /* UTILS_UTILS_H_ */
