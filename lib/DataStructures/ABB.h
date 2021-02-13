#ifndef ARBOL_H_
#define ARBOL_H_

#include <iostream>
#include "nodoABB.h"

using namespace std;

template <class T>
class ABB {

private:
	// Atributos
	NodoABB<T>* raiz;

	// Metodos
	/* Como todos los metodos son recursivos, en general se llaman tipo "hacé este método de este nodo en adelante"
	 * por ejemplo, "imprimí in order a partir de este nodo". Eso va a ser muy útil para los llamados recursivos
	 * pero el usuario nunca va a tener que "hacer algo a partir de tal nodo", el usuario siempre querría hacerlo
	 * desde la raíz. O sea si quiere imprimir, que imprima de la raiz hacia abajo. Si quiere insertar, que inserte
	 * en el árbol que empieza en la raíz.
	 *
	 * A priori se me ocurrió que estos métodos tengan un parámetro de "nodo inicial" llamado simplemente "nodo"
	 * que por default sean la raiz, pero esto no se puede hacer así, lo que se ponga por default deben ser contantes.
	 *
	 * Entonces una solución es que el usuario, siempre que llame a un método, le pase por parámetro la raíz del árbol,
	 * pero esto obviamente es muy poco práctico y honestamente está mal. Entonces la solución definitiva es tener, para
	 * cada método, dos versiones: una privada y una pública. El público llamará al privado con "nodo inicial" = raíz.
	 * Luego el privado se llamará a sí mismo con los sub-árboles.
	 */
	NodoABB<T>* insertar(T dato, NodoABB<T>* nodo);
	NodoABB<T>* buscar(T dato, NodoABB<T>* nodo);
	NodoABB<T>* eliminar(T dato, NodoABB<T>* nodo);

	T encontrar_min(NodoABB<T>* nodo);
	T encontrar_max(NodoABB<T>* nodo);
	T sucesor(NodoABB<T>* nodo);
	T predecesor(NodoABB<T>* nodo);

	void mostrar_in_order(NodoABB<T>* nodo);
	void borrar_todo(NodoABB<T>* nodo);

public:
	ABB();

	void insertar(T dato);
	bool buscar(T dato);
	void eliminar(T dato);

	T encontrar_min();
	T encontrar_max();
	T sucesor(T dato);
	T predecesor(T dato);

	void mostrar_in_order();
	void borrar_todo();

	~ABB();


	NodoABB<T>* get_raiz();
};

template <class T>
NodoABB<T>* ABB<T>::get_raiz() {

	return this -> raiz;
}

// =============================================================================================================================================================================
// =============================================================================================================================================================================
// =============================================================================================================================================================================

template <class T>
ABB<T>::ABB() {

	this -> raiz = nullptr;
}





/*
 * Si hago <void insertar(T dato, Nodo* nodo)>, nodo se pasa por referencia, entonces los cambios que se hagan
 * adentro de la función no se verán reflejados en el nodo original. Pensé en solucionar esto pasando el nodo
 * por referencia pero esto me da error de compilación ya que este nodo que se pasa por referencia, en los
 * llamados recursivos, no será algo constante, así que no se puede pasar por referencia.
 *
 * La única solución que queda es que <insertar> devuelva un puntero, así se lo asigno al puntero original directamente.
 */
template <class T>
NodoABB<T>* ABB<T>::insertar(T dato, NodoABB<T>* nodo) {

	if (nodo == nullptr)
		nodo = new NodoABB<T>(dato);

	else if (dato < nodo -> get_dato())
		nodo -> set_izq(insertar(dato, nodo -> get_izq()));

	else
		nodo -> set_der(insertar(dato, nodo -> get_der()));

	return nodo;
}

template <class T>
void ABB<T>::insertar(T dato) {

	if (!buscar(dato))
		this -> raiz = insertar(dato, this -> raiz);

}





template <class T>
NodoABB<T>* ABB<T>::buscar(T dato, NodoABB<T>* nodo) {

	if (nodo && dato < nodo -> get_dato())
		nodo = buscar(dato, nodo -> get_izq());
	if (nodo && dato > nodo -> get_dato())
		nodo = buscar(dato, nodo -> get_der());

	return nodo;
}

template <class T>
bool ABB<T>::buscar(T dato) {

	return (buscar(dato, this -> raiz) != nullptr);
}





template <class T>
NodoABB<T>* ABB<T>::eliminar(T dato, NodoABB<T>* nodo) {

	if (! nodo) {}

	else if (dato < nodo -> get_dato())
		nodo -> set_izq(eliminar(dato, nodo -> get_izq()));

	else if (dato > nodo -> get_dato())
		nodo -> set_der(eliminar(dato, nodo -> get_der()));

	else {
		// Caso 1:
		if (nodo -> es_hoja()) {
			delete nodo;
			nodo = nullptr;
		}
		// Caso 2:
		else if (nodo -> solo_tiene_der()) {
			nodo -> get_der() -> set_pad(nodo -> get_pad());
			NodoABB<T>* aux = nodo -> get_der();
			delete nodo;
			nodo = aux;
		}
		// Caso 3:
		else if (nodo -> solo_tiene_izq()) {
			nodo -> get_izq() -> set_pad(nodo -> get_pad());
			NodoABB<T>* aux = nodo -> get_izq();
			delete nodo;
			nodo = aux;
		}
		// Caso 4:
		else {
			T reemplazo;
			if (buscar(sucesor(dato)))
				reemplazo = buscar(sucesor(dato), this -> raiz) -> get_dato();
			else
				reemplazo = buscar(predecesor(dato), this -> raiz) -> get_dato();
			this -> raiz = eliminar(reemplazo, this -> raiz);
			nodo -> set_dato(reemplazo);
		}
		// - - - -
	}
	return nodo;
}

template <class T>
void ABB<T>::eliminar(T dato) {

	if (buscar(dato))
		this -> raiz = eliminar(dato, this -> raiz);
	else
		cout << "Ese dato no está en el árbol." << endl;
}





template <class T>
T ABB<T>::encontrar_min(NodoABB<T>* nodo) {

	if (nodo -> get_izq())
		return encontrar_min(nodo -> get_izq());
	else
		return nodo -> get_dato();
}

template <class T>
T ABB<T>::encontrar_min() {

	if (this -> raiz) {
		return encontrar_min(this -> raiz);
	} else {
		cout << "Árbol vacio." << endl;
		return -1;
	}
}





template <class T>
T ABB<T>::encontrar_max(NodoABB<T>* nodo) {

	if (nodo -> get_der())
		return encontrar_max(nodo -> get_der());
	else
		return nodo -> get_dato();
}

template <class T>
T ABB<T>::encontrar_max() {

	if (this -> raiz) {
		return encontrar_max(this -> raiz);
	} else {
		cout << "Árbol vacio." << endl;
		return -1;
	}
}





template <class T>
T ABB<T>::sucesor(NodoABB<T>* nodo) {

	T resultado;
	// Caso 1:
	if (nodo -> get_dato() == encontrar_max()) {
		cout << "El valor no tiene sucesor." << endl;
		resultado = -1;
	}
	// Caso 2:
	else if (nodo -> get_der()) {
		resultado = encontrar_min(nodo -> get_der());
	}
	// Caso 3:
	else {
		T dato = nodo -> get_dato();
		NodoABB<T>* ancestro = nodo -> get_pad();
		while (dato >= ancestro -> get_dato()) {
			ancestro = ancestro -> get_pad();
		}
		resultado = ancestro -> get_dato();
	}
	// - - - -
	return resultado;
}

template <class T>
T ABB<T>::sucesor(T dato) {

	NodoABB<T>* nodo = buscar(dato, this -> raiz);

	if (nodo) {
		return sucesor(nodo);
	} else {
		cout << "Ese valor no pertenece al árbol." << endl;
		return -1;
	}
}





template <class T>
T ABB<T>::predecesor(NodoABB<T>* nodo) {

	T resultado;
	// Caso 1:
	if (nodo -> get_dato() == encontrar_min()) {
		cout << "El valor no tiene predecesor." << endl;
		resultado = -1;
	}
	// Caso 2:
	else if (nodo -> get_izq()) {
		resultado = encontrar_max(nodo -> get_izq());
	}
	// Caso 3:
	else {
		T dato = nodo -> get_dato();
		NodoABB<T>* ancestro = nodo -> get_pad();
		while (dato <= ancestro -> get_dato()) {
			ancestro = ancestro -> get_pad();
		}
		resultado = ancestro -> get_dato();
	}
	// - - - -
	return resultado;
}

template <class T>
T ABB<T>::predecesor(T dato) {

	NodoABB<T>* nodo = buscar(dato, this -> raiz);

	if (nodo) {
		return predecesor(nodo);
	} else {
		cout << "Ese valor no pertenece al árbol." << endl;
		return -1;
	}
}





template <class T>
void ABB<T>::mostrar_in_order(NodoABB<T>* nodo) {

	if (nodo != nullptr) {
		mostrar_in_order(nodo -> get_izq());
		cout << nodo -> get_dato() << " ";
		mostrar_in_order(nodo -> get_der());
	}
}

template <class T>
void ABB<T>::mostrar_in_order() {

	mostrar_in_order(this -> raiz);
	cout << endl;
}





template <class T>
void ABB<T>::borrar_todo(NodoABB<T>* nodo) {

	if (nodo) {
		this -> borrar_todo(nodo -> get_izq());
		this -> borrar_todo(nodo -> get_der());
		delete nodo;
	}
}

template <class T>
void ABB<T>::borrar_todo() {

	this -> borrar_todo(this -> raiz);
}





template <class T>
ABB<T>::~ABB() {

	borrar_todo();
}


#endif /* ARBOL_H_ */
