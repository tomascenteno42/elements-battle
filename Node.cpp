/*
 * Node.cpp
 *
 *  Created on: Jan 21, 2021
 *      Author: a-perez-l
 */

#include "src/main.h"

Node::Node(Data d) {
	this -> data = d;
	this -> next = 0;
}

void Node::setData(Data d) {
	this -> data = d;
}

void Node::setNext(Node* s) {
	this -> next = s;
}

Data Node::getData() {
	return this -> data;
}

Node* Node::getNext() {
	return this -> next;
}

Node::~Node() {

}
