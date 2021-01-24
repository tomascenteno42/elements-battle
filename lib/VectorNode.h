/*
 * Node.h
 *
 *  Created on: Jan 21, 2021
 *      Author: a-perez-l
 */

#ifndef VECTOR_NODE_H_
#define VECTOR_NODE_H_

#include "../src/main.h"

typedef sf::Vector2f Data;

class VectorNode
{

private:
	Data data;
	VectorNode *next;

public:
	VectorNode(Data d);

	void setData(Data d);
	void setNext(VectorNode *s);
	Data getData();
	VectorNode *getNext();

	virtual ~VectorNode();
};

#endif /* VECTOR_NODE_H_ */
