/*
 * stack.h
 *
 *  Created on: Jan 21, 2021
 *      Author: a-perez-l
 */

#ifndef STACK_H_
#define STACK_H_

#include "../src/main.h"

class Stack
{

private:
	VectorNode *last;

public:
	Stack();

	void push(Data d);
	void pop();
	Data peek();
	bool isEmpty();

	virtual ~Stack();
};

#endif /* STACK_H_ */
