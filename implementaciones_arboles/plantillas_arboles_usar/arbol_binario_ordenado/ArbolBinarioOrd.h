// Protección contra inclusión múltiple (ver explicación en NodoBinario.h)
#ifndef ARBOLBINARIOORD_H
#define ARBOLBINARIOORD_H

#include <queue> // para std::queue, usada en el recorrido por niveles
#include "NodoBinario.h" // el árbol está formado por nodos binarios (que ya incluye <iostream>)

/* Árbol binario ordenado (árbol binario de búsqueda):
   para CADA nodo, todos los datos de su subárbol izquierdo son menores que
   su dato y todos los de su subárbol derecho son mayores. No hay datos repetidos.

   Hay dos tipos de operaciones:
   - ITERATIVAS (insertar, eliminar, buscar, nivelOrden): gracias al orden,
     en cada nodo se sabe si hay que bajar por la izquierda o por la derecha,
     así que basta un ciclo que baje por una sola rama, sin recursión.
   - RECURRENTES (altura, tamaño, preOrden, inOrden, posOrden): tienen que
     visitar los dos subárboles de cada nodo.
   En esta versión la RECURSIÓN SE HACE EN EL NODO: el árbol revisa si está
   vacío y le delega el trabajo a la raíz con this->raiz->operacion(). */
template <class T>
class ArbolBinarioOrd {
    protected:
        NodoBinario<T>* raiz; // apuntador a la raíz; NULL si el árbol está vacío
    public:
        ArbolBinarioOrd(); // crea un árbol vacío
        ~ArbolBinarioOrd(); // libera todos los nodos del árbol
        bool esVacio(); // true si el árbol no tiene raíz
        T datoRaiz(); // dato guardado en la raíz (solo si el árbol no está vacío)
        int altura(); // -1 si está vacío, 0 si solo tiene raíz
        int tamano(); // cantidad de nodos del árbol
        bool insertar(T val); // false si val ya estaba (no se permiten repetidos)
        bool eliminar(T val); // false si val no está en el árbol
        bool buscar(T val); // true si val está en el árbol
        void preOrden(); // imprime: nodo, izquierdo, derecho
        void inOrden(); // imprime: izquierdo, nodo, derecho (sale ordenado de menor a mayor)
        void posOrden(); // imprime: izquierdo, derecho, nodo
        void nivelOrden(); // imprime nivel por nivel, de izquierda a derecha
};

// La implementación se incluye aquí porque la clase es una plantilla
#include "ArbolBinarioOrd.hxx"

#endif
