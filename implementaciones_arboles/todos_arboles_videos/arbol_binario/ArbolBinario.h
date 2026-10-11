#ifndef __ARBOLBINARIO_H__
#define __ARBOLBINARIO_H__

#include <queue>
#include "NodoBinario.h"

template< class T >
class ArbolBinario {
protected:
    NodoBinario<T>* raiz;

public:
    ArbolBinario();
    ArbolBinario(T val);
    ~ArbolBinario();

    bool esVacio();
    T datoRaiz();
    int altura();
    int tamano();

    bool insertar(T padre, T val);
    bool eliminar(T val);
    bool buscar(T val);

    void preOrden();
    void inOrden();
    void posOrden();
    void nivelOrden();
};

#include "ArbolBinario.hxx"

#endif
