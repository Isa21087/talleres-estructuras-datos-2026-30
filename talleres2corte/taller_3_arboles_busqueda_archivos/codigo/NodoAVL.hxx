#include "NodoAVL.h"

template< class T >
NodoAVL<T>::NodoAVL() {
    this->hijoIzq = NULL;
    this->hijoDer = NULL;
}

template< class T >
NodoAVL<T>::NodoAVL(T val) {
    this->dato = val;
    this->hijoIzq = NULL;
    this->hijoDer = NULL;
}

template< class T >
NodoAVL<T>::~NodoAVL() {
    // al borrar un nodo tambien se van borrando sus hijos
    delete this->hijoIzq;
    delete this->hijoDer;

    this->hijoIzq = NULL;
    this->hijoDer = NULL;
}

template< class T >
T NodoAVL<T>::obtenerDato() {
    return this->dato;
}

template< class T >
void NodoAVL<T>::fijarDato(T val) {
    this->dato = val;
}

template< class T >
NodoAVL<T>* NodoAVL<T>::obtenerHijoIzq() {
    return this->hijoIzq;
}

template< class T >
NodoAVL<T>* NodoAVL<T>::obtenerHijoDer() {
    return this->hijoDer;
}

template< class T >
void NodoAVL<T>::fijarHijoIzq(NodoAVL<T>* izq) {
    this->hijoIzq = izq;
}

template< class T >
void NodoAVL<T>::fijarHijoDer(NodoAVL<T>* der) {
    this->hijoDer = der;
}

template< class T >
bool NodoAVL<T>::esHoja() {
    return this->hijoIzq == NULL && this->hijoDer == NULL;
}


// calcula la altura desde este nodo
template< class T >
int NodoAVL<T>::altura() {

    if (this->esHoja())
        return 0;

    int altIzq = -1;
    int altDer = -1;

    if (this->hijoIzq != NULL)
        altIzq = this->hijoIzq->altura();

    if (this->hijoDer != NULL)
        altDer = this->hijoDer->altura();

    if (altIzq > altDer)
        return altIzq + 1;

    return altDer + 1;
}


// cuenta este nodo y despues los de sus hijos
template< class T >
int NodoAVL<T>::tamano() {

    int tam = 1;

    if (this->hijoIzq != NULL)
        tam += this->hijoIzq->tamano();

    if (this->hijoDer != NULL)
        tam += this->hijoDer->tamano();

    return tam;
}


template< class T >
void NodoAVL<T>::preOrden() {

    std::cout << this->dato << " ";

    if (this->hijoIzq != NULL)
        this->hijoIzq->preOrden();

    if (this->hijoDer != NULL)
        this->hijoDer->preOrden();
}


template< class T >
void NodoAVL<T>::inOrden() {

    if (this->hijoIzq != NULL)
        this->hijoIzq->inOrden();

    std::cout << this->dato << " ";

    if (this->hijoDer != NULL)
        this->hijoDer->inOrden();
}


template< class T >
void NodoAVL<T>::posOrden() {

    if (this->hijoIzq != NULL)
        this->hijoIzq->posOrden();

    if (this->hijoDer != NULL)
        this->hijoDer->posOrden();

    std::cout << this->dato << " ";
}


// nuevo para el taller
// es exactamente el mismo recorrido inorden
// solo que en vez de mostrar el dato lo guardamos en la lista
template< class T >
void NodoAVL<T>::inordenEnLista(std::list<T>& lista) {

    if (this->hijoIzq != NULL)
        this->hijoIzq->inordenEnLista(lista);

    lista.push_back(this->dato);

    if (this->hijoDer != NULL)
        this->hijoDer->inordenEnLista(lista);
}


// busca donde insertar como en un arbol ordenado
// cuando vuelve de la recursion va balanceando
template< class T >
NodoAVL<T>* NodoAVL<T>::insertar(T val, bool& insertado) {

    if (val < this->dato) {

        if (this->hijoIzq == NULL) {
            this->hijoIzq = new NodoAVL<T>(val);
            insertado = true;
        }
        else {
            this->hijoIzq = this->hijoIzq->insertar(val, insertado);
        }

    }
    else if (val > this->dato) {

        if (this->hijoDer == NULL) {
            this->hijoDer = new NodoAVL<T>(val);
            insertado = true;
        }
        else {
            this->hijoDer = this->hijoDer->insertar(val, insertado);
        }

    }
    else {
        // ya estaba entonces no lo repetimos
        insertado = false;
        return this;
    }

    return this->balancear();
}


// busca el dato y despues de eliminar vuelve balanceando
template< class T >
NodoAVL<T>* NodoAVL<T>::eliminar(T val, bool& eliminado) {

    if (val < this->dato) {

        if (this->hijoIzq != NULL)
            this->hijoIzq = this->hijoIzq->eliminar(val, eliminado);

    }
    else if (val > this->dato) {

        if (this->hijoDer != NULL)
            this->hijoDer = this->hijoDer->eliminar(val, eliminado);

    }
    else {

        eliminado = true;

        // si tiene los dos hijos buscamos el mayor de la izquierda
        // ese dato puede reemplazar el que queremos eliminar
        if (this->hijoIzq != NULL && this->hijoDer != NULL) {

            NodoAVL<T>* maximo = this->hijoIzq;

            while (maximo->obtenerHijoDer() != NULL)
                maximo = maximo->obtenerHijoDer();

            this->dato = maximo->obtenerDato();

            this->hijoIzq =
                this->hijoIzq->eliminar(this->dato, eliminado);
        }
        else {

            // si tiene un hijo ese hijo ocupa su lugar
            // si es hoja reemplazo simplemente queda NULL
            NodoAVL<T>* reemplazo;

            if (this->hijoIzq != NULL)
                reemplazo = this->hijoIzq;
            else
                reemplazo = this->hijoDer;

            // los desconectamos antes del delete
            // porque el destructor tambien intenta borrar los hijos
            this->hijoIzq = NULL;
            this->hijoDer = NULL;

            delete this;

            return reemplazo;
        }
    }

    return this->balancear();
}


// izquierda menos derecha
template< class T >
int NodoAVL<T>::diferenciaAltura() {

    int altIzq = -1;
    int altDer = -1;

    if (this->hijoIzq != NULL)
        altIzq = this->hijoIzq->altura();

    if (this->hijoDer != NULL)
        altDer = this->hijoDer->altura();

    return altIzq - altDer;
}


// sube el hijo izquierdo
template< class T >
NodoAVL<T>* NodoAVL<T>::rotarDerecha() {

    NodoAVL<T>* nuevoPadre = this->hijoIzq;

    this->hijoIzq = nuevoPadre->hijoDer;

    nuevoPadre->hijoDer = this;

    return nuevoPadre;
}


// sube el hijo derecho
template< class T >
NodoAVL<T>* NodoAVL<T>::rotarIzquierda() {

    NodoAVL<T>* nuevoPadre = this->hijoDer;

    this->hijoDer = nuevoPadre->hijoIzq;

    nuevoPadre->hijoIzq = this;

    return nuevoPadre;
}


// primero izquierda sobre el hijo y despues derecha sobre este nodo
template< class T >
NodoAVL<T>* NodoAVL<T>::rotarIzqDer() {

    this->hijoIzq = this->hijoIzq->rotarIzquierda();

    return this->rotarDerecha();
}


// primero derecha sobre el hijo y despues izquierda sobre este nodo
template< class T >
NodoAVL<T>* NodoAVL<T>::rotarDerIzq() {

    this->hijoDer = this->hijoDer->rotarDerecha();

    return this->rotarIzquierda();
}


// aca miramos si el nodo se salio del rango permitido del AVL
template< class T >
NodoAVL<T>* NodoAVL<T>::balancear() {

    int diferencia = this->diferenciaAltura();

    // esta mas pesado a la izquierda
    if (diferencia > 1) {

        if (this->hijoIzq->diferenciaAltura() >= 0)
            return this->rotarDerecha();

        return this->rotarIzqDer();
    }

    // esta mas pesado a la derecha
    if (diferencia < -1) {

        if (this->hijoDer->diferenciaAltura() <= 0)
            return this->rotarIzquierda();

        return this->rotarDerIzq();
    }

    // si esta entre -1 y 1 ya esta balanceado
    return this;
}