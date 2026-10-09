#ifndef NODOGENERAL_H
#define NODOGENERAL_H

#include <iostream>
#include <list>

// El nodo guarda su dato y la lista de apuntadores a sus descendientes directos.
template <class T>
class NodoGeneral {
protected:
    T dato;
    std::list<NodoGeneral<T>*> desc;

public:
    NodoGeneral();
    ~NodoGeneral();

    T& obtenerDato();
    void fijarDato(T& val);
    std::list<NodoGeneral<T>*>& obtenerDesc();

    void limpiarLista();
    void adicionarDesc(T& nval);
    void eliminarDesc(T& val);
    bool esHoja();

    // En esta version la recursion se hace desde el nodo.
    bool insertarNodo(T& padre, T& n);
    bool eliminarNodo(T& val);
    bool buscar(T& n);
    int altura();
    unsigned int tamano();
    void preOrden();
    void posOrden();
};

#include "NodoGeneral.hxx"

#endif
