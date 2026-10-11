#ifndef ARBOLRN_H
#define ARBOLRN_H

#include <set>
#include <list>

template <class T>
class arbolRN {

protected:
    std::set<T> datos; //set usa internamente un arbol rojinegro

public:
    arbolRN();

    bool insert(T val); //inserta un dato
    bool erase(T val); //elimina un dato

    void inordenEnLista(std::list<T>& lista); //guarda los datos ordenados en una lista
};

#include "arbolRN.hxx"

#endif