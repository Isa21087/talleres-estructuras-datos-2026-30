#ifndef MONTICULO_H
#define MONTICULO_H

#include <deque>
#include <list>
#include <algorithm>

template <class T>
class monticulo {

protected:
    std::deque<T> datos; //contenedor donde se guarda el monticulo

public:
    monticulo();

    bool insert(T val); //inserta un dato
    bool erase(T val); //elimina un dato

    void inordenEnLista(std::list<T>& lista); //guarda los datos ordenados
};

#include "monticulo.hxx"

#endif