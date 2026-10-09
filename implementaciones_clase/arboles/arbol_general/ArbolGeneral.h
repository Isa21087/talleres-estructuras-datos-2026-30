#ifndef ARBOLGENERAL_H
#define ARBOLGENERAL_H

#include <queue>
#include "NodoGeneral.h"

// El arbol conserva la referencia a la raiz y delega la recursion al nodo.
template <class T>
class ArbolGeneral {
protected:
    NodoGeneral<T>* raiz;

public:
    ArbolGeneral();
    ArbolGeneral(T& val);
    ~ArbolGeneral();

    bool esVacio();
    NodoGeneral<T>* obtenerRaiz();
    void fijarRaiz(NodoGeneral<T>* nraiz);

    bool insertarNodo(T& padre, T& n);
    bool eliminarNodo(T& n);
    bool buscar(T& n);
    int altura();
    unsigned int tamano();

    void preOrden();
    void posOrden();
    void nivelOrden();
};

#include "ArbolGeneral.hxx"

#endif
