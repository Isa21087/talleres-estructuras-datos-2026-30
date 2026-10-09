// Protección contra inclusión múltiple: si otro archivo ya incluyó este .h,
// NODOGENERAL_H ya está definido y el compilador se salta todo hasta el #endif.
// Así se evita que la clase quede declarada dos veces (error de compilación).
#ifndef NODOGENERAL_H
#define NODOGENERAL_H

#include <iostream> // para std::cout en los recorridos que hace el nodo
#include <list> // librería para usar std::list, donde se guardan los hijos del nodo

/* El NodoGeneral sabe:
   - cuál es su dato;
   - cuáles son sus hijos.
   No sabe si es raíz ni cómo está organizado todo el árbol.
   El ArbolGeneral es el encargado de tener la referencia a la raíz.
   En esta versión la RECURSIÓN SE HACE EN EL NODO: cada nodo resuelve la
   operación para sí mismo y le pide a cada uno de sus hijos que haga lo mismo
   con su propio subárbol. */

// template <class T>: la clase es una plantilla, puede guardar cualquier tipo de dato.
// El tipo real se define al crear el objeto, por ejemplo NodoGeneral<int>.
template <class T>
class NodoGeneral {
    protected: // solo la clase y sus clases hijas pueden acceder a estos atributos
        T dato; // dato que guarda el nodo

        // Se lee de adentro hacia afuera: NodoGeneral<T>* es un apuntador a un nodo
        // y std::list<...> es una lista de esos apuntadores.
        // La lista guarda la dirección de cada hijo, no una copia del nodo hijo.
        std::list<NodoGeneral<T>*> desc;
    public: // métodos que el resto del programa puede usar
        NodoGeneral(); // constructor: crea un nodo sin hijos
        ~NodoGeneral(); // destructor: libera el nodo y todos sus descendientes
        T& obtenerDato(); // devuelve por referencia el dato del nodo
        void fijarDato(T& val); // cambia el dato del nodo sin tocar sus hijos

        // Devuelve la lista de hijos POR REFERENCIA (&), es decir la lista original.
        // El árbol la necesita para el recorrido por niveles.
        std::list<NodoGeneral<T>*>& obtenerDesc();

        void limpiarLista(); // quita los apuntadores a los hijos (no libera su memoria)
        void adicionarDesc(T& nval); // crea un nodo hoja con el dato nval y lo agrega como hijo
        bool eliminarDesc(T& val); // elimina el hijo con dato val (y todo su subárbol); true si lo encontró
        bool esHoja(); // true si el nodo no tiene hijos

        // Operaciones recursivas: trabajan sobre el subárbol que tiene a este nodo como raíz
        bool insertarNodo(T padre, T n); // inserta n como hijo del nodo con dato padre
        bool eliminarNodo(T val); // elimina un descendiente con dato val (no a sí mismo)
        bool buscar(T n); // true si este nodo o algún descendiente tiene el dato n
        int altura(); // 0 si es hoja; si no, 1 + la altura de su hijo más alto
        unsigned int tamano(); // cantidad de nodos del subárbol, contándose a sí mismo
        void preOrden(); // imprime este nodo y luego sus hijos
        void posOrden(); // imprime sus hijos y luego este nodo
};

// Como es una plantilla, el compilador necesita ver la implementación junto con la
// declaración, por eso se incluye el .hxx al final del .h en vez de compilarlo aparte.
#include "NodoGeneral.hxx"

#endif
