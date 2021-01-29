#ifndef GENERICNODE_H_INCLUDED
#define GENERICNODE_H_INCLUDED

#include "../src/main.h"

template <class T>
class GenericNode
{
private:
    T *data;
    GenericNode<T> *nextNode = 0;

public:
    GenericNode(T d);

    void setData(T d);

    void setNextNode(GenericNode<T> *n);

    T getData();

    GenericNode<T> *getNextNode();
};

// IMPLEMENTATION

template <class T>
GenericNode<T>::GenericNode(T d)
{
    data = d;
    nextNode = 0;
}

template <class T>
void GenericNode<T>::setData(T d)
{
    data = d;
}
template <class T>
void GenericNode<T>::setNextNode(GenericNode<T> *gn)
{
    nextNode = gn;
}

template <class T>
T GenericNode<T>::getData()
{
    return data;
}

template <class T>
GenericNode<T> *GenericNode<T>::getNextNode()
{
    return nextNode;
};
#endif