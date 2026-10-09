#include "NodoGeneral.h"

template <class T>
NodoGeneral<T>::NodoGeneral() {
    this->desc.clear();
}

template <class T>
NodoGeneral<T>::~NodoGeneral() {
    this->limpiarLista();
}

template <class T>
T& NodoGeneral<T>::obtenerDato() {
    return this->dato;
}

template <class T>
void NodoGeneral<T>::fijarDato(T& val) {
    this->dato = val;
}

template <class T>
std::list<NodoGeneral<T>*>& NodoGeneral<T>::obtenerDesc() {
    return this->desc;
}

template <class T>
void NodoGeneral<T>::limpiarLista() {
    typename std::list<NodoGeneral<T>*>::iterator it;

    for (it = this->desc.begin(); it != this->desc.end(); it++) {
        delete *it;
    }

    this->desc.clear();
}

template <class T>
void NodoGeneral<T>::adicionarDesc(T& nval) {
    NodoGeneral<T>* nodo = new NodoGeneral<T>();
    nodo->fijarDato(nval);
    this->desc.push_back(nodo);
}

template <class T>
void NodoGeneral<T>::eliminarDesc(T& val) {
    typename std::list<NodoGeneral<T>*>::iterator it;

    for (it = this->desc.begin(); it != this->desc.end(); it++) {
        if ((*it)->obtenerDato() == val) {
            // Al eliminar el hijo tambien se elimina el subarbol que depende de el.
            delete *it;
            this->desc.erase(it);
            return;
        }
    }
}

template <class T>
bool NodoGeneral<T>::esHoja() {
    return this->desc.size() == 0;
}

template <class T>
bool NodoGeneral<T>::insertarNodo(T& padre, T& n) {
    if (this->dato == padre) {
        this->adicionarDesc(n);
        return true;
    }

    typename std::list<NodoGeneral<T>*>::iterator it;

    for (it = this->desc.begin(); it != this->desc.end(); it++) {
        if ((*it)->insertarNodo(padre, n)) {
            return true;
        }
    }

    return false;
}

template <class T>
bool NodoGeneral<T>::eliminarNodo(T& val) {
    typename std::list<NodoGeneral<T>*>::iterator it;

    // El padre es quien tiene la referencia que debe quitar de la lista.
    for (it = this->desc.begin(); it != this->desc.end(); it++) {
        if ((*it)->obtenerDato() == val) {
            this->eliminarDesc(val);
            return true;
        }
    }

    for (it = this->desc.begin(); it != this->desc.end(); it++) {
        if ((*it)->eliminarNodo(val)) {
            return true;
        }
    }

    return false;
}

template <class T>
bool NodoGeneral<T>::buscar(T& n) {
    if (this->dato == n) {
        return true;
    }

    typename std::list<NodoGeneral<T>*>::iterator it;

    for (it = this->desc.begin(); it != this->desc.end(); it++) {
        if ((*it)->buscar(n)) {
            return true;
        }
    }

    return false;
}

template <class T>
int NodoGeneral<T>::altura() {
    if (this->esHoja()) {
        return 0;
    }

    int mayor = -1;
    typename std::list<NodoGeneral<T>*>::iterator it;

    for (it = this->desc.begin(); it != this->desc.end(); it++) {
        int alturaHijo = (*it)->altura();
        if (alturaHijo > mayor) {
            mayor = alturaHijo;
        }
    }

    return mayor + 1;
}

template <class T>
unsigned int NodoGeneral<T>::tamano() {
    unsigned int cantidad = 1;
    typename std::list<NodoGeneral<T>*>::iterator it;

    for (it = this->desc.begin(); it != this->desc.end(); it++) {
        cantidad += (*it)->tamano();
    }

    return cantidad;
}

template <class T>
void NodoGeneral<T>::preOrden() {
    std::cout << this->dato << " ";

    typename std::list<NodoGeneral<T>*>::iterator it;
    for (it = this->desc.begin(); it != this->desc.end(); it++) {
        (*it)->preOrden();
    }
}

template <class T>
void NodoGeneral<T>::posOrden() {
    typename std::list<NodoGeneral<T>*>::iterator it;
    for (it = this->desc.begin(); it != this->desc.end(); it++) {
        (*it)->posOrden();
    }

    std::cout << this->dato << " ";
}
