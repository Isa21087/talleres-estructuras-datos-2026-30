#ifndef __NODOAVL_H__
#define __NODOAVL_H__

#include <cstddef>
#include <iostream>
#include <list>

template< class T >
class NodoAVL {

    protected:
        T dato;

        NodoAVL<T>* hijoIzq;
        NodoAVL<T>* hijoDer;

    public:
        NodoAVL();
        NodoAVL(T val);
        ~NodoAVL();

        T obtenerDato();
        void fijarDato(T val);

        NodoAVL<T>* obtenerHijoIzq();
        NodoAVL<T>* obtenerHijoDer();

        void fijarHijoIzq(NodoAVL<T>* izq);
        void fijarHijoDer(NodoAVL<T>* der);

        bool esHoja();

        int altura();
        int tamano();

        void preOrden();
        void inOrden();
        void posOrden();

        // este es nuevo para el taller
        // hace el mismo inorden pero en vez de imprimir mete los datos en la lista
        void inordenEnLista(std::list<T>& lista);

        // al insertar o eliminar puede cambiar la raiz del subarbol por las rotaciones
        // por eso estos metodos devuelven un apuntador
        NodoAVL<T>* insertar(T val, bool& insertado);
        NodoAVL<T>* eliminar(T val, bool& eliminado);

        // diferencia entre la altura izquierda y derecha
        // si se sale de -1 0 1 toca balancear
        int diferenciaAltura();

        NodoAVL<T>* rotarDerecha();
        NodoAVL<T>* rotarIzquierda();
        NodoAVL<T>* rotarIzqDer();
        NodoAVL<T>* rotarDerIzq();

        NodoAVL<T>* balancear();
};

#include "NodoAVL.hxx"

#endif