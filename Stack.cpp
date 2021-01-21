/*
 * stack.cpp
 *
 *  Created on: Jan 21, 2021
 *      Author: a-perez-l
 */

#include "src/main.h"

Stack::Stack() {
	this -> last = 0;
}

void Stack::push(Data d) {
	Node* aux = new Node(d);
	aux -> setNext(this -> last);
	this -> last = aux;
}

void Stack::pop() {
	Node* borrar = this -> last;
	this -> last = borrar -> getNext();
	delete borrar;
}

Data Stack::peek() {
	return this -> last -> getData();
}

bool Stack::isEmpty() {
	return (this -> last == 0);
}

Stack::~Stack() {
	while (! this -> isEmpty()) {
		this -> pop();
	}
}
