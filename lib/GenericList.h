#ifndef GENERICLIST_H_
#define GENERICLIST_H_

#include "../src/main.h"

template <class T>
class GenericNode;

template <class T>
class GenericList
{
private:
    GenericNode<T> *firstNode = 0;
    GenericNode<T> *currentNode = 0;
    int quantity;

public:
    /**
       Creates empty GenericList.
    */
    GenericList();
    // GenericList(const GenericNode<T> &L);               // copy constructor
    // GenericNode<T> &operator=(const GenericNode<T> &L); // assignment

    /**
     * Inserts d in pos and increments quantity by 1.
     * @param d Data of type T to be added.
     * @param pos Position where d will be inserted. MUST BE HIGHER OR EQUAL THAN 1.
    */
    void add(T d, int index);

    /**
     * Drops element in position pos.
     * @param pos Position in GenericList that will be erased. MUST BE HIGHER OR EQUAL THAN 1.
    */
    void drop(int index);

    /**
     * Consultate element in position pos of GenericList.
     * @param pos Position to consultate. MUST BE HIGHER OR EQUAL THAN 1.
     * @return T (Character*) of position pos.
    */
    T get(int index);

    /**
     * Check if GenericList is empty.
     * @return whether the GenericList is empty or not.
    */
    bool isEmpty();

    /**
     * Cleanses the GenericList.
    */
    virtual ~GenericList();

    /**
     * @return GenericList quantity of elements.
    */
    int getQuantity();

    /**
     * Resets currentNode to first position or null if empty GenericList.
    */
    void reset();

    /**
     * Checks if there is a node next to currentNode.
     * @return true if currentNode aims to something that is not null. 
    */
    bool nextNodeExist();

    /**
     * Looks and returns currentNode aimed element if currentNode doesn't aim to null.
     * @return currentNode
    */
    T getNext();

private:
    /**
     * Looks for node in position pos.
     * @param index Position to look for a node.
     * @return Node in position pos.
    */
    GenericNode<T> *getNode(int index);
};

// IMPLEMENTATION

template <class T>
GenericList<T>::GenericList()
{
    firstNode = 0;
    currentNode = 0;
    int quantity = 0;
}
template <class T>
bool GenericList<T>::isEmpty()
{
    return (quantity == 0);
}
template <class T>
void GenericList<T>::add(T d, int index)
{
    GenericNode<T> *nuevo = new GenericNode<T>(d);
    if (index == 1)
    {
        nuevo->setNextNode(firstNode);
        firstNode = nuevo;
        reset();
    }
    else
    {
        GenericNode<T> *anterior = getNode(index - 1);
        GenericNode<T> *siguiente = anterior->getNextNode();
        nuevo->setNextNode(siguiente);
        anterior->setNextNode(nuevo);
    }
    quantity++;
}

template <class T>
GenericNode<T> *GenericList<T>::getNode(int index)
{
    GenericNode<T> *aux = firstNode;
    for (int i = 1; i < index; i++)
        aux = aux->getNextNode();
    return aux;
}

template <class T>
T GenericList<T>::get(int index)
{
    GenericNode<T> *aux = getNode(index);
    return aux->getData();
}

template <class T>
void GenericList<T>::drop(int index)
{

    GenericNode<T> *borrar;

    if (index == 1)
    {
        borrar = firstNode;

        delete get(index);
        firstNode = borrar->getNextNode();
    }
    else
    {
        GenericNode<T> *anterior = getNode(index - 1);
        borrar = anterior->getNextNode();

        delete get(index);

        GenericNode<T> *siguiente = borrar->getNextNode();
        anterior->setNextNode(siguiente);
    }
    reset();
    delete borrar;
    quantity--;
}
template <class T>
GenericList<T>::~GenericList<T>()
{
    while (!isEmpty())
    {
        drop(1);
    }
}
template <class T>
int GenericList<T>::getQuantity()
{
    return quantity;
}
template <class T>
void GenericList<T>::reset()
{
    currentNode = firstNode;
}
template <class T>
bool GenericList<T>::nextNodeExist()
{
    return (currentNode != 0);
}
template <class T>
T GenericList<T>::getNext()
{
    GenericNode<T> *aux = currentNode;
    currentNode = currentNode->getNextNode();
    return aux->getData();
}

#endif
