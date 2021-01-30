#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include "../../src/main.h"

class List
{
private:
    Node *firstNode = 0;
    Node *currentNode = 0;
    int quantity;

public:
    /**
       Creates empty List.
    */
    List();
    List(const List &L);            // copy constructor
    List &operator=(const List &L); // assignment

    /**
     * Inserts d in pos and increments quantity by 1.
     * @param d Data of type Type to be added.
     * @param pos Position where d will be inserted. MUST BE HIGHER OR EQUAL THAN 1.
    */
    void add(Type d, int index);

    /**
     * Drops element in position pos.
     * @param pos Position in list that will be erased. MUST BE HIGHER OR EQUAL THAN 1.
    */
    void drop(int index);

    /**
     * Consultate element in position pos of list.
     * @param pos Position to consultate. MUST BE HIGHER OR EQUAL THAN 1.
     * @return Type (Character*) of position pos.
    */
    Type get(int index);

    /**
     * Check if List is empty.
     * @return whether the list is empty or not.
    */
    bool isEmpty();

    /**
     * Cleanses the List.
    */
    virtual ~List();

    /**
     * @return List quantity of elements.
    */
    int getQuantity();

    /**
     * Resets currentNode to first position or null if empty List.
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
    Type getNext();

private:
    /**
     * Looks for node in position pos.
     * @param index Position to look for a node.
     * @return Node in position pos.
    */
    Node *getNode(int index);
};

#endif
