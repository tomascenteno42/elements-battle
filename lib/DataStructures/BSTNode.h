#ifndef NODO_H_
#define NODO_H_

template <class K, class T>
class DictionaryNode {

private:
	// Atributos
	K key;
	T data;
	DictionaryNode<K,T>* right;
	DictionaryNode<K,T>* left;
	DictionaryNode<K,T>* dad;

public:
	// Metodos
	DictionaryNode(K key, T data);

	void setData(T data);
	void setKey(K key);
	T getData();
	K getKey();

	void setRight(DictionaryNode<K,T>* right);
	DictionaryNode<K,T>* getRight();

	void setLeft(DictionaryNode<K,T>* left);
	DictionaryNode<K,T>* getLeft();

	void setDad(DictionaryNode<K,T>* dad);
	DictionaryNode<K,T>* getDad();

	bool isLeaf();
	bool onlyRight();
	bool onlyLeft();
};

// -------------- IMPLEMENTATION -----------------

template <class K, class T>
DictionaryNode<K,T>::DictionaryNode(K key, T data) {

	this -> data = data;
	this -> key = key;
	this -> right = nullptr;
	this -> left = nullptr;
	this -> dad = nullptr;
}

template <class K, class T>
void DictionaryNode<K,T>::setData(T data) {
	this -> data = data;
}

template <class K, class T>
void DictionaryNode<K,T>::setKey(K key) {
	this -> key = key;
}

template <class K, class T>
T DictionaryNode<K,T>::getData() {
	return this -> data;
}

template <class K, class T>
K DictionaryNode<K,T>::getKey() {
	return this -> key;
}

template <class K, class T>
void DictionaryNode<K,T>::setLeft(DictionaryNode<K,T>* left) {

	this -> left = left;
	if (left) left -> setDad(this);
}

template <class K, class T>
DictionaryNode<K,T>* DictionaryNode<K,T>::getLeft() {
	return this -> left;
}

template <class K, class T>
void DictionaryNode<K,T>::setRight(DictionaryNode<K,T>* right) {

	this -> right = right;
	if (right) right -> setDad(this);
}

template <class K, class T>
DictionaryNode<K,T>* DictionaryNode<K,T>::getRight() {
	return this -> right;
}

template <class K, class T>
void DictionaryNode<K,T>::setDad(DictionaryNode<K,T>* dad) {

	this -> dad = dad;
}

template <class K, class T>
DictionaryNode<K,T>* DictionaryNode<K,T>::getDad() {

	return this -> dad;
}

template <class K, class T>
bool DictionaryNode<K,T>::isLeaf() {

	return (this -> getLeft() == nullptr && this -> getRight() == nullptr);
}

template <class K, class T>
bool DictionaryNode<K,T>::onlyRight() {

	return (this -> getLeft() == nullptr && this -> getRight() != nullptr);
}

template <class K, class T>
bool DictionaryNode<K,T>::onlyLeft() {

	return (this -> getLeft() != nullptr && this -> getRight() == nullptr);
}



#endif /* NODO_H_ */
