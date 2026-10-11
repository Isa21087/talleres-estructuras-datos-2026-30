// Protección contra inclusión múltiple: si otro archivo ya incluyó este .h,
// NODOBINARIO_H ya está definido y el compilador se salta todo hasta el #endif.
#ifndef NODOBINARIO_H
#define NODOBINARIO_H

#include <cstddef> // para poder usar NULL

/* El NodoBinario es como el NodoGeneral pero con MÁXIMO DOS hijos.
   En vez de una lista de hijos tiene dos apuntadores separados:
   - hijoIzq: subárbol con los datos MENORES que el dato del nodo;
   - hijoDer: subárbol con los datos MAYORES que el dato del nodo.
   Si no tiene alguno de los hijos, ese apuntador vale NULL.
   En esta versión el nodo NO tiene operaciones recursivas: toda la recursión
   (altura, tamaño, recorridos) la hace el árbol. */

// template <class T>: la clase es una plantilla, puede guardar cualquier tipo de dato
template <class T>
class NodoBinario {
    protected: // solo la clase y sus clases hijas pueden acceder a estos atributos
        T dato; // dato que guarda el nodo
        NodoBinario<T>* hijoIzq; // apuntador al hijo izquierdo (NULL si no tiene)
        NodoBinario<T>* hijoDer; // apuntador al hijo derecho (NULL si no tiene)
    public:
        NodoBinario(); // crea un nodo sin hijos
        NodoBinario(T val); // crea un nodo sin hijos que ya guarda el dato val
        ~NodoBinario(); // libera el nodo y todo su subárbol
        T obtenerDato(); // devuelve una copia del dato del nodo
        void fijarDato(T val); // cambia el dato del nodo sin tocar sus hijos
        NodoBinario<T>* obtenerHijoIzq(); // devuelve el apuntador al hijo izquierdo
        NodoBinario<T>* obtenerHijoDer(); // devuelve el apuntador al hijo derecho
        void fijarHijoIzq(NodoBinario<T>* izq); // conecta izq como hijo izquierdo
        void fijarHijoDer(NodoBinario<T>* der); // conecta der como hijo derecho
        bool esHoja(); // true si no tiene ninguno de los dos hijos
};

// Como es una plantilla, la implementación se incluye al final del .h
#include "NodoBinario.hxx"

#endif
