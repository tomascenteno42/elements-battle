/*
 * VectorNode.cpp
 *
 *  Created on: Jan 21, 2021
 *      Author: a-perez-l
 */

#include "../src/main.h"

VectorNode::VectorNode(Data d)
{
	this->data = d;
	this->next = 0;
}

void VectorNode::setData(Data d)
{
	this->data = d;
}

void VectorNode::setNext(VectorNode *s)
{
	this->next = s;
}

Data VectorNode::getData()
{
	return this->data;
}

VectorNode *VectorNode::getNext()
{
	return this->next;
}

VectorNode::~VectorNode()
{
}
