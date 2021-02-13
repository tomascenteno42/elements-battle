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

	void set_left(BSTNode<T>* left);
	BSTNode<T>* get_left();

	void set_dad(BSTNode<T>* dad);
	BSTNode<T>* get_dad();

	bool es_hoja();
	bool solo_tiene_right();
	bool solo_tiene_left();
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
void BSTNode<T>::set_left(BSTNode<T>* left) {

	this -> left = left;
	if (left)
		left -> set_dad(this);
}

template <class T>
BSTNode<T>* BSTNode<T>::get_left() {

	return this -> left;
}

template <class T>
void BSTNode<T>::setRight(BSTNode<T>* right) {

	this -> right = right;
	if (right)
		right -> set_dad(this);
}

template <class T>
BSTNode<T>* BSTNode<T>::getRight() {

	return this -> right;
}

template <class T>
void BSTNode<T>::set_dad(BSTNode<T>* dad) {

	this -> dad = dad;
}

template <class T>
BSTNode<T>* BSTNode<T>::get_dad() {

	return this -> dad;
}

template <class T>
bool BSTNode<T>::es_hoja() {

	return (this -> get_left() == nullptr && this -> getRight() == nullptr);
}

template <class T>
bool BSTNode<T>::solo_tiene_right() {

	return (this -> get_left() == nullptr && this -> getRight() != nullptr);
}

template <class T>
bool BSTNode<T>::solo_tiene_left() {

	return (this -> get_left() != nullptr && this -> getRight() == nullptr);
}



#endif /* NODO_H_ */
