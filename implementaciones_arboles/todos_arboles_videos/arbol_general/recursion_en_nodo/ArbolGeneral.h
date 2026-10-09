// Protección contra inclusión múltiple (ver explicación en NodoGeneral.h)
#ifndef ARBOLGENERAL_H
#define ARBOLGENERAL_H

#include <queue> // para std::queue, usada en el recorrido por niveles
#include "NodoGeneral.h" // el árbol está formado por nodos generales (que ya incluye <iostream>)

/* El ArbolGeneral solo guarda un apuntador a la raíz; desde ella se llega a
   todos los demás nodos a través de las listas de hijos.
   En esta versión la RECURSIÓN SE HACE EN EL NODO: el árbol solo revisa los
   casos generales (árbol vacío, raíz) y le delega el trabajo a la raíz,
   llamando this->raiz->operacion(). Por eso el árbol no necesita métodos
   auxiliares que reciban nodos. */
template <class T>
class ArbolGeneral {
    protected:
        NodoGeneral<T>* raiz; // apuntador a la raíz; NULL si el árbol está vacío
    public:
        ArbolGeneral(); // crea un árbol vacío
        ArbolGeneral(T val); // crea un árbol con una raíz que guarda val
        ~ArbolGeneral(); // libera todos los nodos del árbol
        bool esVacio(); // true si el árbol no tiene raíz
        NodoGeneral<T>* obtenerRaiz(); // devuelve el apuntador a la raíz
        void fijarRaiz(NodoGeneral<T>* nodo); // cambia la raíz por el nodo dado
        bool insertarNodo(T padre, T n); // inserta n como hijo del nodo con dato padre
        bool eliminarNodo(T val); // elimina el nodo con dato val y todo su subárbol
        bool buscar(T n); // true si algún nodo del árbol tiene el dato n
        int altura(); // altura del árbol: -1 si está vacío, 0 si solo tiene raíz
        unsigned int tamano(); // cantidad de nodos del árbol
        void preOrden(); // imprime: nodo actual y luego sus hijos
        void posOrden(); // imprime: hijos y luego el nodo actual
        void nivelOrden(); // imprime nivel por nivel, de izquierda a derecha
};

// La implementación se incluye aquí porque la clase es una plantilla
#include "ArbolGeneral.hxx"

#endif
