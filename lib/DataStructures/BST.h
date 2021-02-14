#ifndef ARBOL_H_
#define ARBOL_H_

#include "BSTNode.h"

using namespace std;

template <class K, class T>
class Dictionary {

private:
	
	DictionaryNode<K,T>* root;

	DictionaryNode<K,T>* insert(K key, T data, DictionaryNode<K,T>* node);
	DictionaryNode<K,T>* search(K key, DictionaryNode<K,T>* node);
	DictionaryNode<K,T>* erase(K key, DictionaryNode<K,T>* node);

	K findMin(DictionaryNode<K,T>* node);
	K findMax(DictionaryNode<K,T>* node);
	K successor(DictionaryNode<K,T>* node);
	K predecessor(DictionaryNode<K,T>* node);

	void showInOrder(DictionaryNode<K,T>* node);
	void deleteAll(DictionaryNode<K,T>* node);

public:
	Dictionary();

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

	~Dictionary();


	DictionaryNode<K,T>* getRoot();
};

template <class K, class T>
DictionaryNode<K,T>* Dictionary<K,T>::getRoot() {
	return this -> root;
}

// =============================================================================================================================================================================
// =============================================================================================================================================================================
// =============================================================================================================================================================================

template <class K, class T>
Dictionary<K,T>::Dictionary() {
	this -> root = nullptr;
}




template <class K, class T>
DictionaryNode<K,T>* Dictionary<K,T>::insert(K key, T data, DictionaryNode<K,T>* node) {

	if (node == nullptr)
		node = new DictionaryNode<K,T>(key, data);

	else if (key < node -> getKey())
		node -> setLeft(insert(key, data, node -> getLeft()));

	else
		node -> setRight(insert(key, data, node -> getRight()));

	return node;
}




template <class K, class T>
void Dictionary<K,T>::insert(K key, T data) {
	if (!search(key))
		this -> root = insert(key, data, this -> root);
}




template <class K, class T>
DictionaryNode<K,T>* Dictionary<K,T>::search(K key, DictionaryNode<K,T>* node) {

	if (node && key < node ->getKey())
		node = search(key, node -> getLeft());
	if (node && key > node ->getKey())
		node = search(key, node -> getRight());

	return node;
}




template <class K, class T>
bool Dictionary<K,T>::search(K key) {
	return (search(key, this -> root) != nullptr);
}




template <class K, class T>
DictionaryNode<K,T>* Dictionary<K,T>::erase(K key, DictionaryNode<K,T>* node) {

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
			DictionaryNode<K,T>* aux = node -> getRight();
			delete node;
			node = aux;

		} else if (node -> onlyLeft()) {
			node -> getLeft() -> setDad(node -> getDad());
			DictionaryNode<K,T>* aux = node -> getLeft();
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
void Dictionary<K,T>::erase(K key) {

	if (search(key))
		this -> root = erase(key, this -> root);
	else
		cout << "Ese data no está en el árbol." << endl;
}




template <class K, class T>
K Dictionary<K,T>::findMin(DictionaryNode<K,T>* node) {

	if (node -> getLeft())
		return findMin(node -> getLeft());
	else
		return node -> getKey();
}




template <class K, class T>
K Dictionary<K,T>::findMin() {

	if (this -> root) {
		return findMin(this -> root);
	} else {
		cout << "Árbol vacio." << endl;
		return "";
	}
}




template <class K, class T>
K Dictionary<K,T>::findMax(DictionaryNode<K,T>* node) {

	if (node -> getRight())
		return findMax(node -> getRight());
	else
		return node -> getKey();
}




template <class K, class T>
K Dictionary<K,T>::findMax() {

	if (this -> root) {
		return findMax(this -> root);
	} else {
		cout << "Árbol vacio." << endl;
		return "";
	}
}




template <class K, class T>
K Dictionary<K,T>::successor(DictionaryNode<K,T>* node) {

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
		DictionaryNode<K,T>* ancestor = node -> getDad();
		while (data >= ancestor -> getData()) {
			ancestor = ancestor -> getDad();
		}
		outcome = ancestor -> getKey();
	}
	// - - - -
	return outcome;
}




template <class K, class T>
K Dictionary<K,T>::successor(K key) {

	DictionaryNode<K,T>* node = search(key, this -> root);

	if (node) {
		return successor(node);
	} else {
		cout << "Ese valor no pertenece al árbol." << endl;
		return "";
	}
}




template <class K, class T>
K Dictionary<K,T>::predecessor(DictionaryNode<K,T>* node) {

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
		DictionaryNode<K,T>* ancestor = node -> getDad();
		while (data <= ancestor -> getData()) {
			ancestor = ancestor -> getDad();
		}
		outcome = ancestor -> getKey();
	}
	// - - - -
	return outcome;
}




template <class K, class T>
K Dictionary<K,T>::predecessor(K key) {

	DictionaryNode<K,T>* node = search(key, this -> root);

	if (node) {
		return predecessor(node);
	} else {
		cout << "Ese valor no pertenece al árbol." << endl;
		return "";
	}
}




template <class K, class T>
T Dictionary<K,T>::getData(K key){
	DictionaryNode<K,T>* node = search(key, this -> root);
	T data = node->getData();
	return data;
}




template <class K, class T>
void Dictionary<K,T>::showInOrder(DictionaryNode<K,T>* node) {

	if (node != nullptr) {
		showInOrder(node -> getLeft());
		cout << node -> getData() << " ";
		showInOrder(node -> getRight());
	}
}




template <class K, class T>
void Dictionary<K,T>::showInOrder() {

	showInOrder(this -> root);
	cout << endl;
}




template <class K, class T>
void Dictionary<K,T>::deleteAll(DictionaryNode<K,T>* node) {

	if (node) {
		this -> deleteAll(node -> getLeft());
		this -> deleteAll(node -> getRight());
		delete node;
	}
}




template <class K, class T>
void Dictionary<K,T>::deleteAll() {

	this -> deleteAll(this -> root);
}




template <class K, class T>
Dictionary<K,T>::~Dictionary() {

	deleteAll();
}


#endif /* ARBOL_H_ */
