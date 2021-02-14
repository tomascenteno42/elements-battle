#ifndef ARBOL_H_
#define ARBOL_H_

#include "BSTNode.h"

using namespace std;

template <class K, class T>
class BST {

private:
	
	BSTNode<K,T>* root;

	BSTNode<K,T>* insert(K key, T data, BSTNode<K,T>* node);
	BSTNode<K,T>* search(K key, BSTNode<K,T>* node);
	BSTNode<K,T>* erase(K key, BSTNode<K,T>* node);

	K findMin(BSTNode<K,T>* node);
	K findMax(BSTNode<K,T>* node);
	K successor(BSTNode<K,T>* node);
	K predecessor(BSTNode<K,T>* node);

	void showInOrder(BSTNode<K,T>* node);
	void deleteAll(BSTNode<K,T>* node);

public:
	BST();

	// Inserts element in tree (key, data)
	void insert(K key, T data);
	bool search(K key);
	void erase(K key);

	K findMin();
	K findMax();
	K successor(K key);
	K predecessor(K key);

	T getData(K key);

	void showInOrder();
	void deleteAll();

	~BST();


	BSTNode<K,T>* getRoot();
};

template <class K, class T>
BSTNode<K,T>* BST<K,T>::getRoot() {
	return this -> root;
}

// =============================================================================================================================================================================
// =============================================================================================================================================================================
// =============================================================================================================================================================================

template <class K, class T>
BST<K,T>::BST() {
	this -> root = nullptr;
}




template <class K, class T>
BSTNode<K,T>* BST<K,T>::insert(K key, T data, BSTNode<K,T>* node) {

	if (node == nullptr)
		node = new BSTNode<K,T>(key, data);

	else if (key < node -> getKey())
		node -> setLeft(insert(key, data, node -> getLeft()));

	else
		node -> setRight(insert(key, data, node -> getRight()));

	return node;
}




template <class K, class T>
void BST<K,T>::insert(K key, T data) {
	if (!search(key))
		this -> root = insert(key, data, this -> root);
}




template <class K, class T>
BSTNode<K,T>* BST<K,T>::search(K key, BSTNode<K,T>* node) {

	if (node && key < node ->getKey())
		node = search(key, node -> getLeft());
	if (node && key > node ->getKey())
		node = search(key, node -> getRight());

	return node;
}




template <class K, class T>
bool BST<K,T>::search(K key) {
	return (search(key, this -> root) != nullptr);
}




template <class K, class T>
BSTNode<K,T>* BST<K,T>::erase(K key, BSTNode<K,T>* node) {

	if (!node) {}

	else if (key < node -> getKey())
		node -> setLeft(erase(key, node -> getLeft()));

	else if (key > node -> getKey())
		node -> setRight(erase(key, node -> getRight()));

	else {
		
		if (node -> isLeaf()) {

			delete node;
			node = nullptr;

		} else if (node -> onlyRight()) {
			node -> getRight() -> setDad(node -> getDad());
			BSTNode<K,T>* aux = node -> getRight();
			delete node;
			node = aux;

		} else if (node -> onlyLeft()) {
			node -> getLeft() -> setDad(node -> getDad());
			BSTNode<K,T>* aux = node -> getLeft();
			delete node;
			node = aux;

		} else {
			K replacement;
			if (search(successor(key)))
				replacement = search(successor(key), this -> root) -> getData();
			else
				replacement = search(predecessor(key), this -> root) -> getData();
			this -> root = erase(replacement, this -> root);
			T newData = getData(replacement);
			node -> setData(newData);
			node -> setKey(replacement);
		}
		// - - - -
	}
	return node;
}




template <class K, class T>
void BST<K,T>::erase(K key) {

	if (search(key))
		this -> root = erase(key, this -> root);
	else
		cout << "Ese data no está en el árbol." << endl;
}




template <class K, class T>
K BST<K,T>::findMin(BSTNode<K,T>* node) {

	if (node -> getLeft())
		return findMin(node -> getLeft());
	else
		return node -> getKey();
}




template <class K, class T>
K BST<K,T>::findMin() {

	if (this -> root) {
		return findMin(this -> root);
	} else {
		cout << "Árbol vacio." << endl;
		return "";
	}
}




template <class K, class T>
K BST<K,T>::findMax(BSTNode<K,T>* node) {

	if (node -> getRight())
		return findMax(node -> getRight());
	else
		return node -> getKey();
}




template <class K, class T>
K BST<K,T>::findMax() {

	if (this -> root) {
		return findMax(this -> root);
	} else {
		cout << "Árbol vacio." << endl;
		return "";
	}
}




template <class K, class T>
K BST<K,T>::successor(BSTNode<K,T>* node) {

	K outcome;
	// Caso 1:
	if (node -> getKey() == findMax()) {
		cout << "El valor no tiene successor." << endl;
		outcome = nullptr;
	}
	// Caso 2:
	else if (node -> getRight()) {
		outcome = findMin(node -> getRight());
	}
	// Caso 3:
	else {
		T data = node -> getData();
		BSTNode<K,T>* ancestor = node -> getDad();
		while (data >= ancestor -> getData()) {
			ancestor = ancestor -> getDad();
		}
		outcome = ancestor -> getKey();
	}
	// - - - -
	return outcome;
}




template <class K, class T>
K BST<K,T>::successor(K key) {

	BSTNode<K,T>* node = search(key, this -> root);

	if (node) {
		return successor(node);
	} else {
		cout << "Ese valor no pertenece al árbol." << endl;
		return "";
	}
}




template <class K, class T>
K BST<K,T>::predecessor(BSTNode<K,T>* node) {

	K outcome;
	// Caso 1:
	if (node -> getKey() == findMin()) {
		cout << "El valor no tiene predecessor." << endl;
		outcome = nullptr;
	}
	// Caso 2:
	else if (node -> getLeft()) {
		outcome = findMax(node -> getLeft());
	}
	// Caso 3:
	else {
		T data = node -> getData();
		BSTNode<K,T>* ancestor = node -> getDad();
		while (data <= ancestor -> getData()) {
			ancestor = ancestor -> getDad();
		}
		outcome = ancestor -> getKey();
	}
	// - - - -
	return outcome;
}




template <class K, class T>
K BST<K,T>::predecessor(K key) {

	BSTNode<K,T>* node = search(key, this -> root);

	if (node) {
		return predecessor(node);
	} else {
		cout << "Ese valor no pertenece al árbol." << endl;
		return "";
	}
}




template <class K, class T>
T BST<K,T>::getData(K key){
	BSTNode<K,T>* node = search(key, this -> root);
	T data = node->getData();
	return data;
}




template <class K, class T>
void BST<K,T>::showInOrder(BSTNode<K,T>* node) {

	if (node != nullptr) {
		showInOrder(node -> getLeft());
		cout << node -> getData() << " ";
		showInOrder(node -> getRight());
	}
}




template <class K, class T>
void BST<K,T>::showInOrder() {

	showInOrder(this -> root);
	cout << endl;
}




template <class K, class T>
void BST<K,T>::deleteAll(BSTNode<K,T>* node) {

	if (node) {
		this -> deleteAll(node -> getLeft());
		this -> deleteAll(node -> getRight());
		delete node;
	}
}




template <class K, class T>
void BST<K,T>::deleteAll() {

	this -> deleteAll(this -> root);
}




template <class K, class T>
BST<K,T>::~BST() {

	deleteAll();
}


#endif /* ARBOL_H_ */
