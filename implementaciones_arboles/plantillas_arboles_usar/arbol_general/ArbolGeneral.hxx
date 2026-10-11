// Implementación de ArbolGeneral con la recursión hecha EN EL NODO.
// El árbol maneja los casos generales y le delega el trabajo a la raíz.
#include "ArbolGeneral.h"

template <class T>
ArbolGeneral<T>::ArbolGeneral() {
    // Árbol vacío: la raíz no apunta a ningún nodo
    this->raiz = NULL;
}

template <class T>
ArbolGeneral<T>::ArbolGeneral(T val) {
    NodoGeneral<T>* nodo = new NodoGeneral<T>(); // se crea el nodo en memoria dinámica
    nodo->fijarDato(val); // se le asigna el dato recibido
    this->raiz = nodo; // ese nodo pasa a ser la raíz
}

template <class T>
ArbolGeneral<T>::~ArbolGeneral() {
    // Borrar la raíz llama al destructor del nodo, que borra en cascada a todos
    // sus hijos; así se libera el árbol completo con una sola instrucción
    delete this->raiz;
    this->raiz = NULL; // se deja la raíz en NULL para no apuntar a memoria liberada
}

template <class T>
bool ArbolGeneral<T>::esVacio() {
    // El árbol está vacío cuando no hay raíz
    return this->raiz == NULL;
}

template <class T>
NodoGeneral<T>* ArbolGeneral<T>::obtenerRaiz() {
    return this->raiz;
}

template <class T>
void ArbolGeneral<T>::fijarRaiz(NodoGeneral<T>* nodo) {
    // Solo cambia el apuntador; no libera la raíz anterior
    this->raiz = nodo;
}

template <class T>
bool ArbolGeneral<T>::insertarNodo(T padre, T n) {
    // si el arbol esta vacio, crear nuevo nodo, asignar dato, poner ese nodo como raiz
    // (en este caso no importa el padre, el nuevo nodo es la raíz)
    if (esVacio()) {
        NodoGeneral<T>* nodo = new NodoGeneral<T>();
        nodo->fijarDato(n);
        this->raiz = nodo;
        return true;
    }
    // si no, la raíz se encarga de buscar al padre en todo su subárbol
    return this->raiz->insertarNodo(padre, n);
}

template <class T>
bool ArbolGeneral<T>::eliminarNodo(T val) {
    if (esVacio()) {
        return false;
    }
    // si es la raiz la que quiero eliminar:
    // - hacer delete a raiz (se borra todo el árbol en cascada)
    // - poner raiz en nulo
    // Este caso lo resuelve el árbol porque la raíz no tiene un padre que la elimine
    if (this->raiz->obtenerDato() == val) {
        delete this->raiz;
        this->raiz = NULL;
        return true;
    }
    // si no es la raíz, la raíz busca y elimina entre sus descendientes
    return this->raiz->eliminarNodo(val);
}

template <class T>
bool ArbolGeneral<T>::buscar(T n) {
    // en un árbol vacío no hay nada que buscar
    if (esVacio()) {
        return false;
    }
    return this->raiz->buscar(n);
} 

template <class T>
int ArbolGeneral<T>::altura() {
    // Se usa int (no unsigned) porque el árbol vacío tiene altura -1.
    // La altura del árbol es la altura de su raíz.
    if (esVacio()) {
        return -1;
    } else {
        return this->raiz->altura();
    }
}

template <class T>
unsigned int ArbolGeneral<T>::tamano() {
    // si esta vacio, retornar 0; si no, el tamaño del árbol es el del subárbol de la raíz
    if (esVacio()) {
        return 0;
    }
    return this->raiz->tamano();
}

template <class T>
void ArbolGeneral<T>::preOrden() {
    // si hay raíz, ella empieza el recorrido
    if (!this->esVacio()) {
        (this->raiz)->preOrden();
    }
}

template <class T>
void ArbolGeneral<T>::posOrden() {
    // si hay raíz, ella empieza el recorrido
    if (!this->esVacio()) {
        (this->raiz)->posOrden();
    }
}

template <class T>
void ArbolGeneral<T>::nivelOrden() {
    // NO ES RECURSIVO, por eso se queda en el árbol y no en el nodo
    // poner la raiz en una cola
    // hacer un ciclo mientras haya algo en la cola
    // - saco el primero diponible en la cola
    // - imprimo su dato
    // - inserto en la cola todos sus hijos
    // La cola (primero en entrar, primero en salir) hace que se termine un nivel
    // completo antes de empezar el siguiente.
    if (this->esVacio()) {
        return;
    }
    std::queue<NodoGeneral<T>*> cola; // cola de apuntadores a nodos pendientes por imprimir
    cola.push(this->raiz);
    while (!cola.empty()) {
        NodoGeneral<T>* nodo = cola.front(); // front() consulta el primero de la cola...
        cola.pop(); // ...y pop() lo saca (pop no devuelve el elemento)
        std::cout << nodo->obtenerDato() << " ";
        // "typename" es obligatorio porque iterator depende de T (ver NodoGeneral.hxx)
        typename std::list<NodoGeneral<T>*>::iterator it;
        for (it = nodo->obtenerDesc().begin(); it != nodo->obtenerDesc().end(); it++) {
            cola.push(*it); // los hijos quedan al final de la cola, detrás del nivel actual
        }
    }
}
