#ifndef ARBOL_H_
#define ARBOL_H_

#include <iostream>

#include "BSTNode.h"

using namespace std;

template <class T>
class BST {

private:
	// Atributos
	BSTNode<T>* root;

	// Metodos
	/* Como todos los metodos son recursivos, en general se llaman tipo "hacé este método de este node en adelante"
	 * por ejemplo, "imprimí in order a partir de este node". Eso va a ser muy útil para los llamados recursivos
	 * pero el usuario nunca va a tener que "hacer algo a partir de tal node", el usuario siempre querría hacerlo
	 * desde la raíz. O sea si quiere imprimir, que imprima de la root hacia abajo. Si quiere insert, que inserte
	 * en el árbol que empieza en la raíz.
	 *
	 * A priori se me ocurrió que estos métodos tengan un parámetro de "node inicial" llamado simplemente "node"
	 * que por default sean la root, pero esto no se puede hacer así, lo que se ponga por default deben ser contantes.
	 *
	 * Entonces una solución es que el usuario, siempre que llame a un método, le pase por parámetro la raíz del árbol,
	 * pero esto obviamente es muy poco práctico y honestamente está mal. Entonces la solución definitiva es tener, para
	 * cada método, dos versiones: una privada y una pública. El público llamará al privado con "node inicial" = raíz.
	 * Luego el privado se llamará a sí mismo con los sub-árboles.
	 */
	BSTNode<T>* insert(T data, BSTNode<T>* node);
	BSTNode<T>* search(T data, BSTNode<T>* node);
	BSTNode<T>* erase(T data, BSTNode<T>* node);

	T findMin(BSTNode<T>* node);
	T findMax(BSTNode<T>* node);
	T successor(BSTNode<T>* node);
	T predecessor(BSTNode<T>* node);

	void showInOrder(BSTNode<T>* node);
	void deleteAll(BSTNode<T>* node);

public:
	BST();

	void insert(T data);
	bool search(T data);
	void erase(T data);

	T findMin();
	T findMax();
	T successor(T data);
	T predecessor(T data);

	void showInOrder();
	void deleteAll();

	~BST();


	BSTNode<T>* getRoot();
};

template <class T>
BSTNode<T>* BST<T>::getRoot() {

	return this -> root;
}

// =============================================================================================================================================================================
// =============================================================================================================================================================================
// =============================================================================================================================================================================

template <class T>
BST<T>::BST() {
	this -> root = nullptr;
}

/*
 * Si hago <void insert(T data, node* node)>, node se pasa por referencia, entonces los cambios que se hagan
 * adentro de la función no se verán reflejados en el node original. Pensé en solucionar esto pasando el node
 * por referencia pero esto me da error de compilación ya que este node que se pasa por referencia, en los
 * llamados recursivos, no será algo constante, así que no se puede pasar por referencia.
 *
 * La única solución que queda es que <insert> devuelva un puntero, así se lo asigno al puntero original directamente.
 */
template <class T>
BSTNode<T>* BST<T>::insert(T data, BSTNode<T>* node) {

	if (node == nullptr)
		node = new BSTNode<T>(data);

	else if (data < node -> getData())
		node -> setLeft(insert(data, node -> getLeft()));

	else
		node -> setRight(insert(data, node -> getRight()));

	return node;
}




template <class T>
void BST<T>::insert(T data) {

	if (!search(data))
		this -> root = insert(data, this -> root);
}




template <class T>
BSTNode<T>* BST<T>::search(T data, BSTNode<T>* node) {

	if (node && data < node -> getData())
		node = search(data, node -> getLeft());
	if (node && data > node -> getData())
		node = search(data, node -> getRight());

	return node;
}




template <class T>
bool BST<T>::search(T data) {

	return (search(data, this -> root) != nullptr);
}




template <class T>
BSTNode<T>* BST<T>::erase(T data, BSTNode<T>* node) {

	if (! node) {}

	else if (data < node -> getData())
		node -> setLeft(erase(data, node -> getLeft()));

	else if (data > node -> getData())
		node -> setRight(erase(data, node -> getRight()));

	else {
		// Caso 1:
		if (node -> isLeaf()) {
			delete node;
			node = nullptr;
		}
		// Caso 2:
		else if (node -> onlyRight()) {
			node -> getRight() -> setDad(node -> getDad());
			BSTNode<T>* aux = node -> getRight();
			delete node;
			node = aux;
		}
		// Caso 3:
		else if (node -> olnyLeft()) {
			node -> getLeft() -> setDad(node -> getDad());
			BSTNode<T>* aux = node -> getLeft();
			delete node;
			node = aux;
		}
		// Caso 4:
		else {
			T replacement;
			if (search(successor(data)))
				replacement = search(successor(data), this -> root) -> getData();
			else
				replacement = search(predecessor(data), this -> root) -> getData();
			this -> root = erase(replacement, this -> root);
			node -> set_data(replacement);
		}
		// - - - -
	}
	return node;
}




template <class T>
void BST<T>::erase(T data) {

	if (search(data))
		this -> root = erase(data, this -> root);
	else
		cout << "Ese data no está en el árbol." << endl;
}




template <class T>
T BST<T>::findMin(BSTNode<T>* node) {

	if (node -> getLeft())
		return findMin(node -> getLeft());
	else
		return node -> getData();
}




template <class T>
T BST<T>::findMin() {

	if (this -> root) {
		return findMin(this -> root);
	} else {
		cout << "Árbol vacio." << endl;
		return -1;
	}
}




template <class T>
T BST<T>::findMax(BSTNode<T>* node) {

	if (node -> getRight())
		return findMax(node -> getRight());
	else
		return node -> getData();
}




template <class T>
T BST<T>::findMax() {

	if (this -> root) {
		return findMax(this -> root);
	} else {
		cout << "Árbol vacio." << endl;
		return -1;
	}
}




template <class T>
T BST<T>::successor(BSTNode<T>* node) {

	T outcome;
	// Caso 1:
	if (node -> getData() == findMax()) {
		cout << "El valor no tiene successor." << endl;
		outcome = -1;
	}
	// Caso 2:
	else if (node -> getRight()) {
		outcome = findMin(node -> getRight());
	}
	// Caso 3:
	else {
		T data = node -> getData();
		BSTNode<T>* ancestor = node -> getDad();
		while (data >= ancestor -> getData()) {
			ancestor = ancestor -> getDad();
		}
		outcome = ancestor -> getData();
	}
	// - - - -
	return outcome;
}

template <class T>
T BST<T>::successor(T data) {

	BSTNode<T>* node = search(data, this -> root);

	if (node) {
		return successor(node);
	} else {
		cout << "Ese valor no pertenece al árbol." << endl;
		return -1;
	}
}




template <class T>
T BST<T>::predecessor(BSTNode<T>* node) {

	T outcome;
	// Caso 1:
	if (node -> getData() == findMin()) {
		cout << "El valor no tiene predecessor." << endl;
		outcome = -1;
	}
	// Caso 2:
	else if (node -> getLeft()) {
		outcome = findMax(node -> getLeft());
	}
	// Caso 3:
	else {
		T data = node -> getData();
		BSTNode<T>* ancestor = node -> getDad();
		while (data <= ancestor -> getData()) {
			ancestor = ancestor -> getDad();
		}
		outcome = ancestor -> getData();
	}
	// - - - -
	return outcome;
}




template <class T>
T BST<T>::predecessor(T data) {

	BSTNode<T>* node = search(data, this -> root);

	if (node) {
		return predecessor(node);
	} else {
		cout << "Ese valor no pertenece al árbol." << endl;
		return -1;
	}
}




template <class T>
void BST<T>::showInOrder(BSTNode<T>* node) {

	if (node != nullptr) {
		showInOrder(node -> getLeft());
		cout << node -> getData() << " ";
		showInOrder(node -> getRight());
	}
}




template <class T>
void BST<T>::showInOrder() {

	showInOrder(this -> root);
	cout << endl;
}




template <class T>
void BST<T>::deleteAll(BSTNode<T>* node) {

	if (node) {
		this -> deleteAll(node -> getLeft());
		this -> deleteAll(node -> getRight());
		delete node;
	}
}




template <class T>
void BST<T>::deleteAll() {

	this -> deleteAll(this -> root);
}




template <class T>
BST<T>::~BST() {

	deleteAll();
}


#endif /* ARBOL_H_ */
