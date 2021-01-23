#include "../src/main.h"

Node::Node(Type d)
{
    data = d;
    nextNode = 0;
}

void Node::setData(Type d)
{
    data = d;
}

void Node::setNextNode(Node *s)
{
    nextNode = s;
}

Type Node::getData()
{
    return data;
}

Node *Node::getNextNode()
{
    return nextNode;
}
