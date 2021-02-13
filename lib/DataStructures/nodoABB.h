#ifndef NODO_H_
#define NODO_H_

template <class T>
class NodoABB {

private:
	// Atributos
	T dato;
	NodoABB<T>* der;
	NodoABB<T>* izq;
	NodoABB<T>* pad;

public:
	// Metodos
	NodoABB(T dato);

	void set_dato(T dato);
	T get_dato();

	void set_der(NodoABB<T>* der);
	NodoABB<T>* get_der();

	void set_izq(NodoABB<T>* izq);
	NodoABB<T>* get_izq();

	void set_pad(NodoABB<T>* pad);
	NodoABB<T>* get_pad();

	bool es_hoja();
	bool solo_tiene_der();
	bool solo_tiene_izq();
};



template <class T>
NodoABB<T>::NodoABB(T dato) {

	this -> dato = dato;
	this -> der = nullptr;
	this -> izq = nullptr;
	this -> pad = nullptr;
}

template <class T>
void NodoABB<T>::set_dato(T dato) {

	this -> dato = dato;
}

template <class T>
T NodoABB<T>::get_dato() {

	return this -> dato;
}

template <class T>
void NodoABB<T>::set_izq(NodoABB<T>* izq) {

	this -> izq = izq;
	if (izq)
		izq -> set_pad(this);
}

template <class T>
NodoABB<T>* NodoABB<T>::get_izq() {

	return this -> izq;
}

template <class T>
void NodoABB<T>::set_der(NodoABB<T>* der) {

	this -> der = der;
	if (der)
		der -> set_pad(this);
}

template <class T>
NodoABB<T>* NodoABB<T>::get_der() {

	return this -> der;
}

template <class T>
void NodoABB<T>::set_pad(NodoABB<T>* pad) {

	this -> pad = pad;
}

template <class T>
NodoABB<T>* NodoABB<T>::get_pad() {

	return this -> pad;
}

template <class T>
bool NodoABB<T>::es_hoja() {

	return (this -> get_izq() == nullptr && this -> get_der() == nullptr);
}

template <class T>
bool NodoABB<T>::solo_tiene_der() {

	return (this -> get_izq() == nullptr && this -> get_der() != nullptr);
}

template <class T>
bool NodoABB<T>::solo_tiene_izq() {

	return (this -> get_izq() != nullptr && this -> get_der() == nullptr);
}



#endif /* NODO_H_ */
