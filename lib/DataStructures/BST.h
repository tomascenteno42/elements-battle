#ifndef ARBOL_H_
#define ARBOL_H_

#include "../../src/main.h"

using namespace std;

template <class K, class T>
class BST
{
private:
	BSTNode<K,T>* root;
	int quantity;

	BSTNode<K,T>* insert(K key, T data, BSTNode<K,T>* node);
	BSTNode<K,T>* search(K key, BSTNode<K,T>* node);
	BSTNode<K,T>* erase(K key, BSTNode<K,T>* node);

	K findMin(BSTNode<K,T>* node);
	K findMax(BSTNode<K,T>* node);
	K successor(BSTNode<K,T>* node);
	K predecessor(BSTNode<K,T>* node);

	void showInOrder(BSTNode<K,T>* node);
	void keysInOrder(BSTNode<K,T>* node, std::vector<K> &keysVector);

	void deleteAll(BSTNode<K,T>* node);

public:
	BST();

	// Inserts element in tree (key, data)
	void insert(K key, T data);
	bool search(K key);
	void erase(K key);

	int getQuantity();
	K findMin();
	K findMax();
	K successor(K key);
	K predecessor(K key);

	T getData(K key);
	BSTNode<K,T>* getRoot();

	void showInOrder();
	std::vector<K> keysInOrder();

	void deleteAll();

	~BST();
};


template <class K, class T>
BST<K,T>::BST()
{
	root = 0;
	quantity = 0;
}


template <class K, class T>
BSTNode<K,T>* BST<K,T>::insert(K key, T data, BSTNode<K,T>* node)
{
	if (node == 0)
		node = new BSTNode<K,T>(key, data);
	else if (key < node->getKey())
		node->setLeft(insert(key, data, node->getLeft()));
	else
		node->setRight(insert(key, data, node->getRight()));

	return node;
}


template <class K, class T>
void BST<K,T>::insert(K key, T data)
{
	if (!search(key)){
		root = insert(key, data, root);
		quantity++;
	}
}


template <class K, class T>
BSTNode<K,T>* BST<K,T>::search(K key, BSTNode<K,T>* node)
{
	if (node && key < node->getKey())
		node = search(key, node->getLeft());
	if (node && key > node->getKey())
		node = search(key, node->getRight());

	return node;
}


template <class K, class T>
bool BST<K,T>::search(K key)
{
	return (search(key, root) != 0);
}


template <class K, class T>
BSTNode<K,T>* BST<K,T>::erase(K key, BSTNode<K,T>* node)
{
	if (!node) {}

	else if (key < node->getKey()){
		node->setLeft(erase(key, node->getLeft()));
		quantity--;
	}
	else if (key > node->getKey()){
		node->setRight(erase(key, node->getRight()));
		quantity--;
	}
	else
	{
		if (node->isLeaf())
		{
			delete node;
			node = 0;
		}
		else if (node->onlyRight())
		{
			node->getRight()->setParent(node->getParent());
			BSTNode<K,T>* aux = node->getRight();
			delete node;
			node = aux;
		}
		else if (node->onlyLeft())
		{
			node->getLeft()->setParent(node->getParent());
			BSTNode<K,T>* aux = node->getLeft();
			delete node;
			node = aux;
		}
		else
		{
			K replacement;
			if (search(successor(key)))
				replacement = search(successor(key), root)->getKey();
			else
				replacement = search(predecessor(key), root)->getKey();
			T newData = getData(replacement);
			root = erase(replacement, root);
			node->setData(newData);
			node->setKey(replacement);
		}
		quantity--;
	}
	return node;
}


template <class K, class T>
void BST<K,T>::erase(K key)
{
	if (search(key))
		root = erase(key, root);
	else
		cout << "The tree does not contain specified data" << endl;
}

template <class K, class T>
int BST<K,T>::getQuantity(){
	return quantity;
}

template <class K, class T>
K BST<K,T>::findMin(BSTNode<K,T>* node)
{
	if (node->getLeft())
		return findMin(node->getLeft());
	else
		return node->getKey();
}


template <class K, class T>
K BST<K,T>::findMin()
{
	if (root)
		return findMin(root);
	else
		return "";
}


template <class K, class T>
K BST<K,T>::findMax(BSTNode<K,T>* node)
{
	if (node->getRight())
		return findMax(node->getRight());
	else
		return node->getKey();
}


template <class K, class T>
K BST<K,T>::findMax()
{
	if (root)
		return findMax(root);
	else
		return "";
}


template <class K, class T>
K BST<K,T>::successor(BSTNode<K,T>* node)
{
	K outcome;

	if (node->getKey() == findMax())	// node has no successor
		outcome = "";
	else if (node->getRight())
		outcome = findMin(node->getRight());
	else
	{
		T data = node->getData();
		BSTNode<K,T>* ancestor = node->getParent();
		while (data >= ancestor->getData())
			ancestor = ancestor->getParent();
		outcome = ancestor->getKey();
	}
	return outcome;
}


template <class K, class T>
K BST<K,T>::successor(K key)
{
	BSTNode<K,T>* node = search(key, root);

	if (node) 
		return successor(node);
	else
		return "";
}


template <class K, class T>
K BST<K,T>::predecessor(BSTNode<K,T>* node)
{
	K outcome;
	if (node->getKey() == findMin())	// node has no predecessor
		outcome = "";
	else if (node->getLeft())
		outcome = findMax(node->getLeft());
	else
	{
		T data = node->getData();
		BSTNode<K,T>* ancestor = node->getParent();
		while (data <= ancestor->getData())
			ancestor = ancestor->getParent();
		outcome = ancestor->getKey();
	}
	return outcome;
}


template <class K, class T>
K BST<K,T>::predecessor(K key)
{
	BSTNode<K,T>* node = search(key, root);

	if (node)
		return predecessor(node);
	else
		return "";
}


template <class K, class T>
T BST<K,T>::getData(K key)
{
	BSTNode<K,T>* node = search(key, root);
	T data = node->getData();
	return data;
}


template <class K, class T>
BSTNode<K,T>* BST<K,T>::getRoot()
{
	return root;
}


template <class K, class T>
void BST<K,T>::showInOrder(BSTNode<K,T>* node)
{
	if (node != 0)
	{
		showInOrder(node->getLeft());
		cout << node->getKey() << " ";
		showInOrder(node->getRight());
	}
}


template <class K, class T>
void BST<K,T>::showInOrder()
{
	showInOrder(root);
	cout << endl;
}


template <class K, class T>
void BST<K,T>::keysInOrder(BSTNode<K,T>* node, std::vector<K> &keysVector)
{
	if (node != 0)
	{
		keysInOrder(node->getLeft(), keysVector);
		keysVector.push_back(node->getKey());
		keysInOrder(node->getRight(), keysVector);
	}
}


template <class K, class T>
std::vector<K> BST<K,T>::keysInOrder()
{
	std::vector<K> keysVector;
	keysInOrder(root, keysVector);
	return keysVector;
}


template <class K, class T>
void BST<K,T>::deleteAll(BSTNode<K,T>* node)
{
	if (node)
	{
		deleteAll(node->getLeft());
		deleteAll(node->getRight());
		delete node;
	}
}


template <class K, class T>
void BST<K,T>::deleteAll()
{
	deleteAll(root);
}


template <class K, class T>
BST<K,T>::~BST()
{
	deleteAll();
}


#endif /* ARBOL_H_ */
