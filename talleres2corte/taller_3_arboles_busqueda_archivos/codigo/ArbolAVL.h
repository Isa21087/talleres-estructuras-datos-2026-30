#ifndef __ARBOLAVL_H__
#define __ARBOLAVL_H__

#include <queue>
#include <list>

#include "NodoAVL.h"

template< class T >
class ArbolAVL {

    protected:
        NodoAVL<T>* raiz;

    public:
        ArbolAVL();
        ~ArbolAVL();

        bool esVacio();

        T datoRaiz();

        int altura();
        int tamano();

        // estos son los nombres que ya tenia nuestra implementacion
        bool insertar(T val);
        bool eliminar(T val);
        bool buscar(T val);

        // estos nombres los necesita la funcion generica del profe
        // simplemente llaman los metodos que ya teniamos
        bool insert(T val);
        bool erase(T val);

        void preOrden();
        void inOrden();
        void posOrden();
        void nivelOrden();

        // nuevo para el taller
        // guarda el inorden en una lista en vez de imprimirlo
        void inordenEnLista(std::list<T>& lista);
};

#include "ArbolAVL.hxx"

#endif