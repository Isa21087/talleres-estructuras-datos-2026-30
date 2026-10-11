#ifndef __NODOBINARIO_H__
#define __NODOBINARIO_H__

#include <cstddef>
#include <iostream>

template< class T >
class NodoBinario {
protected:
    T dato;
    NodoBinario<T>* hijoIzq;
    NodoBinario<T>* hijoDer;

public:
    NodoBinario();
    NodoBinario(T val);
    ~NodoBinario();

    T obtenerDato();
    void fijarDato(T val);

    NodoBinario<T>* obtenerHijoIzq();
    NodoBinario<T>* obtenerHijoDer();
    void fijarHijoIzq(NodoBinario<T>* izq);
    void fijarHijoDer(NodoBinario<T>* der);

    bool esHoja();

    NodoBinario<T>* buscarNodo(T val);
    bool eliminarNodo(T val);
    int altura();
    int tamano();

    void preOrden();
    void inOrden();
    void posOrden();
};

#include "NodoBinario.hxx"

#endif
