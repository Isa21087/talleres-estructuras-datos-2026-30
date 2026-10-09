#include "ArbolGeneral.h"

template <class T>
ArbolGeneral<T>::ArbolGeneral() {
    this->raiz = NULL;
}

template <class T>
ArbolGeneral<T>::ArbolGeneral(T& val) {
    NodoGeneral<T>* nodo = new NodoGeneral<T>();
    nodo->fijarDato(val);
    this->raiz = nodo;
}

template <class T>
ArbolGeneral<T>::~ArbolGeneral() {
    delete this->raiz;
    this->raiz = NULL;
}

template <class T>
bool ArbolGeneral<T>::esVacio() {
    return this->raiz == NULL;
}

template <class T>
NodoGeneral<T>* ArbolGeneral<T>::obtenerRaiz() {
    return this->raiz;
}

template <class T>
void ArbolGeneral<T>::fijarRaiz(NodoGeneral<T>* nraiz) {
    this->raiz = nraiz;
}

template <class T>
bool ArbolGeneral<T>::insertarNodo(T& padre, T& n) {
    // Si el arbol esta vacio no existe un padre donde insertar.
    if (this->esVacio()) {
        return false;
    }

    return this->raiz->insertarNodo(padre, n);
}

template <class T>
bool ArbolGeneral<T>::eliminarNodo(T& n) {
    if (this->esVacio()) {
        return false;
    }

    // La raiz no tiene padre, por eso este caso se resuelve desde el arbol.
    if (this->raiz->obtenerDato() == n) {
        delete this->raiz;
        this->raiz = NULL;
        return true;
    }

    return this->raiz->eliminarNodo(n);
}

template <class T>
bool ArbolGeneral<T>::buscar(T& n) {
    if (this->esVacio()) {
        return false;
    }

    return this->raiz->buscar(n);
}

template <class T>
int ArbolGeneral<T>::altura() {
    // Se usa int porque por definicion el arbol vacio tiene altura -1.
    if (this->esVacio()) {
        return -1;
    }

    return this->raiz->altura();
}

template <class T>
unsigned int ArbolGeneral<T>::tamano() {
    if (this->esVacio()) {
        return 0;
    }

    return this->raiz->tamano();
}

template <class T>
void ArbolGeneral<T>::preOrden() {
    if (!this->esVacio()) {
        this->raiz->preOrden();
    }
}

template <class T>
void ArbolGeneral<T>::posOrden() {
    if (!this->esVacio()) {
        this->raiz->posOrden();
    }
}

template <class T>
void ArbolGeneral<T>::nivelOrden() {
    if (this->esVacio()) {
        return;
    }

    std::queue<NodoGeneral<T>*> cola;
    cola.push(this->raiz);

    while (!cola.empty()) {
        NodoGeneral<T>* nodo = cola.front();
        cola.pop();

        std::cout << nodo->obtenerDato() << " ";

        typename std::list<NodoGeneral<T>*>::iterator it;
        for (it = nodo->obtenerDesc().begin(); it != nodo->obtenerDesc().end(); it++) {
            cola.push(*it);
        }
    }
}
