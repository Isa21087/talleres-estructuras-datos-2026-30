// Archivo con la implementación de los métodos de NodoGeneral.
// Se separa de la declaración (.h) para que sea más fácil de leer.

// Se incluye el .h para implementar los métodos según su declaración.
// Gracias a la protección #ifndef no se genera una inclusión infinita.
#include "NodoGeneral.h"

// Cada vez que se implementa un método de una clase plantilla hay que volver a
// escribir template <class T> y luego NodoGeneral<T>::nombreDelMetodo.

template <class T>
NodoGeneral<T>::NodoGeneral() {
    // La lista ya nace vacía, pero se limpia para asegurar que el nodo empiece sin hijos
    this->desc.clear();
}

template <class T>
NodoGeneral<T>::~NodoGeneral() {
    // Para liberar bien la memoria hay que recorrer los hijos y borrar cada uno.
    // "typename" es obligatorio porque iterator depende de T: le dice al compilador
    // que std::list<NodoGeneral<T>*>::iterator es un tipo y no una variable.
    typename std::list<NodoGeneral<T>*>::iterator it;
    for (it = desc.begin(); it != desc.end(); it++) {
        // *it es el apuntador guardado en esa posición de la lista.
        // delete *it borra el nodo hijo al que apunta, lo que llama a SU destructor,
        // y así se borra en cascada todo el subárbol de ese hijo.
        delete *it;
    }
    // delete liberó los nodos, pero la lista aún tiene los apuntadores (ya inválidos).
    // clear() quita esos apuntadores de la lista.
    desc.clear();
}

template <class T>
T& NodoGeneral<T>::obtenerDato() {
    // Devuelve por referencia: quien lo reciba puede leer y también modificar el dato original
    return this->dato;
}

template <class T>
void NodoGeneral<T>::fijarDato(T& val) {
    // Reemplaza el dato del nodo; los hijos siguen siendo los mismos
    this->dato = val;
}

template <class T>
std::list<NodoGeneral<T>*>& NodoGeneral<T>::obtenerDesc() {
    // Devuelve la lista original de hijos (no una copia) para que el árbol pueda recorrerla
    return this->desc;
}

template <class T>
void NodoGeneral<T>::limpiarLista() {
    // Deja al nodo sin hijos (como hoja). Ojo: solo quita los apuntadores,
    // no libera la memoria de los hijos.
    this->desc.clear();
}

template <class T>
void NodoGeneral<T>::adicionarDesc(T& nval) {
    NodoGeneral<T>* nodo = new NodoGeneral<T>(); // se reserva memoria para el nuevo nodo
    nodo->fijarDato(nval); // se le asigna el dato
    this->desc.push_back(nodo); // se agrega su dirección al final de la lista de hijos
}

template <class T>
bool NodoGeneral<T>::eliminarDesc(T& val) {
    // Buscar el nodo con el valor dado
    typename std::list<NodoGeneral<T>*>::iterator it;
    NodoGeneral<T>* aux; // apuntador auxiliar al hijo que se está revisando
    bool eliminado = false;
    for (it = desc.begin(); it != desc.end(); it++) {
        aux = *it;  
        if (aux->obtenerDato() == val) {
            break; // se encontró: el iterador queda parado en ese hijo
        }
    }

    // Si lo encontramos, lo eliminamos
    // (si no se encontró, el ciclo terminó con it == desc.end())
    if (it != desc.end()) {
        delete *it; // libera el hijo y, por su destructor, todo su subárbol
        this->desc.erase(it); // quita de la lista el apuntador a ese hijo
        eliminado = true;
    }
    return eliminado;
}

template <class T>
bool NodoGeneral<T>::esHoja() {
    // Un nodo es hoja cuando su lista de hijos está vacía
    return this->desc.size() == 0;
}
