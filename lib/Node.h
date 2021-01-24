#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include "../src/main.h"

typedef Character *Type;

class Node
{
private:
    Type data;
    Node *nextNode = 0;

public:
    /**
        Creates a Node with data = d and nextNode as a null pointer.
        @param d Desired value for a new Node.
    */
    Node(Type d);

    void setData(Type d);

    void setNextNode(Node *n);

    Type getData();

    Node *getNextNode();
};

#endif