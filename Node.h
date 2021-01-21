/*
 * Node.h
 *
 *  Created on: Jan 21, 2021
 *      Author: a-perez-l
 */

#ifndef NODE_H_
#define NODE_H_

#include "src/main.h"

typedef sf::Vector2f Data;

class Node {

private:
	Data data;
	Node* next;

public:
	Node(Data d);

	void setData(Data d);
	void setNext(Node* s);
	Data getData();
	Node* getNext();

	virtual ~Node();
};

#endif /* NODE_H_ */
