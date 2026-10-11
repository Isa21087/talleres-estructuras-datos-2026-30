#include "ArbolBinario.h"

template< class T >
ArbolBinario<T>::ArbolBinario() {
    this->raiz = NULL;
}

template< class T >
ArbolBinario<T>::ArbolBinario(T val) {
    this->raiz = new NodoBinario<T>(val);
}

template< class T >
ArbolBinario<T>::~ArbolBinario() {
    delete this->raiz;
    this->raiz = NULL;
}

template< class T >
bool ArbolBinario<T>::esVacio() {
    return this->raiz == NULL;
}

template< class T >
T ArbolBinario<T>::datoRaiz() {
    return this->raiz->obtenerDato();
}

template< class T >
int ArbolBinario<T>::altura() {
    if (this->esVacio())
        return -1;

    return this->raiz->altura();
}

template< class T >
int ArbolBinario<T>::tamano() {
    if (this->esVacio())
        return 0;

    return this->raiz->tamano();
}

template< class T >
bool ArbolBinario<T>::insertar(T padre, T val) {
    // si el arbol esta vacio, el primer dato se convierte en la raiz
    if (this->esVacio()) {
        this->raiz = new NodoBinario<T>(val);
        return true;
    }

    NodoBinario<T>* nodoPadre = this->raiz->buscarNodo(padre);

    if (nodoPadre == NULL)
        return false;

    // en esta implementacion se usa primero el espacio izquierdo y luego el derecho
    if (nodoPadre->obtenerHijoIzq() == NULL) {
        nodoPadre->fijarHijoIzq(new NodoBinario<T>(val));
        return true;
    }

    if (nodoPadre->obtenerHijoDer() == NULL) {
        nodoPadre->fijarHijoDer(new NodoBinario<T>(val));
        return true;
    }

    return false;
}

template< class T >
bool ArbolBinario<T>::eliminar(T val) {
    if (this->esVacio())
        return false;

    // la raiz se maneja desde el arbol porque no tiene un padre que la desconecte
    if (this->raiz->obtenerDato() == val) {
        delete this->raiz;
        this->raiz = NULL;
        return true;
    }

    return this->raiz->eliminarNodo(val);
}

template< class T >
bool ArbolBinario<T>::buscar(T val) {
    if (this->esVacio())
        return false;

    return this->raiz->buscarNodo(val) != NULL;
}

template< class T >
void ArbolBinario<T>::preOrden() {
    if (!this->esVacio())
        this->raiz->preOrden();
}

template< class T >
void ArbolBinario<T>::inOrden() {
    if (!this->esVacio())
        this->raiz->inOrden();
}

template< class T >
void ArbolBinario<T>::posOrden() {
    if (!this->esVacio())
        this->raiz->posOrden();
}

template< class T >
void ArbolBinario<T>::nivelOrden() {
    if (this->esVacio())
        return;

    std::queue< NodoBinario<T>* > cola;
    cola.push(this->raiz);

    while (!cola.empty()) {
        NodoBinario<T>* nodo = cola.front();
        cola.pop();

        std::cout << nodo->obtenerDato() << " ";

        if (nodo->obtenerHijoIzq() != NULL)
            cola.push(nodo->obtenerHijoIzq());

        if (nodo->obtenerHijoDer() != NULL)
            cola.push(nodo->obtenerHijoDer());
    }
}
