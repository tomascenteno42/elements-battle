#include "../src/main.h"

List::List()
{
    firstNode = 0;
    currentNode = 0;
    quantity = 0;
}

bool List::isEmpty()
{
    return (quantity == 0);
}

void List::add(Type d, int index)
{
    Node *nuevo = new Node(d);
    if (index == 1)
    {
        nuevo->setNextNode(firstNode);
        firstNode = nuevo;
        reset();
    }
    else
    {
        Node *anterior = getNode(index - 1);
        Node *siguiente = anterior->getNextNode();
        nuevo->setNextNode(siguiente);
        anterior->setNextNode(nuevo);
    }
    quantity++;
}

Node *List::getNode(int index)
{
    Node *aux = firstNode;
    for (int i = 1; i < index; i++)
        aux = aux->getNextNode();
    return aux;
}

Type List::get(int index)
{
    Node *aux = getNode(index);
    return aux->getData();
}

void List::drop(int index)
{

    Node *borrar;

    if (index == 1)
    {
        borrar = firstNode;

        delete get(index);
        firstNode = borrar->getNextNode();
    }
    else
    {
        Node *anterior = getNode(index - 1);
        borrar = anterior->getNextNode();

        delete get(index);

        Node *siguiente = borrar->getNextNode();
        anterior->setNextNode(siguiente);
    }
    reset();
    delete borrar;
    quantity--;
}

List::~List()
{
    while (!isEmpty())
    {
        drop(1);
    }
}

int List::getQuantity()
{
    return quantity;
}

void List::reset()
{
    currentNode = firstNode;
}

bool List::nextNodeExist()
{
    return (currentNode != 0);
}

Type List::getNext()
{
    Node *aux = currentNode;
    currentNode = currentNode->getNextNode();
    return aux->getData();
}
