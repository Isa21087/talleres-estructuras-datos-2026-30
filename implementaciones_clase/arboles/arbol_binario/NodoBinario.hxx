#include "NodoBinario.h"

template< class T >
NodoBinario<T>::NodoBinario() {
    this->hijoIzq = NULL;
    this->hijoDer = NULL;
}

template< class T >
NodoBinario<T>::NodoBinario(T val) {
    this->dato = val;
    this->hijoIzq = NULL;
    this->hijoDer = NULL;
}

template< class T >
NodoBinario<T>::~NodoBinario() {
    // al eliminar un nodo tambien se eliminan sus dos subarboles
    delete this->hijoIzq;
    delete this->hijoDer;

    this->hijoIzq = NULL;
    this->hijoDer = NULL;
}

template< class T >
T NodoBinario<T>::obtenerDato() {
    return this->dato;
}

template< class T >
void NodoBinario<T>::fijarDato(T val) {
    this->dato = val;
}

template< class T >
NodoBinario<T>* NodoBinario<T>::obtenerHijoIzq() {
    return this->hijoIzq;
}

template< class T >
NodoBinario<T>* NodoBinario<T>::obtenerHijoDer() {
    return this->hijoDer;
}

template< class T >
void NodoBinario<T>::fijarHijoIzq(NodoBinario<T>* izq) {
    this->hijoIzq = izq;
}

template< class T >
void NodoBinario<T>::fijarHijoDer(NodoBinario<T>* der) {
    this->hijoDer = der;
}

template< class T >
bool NodoBinario<T>::esHoja() {
    return this->hijoIzq == NULL && this->hijoDer == NULL;
}

template< class T >
NodoBinario<T>* NodoBinario<T>::buscarNodo(T val) {
    // como no es un arbol ordenado, la busqueda puede necesitar revisar ambos lados
    if (this->dato == val)
        return this;

    NodoBinario<T>* encontrado = NULL;

    if (this->hijoIzq != NULL)
        encontrado = this->hijoIzq->buscarNodo(val);

    if (encontrado == NULL && this->hijoDer != NULL)
        encontrado = this->hijoDer->buscarNodo(val);

    return encontrado;
}

template< class T >
bool NodoBinario<T>::eliminarNodo(T val) {
    // el padre revisa a sus hijos porque es quien guarda los apuntadores hacia ellos
    if (this->hijoIzq != NULL && this->hijoIzq->obtenerDato() == val) {
        delete this->hijoIzq;
        this->hijoIzq = NULL;
        return true;
    }

    if (this->hijoDer != NULL && this->hijoDer->obtenerDato() == val) {
        delete this->hijoDer;
        this->hijoDer = NULL;
        return true;
    }

    if (this->hijoIzq != NULL && this->hijoIzq->eliminarNodo(val))
        return true;

    if (this->hijoDer != NULL && this->hijoDer->eliminarNodo(val))
        return true;

    return false;
}

template< class T >
int NodoBinario<T>::altura() {
    int alturaIzq = -1;
    int alturaDer = -1;

    if (this->hijoIzq != NULL)
        alturaIzq = this->hijoIzq->altura();

    if (this->hijoDer != NULL)
        alturaDer = this->hijoDer->altura();

    if (alturaIzq > alturaDer)
        return alturaIzq + 1;

    return alturaDer + 1;
}

template< class T >
int NodoBinario<T>::tamano() {
    int tam = 1;

    if (this->hijoIzq != NULL)
        tam += this->hijoIzq->tamano();

    if (this->hijoDer != NULL)
        tam += this->hijoDer->tamano();

    return tam;
}

template< class T >
void NodoBinario<T>::preOrden() {
    std::cout << this->dato << " ";

    if (this->hijoIzq != NULL)
        this->hijoIzq->preOrden();

    if (this->hijoDer != NULL)
        this->hijoDer->preOrden();
}

template< class T >
void NodoBinario<T>::inOrden() {
    if (this->hijoIzq != NULL)
        this->hijoIzq->inOrden();

    std::cout << this->dato << " ";

    if (this->hijoDer != NULL)
        this->hijoDer->inOrden();
}

template< class T >
void NodoBinario<T>::posOrden() {
    if (this->hijoIzq != NULL)
        this->hijoIzq->posOrden();

    if (this->hijoDer != NULL)
        this->hijoDer->posOrden();

    std::cout << this->dato << " ";
}
