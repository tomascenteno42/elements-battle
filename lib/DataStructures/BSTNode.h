#ifndef NODO_H_
#define NODO_H_

template <class K, class T>
class BSTNode {

private:
	// Atributos
	K key;
	T data;
	BSTNode<K,T>* right;
	BSTNode<K,T>* left;
	BSTNode<K,T>* dad;

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

	void setDad(BSTNode<K,T>* dad);
	BSTNode<K,T>* getDad();

	bool isLeaf();
	bool onlyRight();
	bool onlyLeft();
};

// -------------- IMPLEMENTATION -----------------

template <class K, class T>
BSTNode<K,T>::BSTNode(K key, T data) {

	this -> data = data;
	this -> key = key;
	this -> right = nullptr;
	this -> left = nullptr;
	this -> dad = nullptr;
}

template <class K, class T>
void BSTNode<K,T>::setData(T data) {
	this -> data = data;
}

template <class K, class T>
void BSTNode<K,T>::setKey(K key) {
	this -> key = key;
}

template <class K, class T>
T BSTNode<K,T>::getData() {
	return this -> data;
}

template <class K, class T>
K BSTNode<K,T>::getKey() {
	return this -> key;
}

template <class K, class T>
void BSTNode<K,T>::setLeft(BSTNode<K,T>* left) {

	this -> left = left;
	if (left) left -> setDad(this);
}

template <class K, class T>
BSTNode<K,T>* BSTNode<K,T>::getLeft() {
	return this -> left;
}

template <class K, class T>
void BSTNode<K,T>::setRight(BSTNode<K,T>* right) {

	this -> right = right;
	if (right) right -> setDad(this);
}

template <class K, class T>
BSTNode<K,T>* BSTNode<K,T>::getRight() {
	return this -> right;
}

template <class K, class T>
void BSTNode<K,T>::setDad(BSTNode<K,T>* dad) {

	this -> dad = dad;
}

template <class K, class T>
BSTNode<K,T>* BSTNode<K,T>::getDad() {

	return this -> dad;
}

template <class K, class T>
bool BSTNode<K,T>::isLeaf() {

	return (this -> getLeft() == nullptr && this -> getRight() == nullptr);
}

template <class K, class T>
bool BSTNode<K,T>::onlyRight() {

	return (this -> getLeft() == nullptr && this -> getRight() != nullptr);
}

template <class K, class T>
bool BSTNode<K,T>::onlyLeft() {

	return (this -> getLeft() != nullptr && this -> getRight() == nullptr);
}



#endif /* NODO_H_ */
