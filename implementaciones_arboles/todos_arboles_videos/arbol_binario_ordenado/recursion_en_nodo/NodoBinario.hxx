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

// recurrente
template <class T>
int NodoBinario<T>::altura() {
    int valt;

    if (this->esHoja()) {
        // un nodo sin hijos tiene altura 0
        valt = 0;
    } else {
        // Al menos tiene un hijo: se calcula la altura de cada hijo, se escoge
        // la mayor y se le suma 1 para contar este nodo.
        // Se inician en -1 por si falta alguno de los hijos.
        int valt_izq = -1;
        int valt_der = -1;
        // Aquí no se puede verificar "this != NULL" como en la versión del árbol:
        // si el hijo es NULL, no hay ningún nodo sobre el cual llamar altura().
        // Por eso se verifica que el hijo exista ANTES de hacer el llamado.
        if (this->hijoIzq != NULL)
            valt_izq = (this->hijoIzq)->altura();
        if (this->hijoDer != NULL)
            valt_der = (this->hijoDer)->altura();
        if (valt_izq > valt_der)
            valt = valt_izq + 1;
        else
            valt = valt_der + 1;
    }

    return valt;
}

// recurrente
template <class T>
int NodoBinario<T>::tamano() {
    // 1 por este nodo + los nodos de cada subárbol que exista
    int tam = 1;
    if (this->hijoIzq != NULL)
        tam += (this->hijoIzq)->tamano();
    if (this->hijoDer != NULL)
        tam += (this->hijoDer)->tamano();
    return tam;
}

// recurrente
template <class T>
void NodoBinario<T>::preOrden() {
    std::cout << this->dato << " "; // 1. visitar este nodo
    if (this->hijoIzq != NULL)
        (this->hijoIzq)->preOrden(); // 2. recorrer el izquierdo
    if (this->hijoDer != NULL)
        (this->hijoDer)->preOrden(); // 3. recorrer el derecho
}

// recurrente
template <class T>
void NodoBinario<T>::inOrden() {
    if (this->hijoIzq != NULL)
        (this->hijoIzq)->inOrden(); // 1. recorrer el izquierdo
    std::cout << this->dato << " "; // 2. visitar este nodo
    if (this->hijoDer != NULL)
        (this->hijoDer)->inOrden(); // 3. recorrer el derecho
}

// recurrente
template <class T>
void NodoBinario<T>::posOrden() {
    if (this->hijoIzq != NULL)
        (this->hijoIzq)->posOrden(); // 1. recorrer el izquierdo
    if (this->hijoDer != NULL)
        (this->hijoDer)->posOrden(); // 2. recorrer el derecho
    std::cout << this->dato << " "; // 3. visitar este nodo
}
