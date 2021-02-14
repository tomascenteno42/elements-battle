#ifndef NODO_H_
#define NODO_H_

#include "../../src/main.h"

template <class K, class T>
class BSTNode {

private:
	// Atributos
	K key;
	T data;
	BSTNode<K,T>* right;
	BSTNode<K,T>* left;
	BSTNode<K,T>* parent;

public:
	// Metodos
	BSTNode(K key, T data);

	void setData(T data);
	void setKey(K key);
	T getData();
	K getKey();

	void setRight(BSTNode<K,T>* right);
	BSTNode<K,T>* getRight();

	void setLeft(BSTNode<K,T>* left);
	BSTNode<K,T>* getLeft();

	void setParent(BSTNode<K,T>* parent);
	BSTNode<K,T>* getParent();

	bool isLeaf();
	bool onlyRight();
	bool onlyLeft();

	~BSTNode();
};

// -------------- IMPLEMENTATION -----------------

template <class K, class T>
BSTNode<K,T>::BSTNode(K key, T data)
{
	this -> data = data;
	this -> key = key;
	this -> right = 0;
	this -> left = 0;
	this -> parent = 0;
}

template <class K, class T>
void BSTNode<K,T>::setData(T data)
{
	this -> data = data;
}

template <class K, class T>
void BSTNode<K,T>::setKey(K key)
{
	this -> key = key;
}

template <class K, class T>
T BSTNode<K,T>::getData()
{
	return data;
}


template <class K, class T>
K BSTNode<K,T>::getKey()
{
	return key;
}


template <class K, class T>
void BSTNode<K,T>::setLeft(BSTNode<K,T>* left)
{
	this -> left = left;
  
	if (left)
    left -> setParent(this);
}


template <class K, class T>
BSTNode<K,T>* BSTNode<K,T>::getLeft()
{
	return this -> left;
}


template <class K, class T>
void BSTNode<K,T>::setRight(BSTNode<K,T>* right)
{
	this -> right = right;

	if (right)
    right -> setParent(this);
}

template <class K, class T>
BSTNode<K,T>* BSTNode<K,T>::getRight()
{
	return right;
}


template <class K, class T>
void BSTNode<K,T>::setParent(BSTNode<K,T>* parent)
{
	this -> parent = parent;
}


template <class K, class T>
BSTNode<K,T>* BSTNode<K,T>::getParent()
{
	return parent;
}


template <class K, class T>
bool BSTNode<K,T>::isLeaf()
{
	return (getLeft() == 0 && getRight() == 0);
}


template <class K, class T>
bool BSTNode<K,T>::onlyRight()
{
	return (getLeft() == 0 && getRight() != 0);
}


template <class K, class T>
bool BSTNode<K,T>::onlyLeft()
{
	return (getLeft() != 0 && getRight() == 0);
}


template <class K, class T>
BSTNode<K,T>::~BSTNode()
{
	delete data;
}

#endif /* NODO_H_ */
