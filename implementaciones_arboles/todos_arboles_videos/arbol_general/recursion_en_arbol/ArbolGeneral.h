// Protección contra inclusión múltiple (ver explicación en NodoGeneral.h)
#ifndef ARBOLGENERAL_H
#define ARBOLGENERAL_H

#include <iostream> // para std::cout en los recorridos
#include <queue> // para std::queue, usada en el recorrido por niveles
#include "NodoGeneral.h" // el árbol está formado por nodos generales

/* El ArbolGeneral solo guarda un apuntador a la raíz; desde ella se llega a
   todos los demás nodos a través de las listas de hijos.
   En esta versión la RECURSIÓN SE HACE EN EL ÁRBOL: cada operación pública
   revisa los casos generales (árbol vacío, raíz) y luego llama a una versión
   protegida del mismo nombre que recibe un nodo y se llama a sí misma
   sobre cada uno de los hijos. */
template <class T>
class ArbolGeneral {
    protected:
        NodoGeneral<T>* raiz; // apuntador a la raíz; NULL si el árbol está vacío

        // Métodos auxiliares recursivos: reciben el nodo desde donde se trabaja.
        // Son protected porque el usuario del árbol no maneja nodos directamente,
        // solo llama a las versiones públicas de abajo.
        bool insertarNodo(NodoGeneral<T>* nodo, T padre, T n);
        bool eliminarNodo(NodoGeneral<T>* nodo, T val);
        bool buscar(NodoGeneral<T>* nodo, T n);
        int altura(NodoGeneral<T>* nodo);
        unsigned int tamano(NodoGeneral<T>* nodo);
        void preOrden(NodoGeneral<T>* nodo);
        void posOrden(NodoGeneral<T>* nodo);
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
