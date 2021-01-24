#include "../src/main.h"

Stack::Stack()
{
	this->last = 0;
}

void Stack::push(Data d)
{
	VectorNode *aux = new VectorNode(d);
	aux->setNext(this->last);
	this->last = aux;
}

void Stack::pop()
{
	VectorNode *borrar = this->last;
	this->last = borrar->getNext();
	delete borrar;
}

Data Stack::peek()
{
	return this->last->getData();
}

bool Stack::isEmpty()
{
	return (this->last == 0);
}

Stack::~Stack()
{
	while (!this->isEmpty())
	{
		this->pop();
	}
}
