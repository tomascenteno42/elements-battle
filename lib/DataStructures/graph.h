
#ifndef GRAPH_H
#define GRAPH_H

#include "../../src/main.h"

using namespace std;

template <class T>
class GraphData {
public:
    T data;
    int cost;
    vector<int> adjList;
};

template <class T>
class Graph
{
private:
    int vertices;
    GenericList<GraphData<T>*> *head;      // GenericList<GraphData>
    GenericNode<GraphData<T>*> *current;   // GenericNode<GraphData>

public:
    // CONSTRUCTOR
    Graph(int v);
    
    // Fills index node
    void fillNode(T data, int cost, int index);

    // Links two nodes
    void addEdge(int from, int to); // A -> B

    // Returns number of vertices
    int getVertices();

    // Gets data from node in pos
    GraphData<T>* getData(int pos);

    void printGraph();    // Test Purposes

    // DESTRUCTOR
    ~Graph();
};

// IMPLEMENTACION

template <class T>
Graph<T>::Graph(int v) 
{
    vertices = v;
    head = new GenericList<GraphData<T>*>;
    current = 0;

    for (size_t i = 0; i < vertices; i++)
    {
        GraphData<T> *nodeData = new GraphData<T>();

        if (head->isEmpty())
            head->add(nodeData, 1);
        else
            head->add(nodeData, head->getQuantity() + 1);
    }
}

template <class T> 
void Graph<T>::fillNode(T data, int cost, int index)
{
    if (index <= vertices && index > 0 && head->get(index) != 0)
    {
        GraphData<T> *graphdata = head->get(index);
        graphdata->cost = cost;
        graphdata->data = data;
    }
    else
        cout << "FILL NODE ERROR" << endl;
}

template <class T>
void Graph<T>::addEdge(int A, int B)
{
    if (A <= vertices && A > 0 && B <= vertices && B > 0 && A != B && head->get(A) != 0 && head->get(A) != 0)
    {
        GraphData<T> *graphdata; 
    
        graphdata = head->get(A);
        graphdata->adjList.push_back(B);

        graphdata = head->get(B);
        graphdata->adjList.push_back(A);/* code */
    }
    else
        cout << "ADD EDGE ERROR" << endl;
}

template <class T> 
int Graph<T>::getVertices()
{
    return vertices;
}

template <class T>
GraphData<T>* Graph<T>::getData(int pos)
{
    if (pos <= vertices && pos > 0 && head->get(pos) != 0)
        return head->get(pos);
    else
    {
        cout << "GETDATA ERROR" << endl;
        return 0;
    }
}

template <class T>
void Graph<T>::printGraph()
{
    GraphData<T> *graphdata;
    
    for (size_t i = 0; i < vertices; i++)
    {
        graphdata = head->get(i+1);
        cout << "NODO " << i+1 << endl;
        cout << "Data: " << *(graphdata->data) << endl;
        cout << "Cost: " << graphdata->cost << endl;
        cout << "Linked to: ";
        for (size_t i = 0; i < graphdata->adjList.size(); i++)
            cout << graphdata->adjList[i] << ",";
        cout << endl << endl;
    }
}

template <class T>
Graph<T>::~Graph()
{  
    for (size_t i = 0; i < vertices; i++)
        delete getData(i+1)->data;
    delete head;
}

#endif