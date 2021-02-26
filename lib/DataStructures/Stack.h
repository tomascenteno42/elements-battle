#ifndef STACK_H_
#define STACK_H_

#include "../../src/main.h"

template <class T>
class GenericNode;

template <class T>
class Stack
{

private:
	GenericNode<T>* last;

public:
	Stack();

	void push(T d);
	void pop();
	T peek();
	bool isEmpty();

	virtual ~Stack();
};

// IMPLEMENTATION

template <class T>
Stack<T>::Stack()
{
	this->last = 0;
}

template <class T>
void Stack<T>::push(T d)
{
	GenericNode<T>* aux = new GenericNode<T>(d);
	aux->setNextNode(this->last);
	this->last = aux;
}

template <class T>
void Stack<T>::pop()
{
	GenericNode<T>* aux = this->last;
	this->last = aux->getNextNode();
	delete aux;
}

template <class T>
T Stack<T>::peek()
{
	return this->last->getData();
}

template <class T>
bool Stack<T>::isEmpty()
{
	return (this->last == 0);
}

template <class T>
Stack<T>::~Stack()
{
	while (!this->isEmpty())
	{
		this->pop();
	}
}

#endif /* STACK_H_ */
