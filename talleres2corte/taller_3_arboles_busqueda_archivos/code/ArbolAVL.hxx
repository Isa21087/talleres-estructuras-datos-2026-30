#include "ArbolAVL.h"


template< class T >
ArbolAVL<T>::ArbolAVL() {
    this->raiz = NULL; // el arbol empieza vacio
}


template< class T >
ArbolAVL<T>::~ArbolAVL() {

    if (!this->esVacio())
        delete this->raiz; // al borrar la raiz se borra todo el arbol

    this->raiz = NULL;
}


template< class T >
bool ArbolAVL<T>::esVacio() {
    return this->raiz == NULL; // si no hay raiz no hay arbol
}


template< class T >
T ArbolAVL<T>::datoRaiz() {
    return this->raiz->obtenerDato();
}


template< class T >
int ArbolAVL<T>::altura() {

    if (this->esVacio())
        return -1; // por convencion el arbol vacio tiene altura -1

    return this->raiz->altura(); // desde la raiz se calcula todo
}


template< class T >
int ArbolAVL<T>::tamano() {

    if (this->esVacio())
        return 0;

    return this->raiz->tamano(); // la raiz cuenta todos los nodos que tiene debajo
}


template< class T >
bool ArbolAVL<T>::insertar(T val) {

    if (this->esVacio()) {
        this->raiz = new NodoAVL<T>(val); // si esta vacio este dato se vuelve la raiz
        return true;
    }

    bool insertado = false; // el nodo nos va a avisar si si logro insertarlo

    this->raiz = this->raiz->insertar(val, insertado);
    // guardamos lo que devuelve porque una rotacion puede cambiar la raiz

    return insertado;
}


template< class T >
bool ArbolAVL<T>::eliminar(T val) {

    if (this->esVacio())
        return false; // si esta vacio no hay nada que borrar

    bool eliminado = false; // el nodo nos avisa si encontro el dato

    this->raiz = this->raiz->eliminar(val, eliminado);
    // igual que al insertar una rotacion puede cambiar quien queda de raiz

    return eliminado;
}


template< class T >
bool ArbolAVL<T>::buscar(T val) {

    NodoAVL<T>* nodo = this->raiz; // arrancamos buscando desde la raiz

    while (nodo != NULL) {

        if (val < nodo->obtenerDato()) {
            nodo = nodo->obtenerHijoIzq(); // si es menor solo puede estar a la izquierda
        }
        else if (val > nodo->obtenerDato()) {
            nodo = nodo->obtenerHijoDer(); // si es mayor solo puede estar a la derecha
        }
        else {
            return true; // si no es menor ni mayor entonces es igual
        }
    }

    return false; // llegamos a NULL y nunca lo encontramos
}


// el profe usa insert pero nosotros ya teniamos insertar
// entonces este solo conecta un nombre con el otro
template< class T >
bool ArbolAVL<T>::insert(T val) {
    return this->insertar(val);
}


// lo mismo pasa con erase y eliminar
template< class T >
bool ArbolAVL<T>::erase(T val) {
    return this->eliminar(val);
}


template< class T >
void ArbolAVL<T>::preOrden() {

    if (!this->esVacio())
        this->raiz->preOrden(); // el nodo hace la recursion
}


template< class T >
void ArbolAVL<T>::inOrden() {

    if (!this->esVacio())
        this->raiz->inOrden(); // izquierdo nodo derecho
}


template< class T >
void ArbolAVL<T>::posOrden() {

    if (!this->esVacio())
        this->raiz->posOrden();
}


// esto es nuevo para el taller
// necesitamos el inorden guardado en una lista y no solo impreso
template< class T >
void ArbolAVL<T>::inordenEnLista(std::list<T>& lista) {

    if (!this->esVacio())
        this->raiz->inordenEnLista(lista); // la recursion sigue estando en el nodo
}


template< class T >
void ArbolAVL<T>::nivelOrden() {

    if (this->esVacio())
        return;

    std::queue< NodoAVL<T>* > cola;

    cola.push(this->raiz); // empezamos metiendo la raiz

    while (!cola.empty()) {

        NodoAVL<T>* nodo = cola.front(); // miramos el primero
        cola.pop(); // y ahora si lo sacamos

        std::cout << nodo->obtenerDato() << " ";

        if (nodo->obtenerHijoIzq() != NULL)
            cola.push(nodo->obtenerHijoIzq()); // metemos primero el izquierdo

        if (nodo->obtenerHijoDer() != NULL)
            cola.push(nodo->obtenerHijoDer()); // despues el derecho
    }
}