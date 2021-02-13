#ifndef NODO_H_
#define NODO_H_

template <class T>
class BSTNode {

private:
	// Atributos
	T data;
	BSTNode<T>* right;
	BSTNode<T>* left;
	BSTNode<T>* dad;

public:
	// Metodos
	BSTNode(T data);

	void setData(T data);
	T getData();

	void setRight(BSTNode<T>* right);
	BSTNode<T>* getRight();

	void setLeft(BSTNode<T>* left);
	BSTNode<T>* getLeft();

	void setDad(BSTNode<T>* dad);
	BSTNode<T>* getDad();

	bool isLeaf();
	bool onlyRight();
	bool onlyLeft();
};



template <class T>
BSTNode<T>::BSTNode(T data) {

	this -> data = data;
	this -> right = nullptr;
	this -> left = nullptr;
	this -> dad = nullptr;
}

template <class T>
void BSTNode<T>::setData(T data) {

	this -> data = data;
}

template <class T>
T BSTNode<T>::getData() {

	return this -> data;
}

template <class T>
void BSTNode<T>::setLeft(BSTNode<T>* left) {

	this -> left = left;
	if (left)
		left -> setDad(this);
}

template <class T>
BSTNode<T>* BSTNode<T>::getLeft() {

	return this -> left;
}

template <class T>
void BSTNode<T>::setRight(BSTNode<T>* right) {

	this -> right = right;
	if (right)
		right -> setDad(this);
}

template <class T>
BSTNode<T>* BSTNode<T>::getRight() {

	return this -> right;
}

template <class T>
void BSTNode<T>::setDad(BSTNode<T>* dad) {

	this -> dad = dad;
}

template <class T>
BSTNode<T>* BSTNode<T>::getDad() {

	return this -> dad;
}

template <class T>
bool BSTNode<T>::isLeaf() {

	return (this -> getLeft() == nullptr && this -> getRight() == nullptr);
}

template <class T>
bool BSTNode<T>::onlyRight() {

	return (this -> getLeft() == nullptr && this -> getRight() != nullptr);
}

template <class T>
bool BSTNode<T>::onlyLeft() {

	return (this -> getLeft() != nullptr && this -> getRight() == nullptr);
}



#endif /* NODO_H_ */
