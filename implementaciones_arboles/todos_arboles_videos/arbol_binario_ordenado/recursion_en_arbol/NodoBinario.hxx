// Implementación de los métodos de NodoBinario
#include "NodoBinario.h"

template <class T>
NodoBinario<T>::NodoBinario() {
    // Un nodo nuevo no tiene hijos: se dejan ambos apuntadores en NULL
    // para que nunca apunten a una dirección de memoria basura
    this->hijoIzq = NULL;
    this->hijoDer = NULL;
}

template <class T>
NodoBinario<T>::NodoBinario(T val) {
    // Igual que el constructor vacío, pero de una vez guarda el dato
    this->dato = val;
    this->hijoIzq = NULL;
    this->hijoDer = NULL;
}

template <class T>
NodoBinario<T>::~NodoBinario() {
    // Borrar cada hijo llama a SU destructor, que borra a sus hijos, y así
    // en cascada se libera todo el subárbol. Hacer delete de NULL no hace nada,
    // por eso no hace falta preguntar antes si el hijo existe.
    delete this->hijoIzq;
    delete this->hijoDer;
    this->hijoIzq = NULL;
    this->hijoDer = NULL;
}

template <class T>
T NodoBinario<T>::obtenerDato() {
    return this->dato;
}

template <class T>
void NodoBinario<T>::fijarDato(T val) {
    this->dato = val;
}

template <class T>
NodoBinario<T>* NodoBinario<T>::obtenerHijoIzq() {
    return this->hijoIzq;
}

template <class T>
NodoBinario<T>* NodoBinario<T>::obtenerHijoDer() {
    return this->hijoDer;
}

template <class T>
void NodoBinario<T>::fijarHijoIzq(NodoBinario<T>* izq) {
    // Solo cambia el apuntador: no libera el hijo izquierdo que había antes
    this->hijoIzq = izq;
}

template <class T>
void NodoBinario<T>::fijarHijoDer(NodoBinario<T>* der) {
    // Solo cambia el apuntador: no libera el hijo derecho que había antes
    this->hijoDer = der;
}

template <class T>
bool NodoBinario<T>::esHoja() {
    // Es hoja cuando no tiene ni hijo izquierdo ni hijo derecho
    return (this->hijoIzq == NULL && this->hijoDer == NULL);
}
