// Implementación de ArbolGeneral con la recursión hecha EN EL ÁRBOL.
// Cada operación pública maneja los casos generales y llama a su versión
// auxiliar (protected) que recibe un nodo y se llama sobre cada hijo.
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
    if (this->esVacio()) {
        NodoGeneral<T>* nodo = new NodoGeneral<T>();
        nodo->fijarDato(n);
        this->raiz = nodo;
        return true;
    }
    // si hay al menos un nodo, se empieza a buscar el padre desde la raíz
    return this->insertarNodo(this->raiz, padre, n);
}

template <class T>
bool ArbolGeneral<T>::insertarNodo(NodoGeneral<T>* nodo, T padre, T n) {
    // - revisar el nodo donde estoy para ver si coincide con padre
    // - si es padre, insertar nuevo nodo como hijo
    // - si no es el padre, revisar cada nodo hijo y llamar a insertar allí
    if (nodo->obtenerDato() == padre) {
        nodo->adicionarDesc(n); // el nodo crea el hijo con el dato n
        return true;
    }
    typename std::list<NodoGeneral<T>*>::iterator it;
    for (it = nodo->obtenerDesc().begin(); it != nodo->obtenerDesc().end(); it++) {
        // *it es el apuntador a un hijo: se repite la búsqueda en su subárbol
        if (this->insertarNodo(*it, padre, n)) {
            return true; // ya se insertó, no hace falta seguir con los demás hijos
        }
    }
    // el padre no está en este subárbol
    return false;
}

template <class T>
bool ArbolGeneral<T>::eliminarNodo(T val) {
    // si el arbol es vacio:
    // retornar
    if (this->esVacio()) {
        return false;
    }
    // si es la raiz la que quiero eliminar:
    // - hacer delete a raiz (se borra todo el árbol en cascada)
    // - poner raiz en nulo
    if (this->raiz->obtenerDato() == val) {
        delete this->raiz;
        this->raiz = NULL;
        return true;
    }
    // si no es la raíz, se busca entre los descendientes
    return this->eliminarNodo(this->raiz, val);
}

template <class T>
bool ArbolGeneral<T>::eliminarNodo(NodoGeneral<T>* nodo, T val) {
    // - si alguno de los hijos es el que quiero eliminar, eliminarlo
    // - si ninguno de los hijos es el que quiero eliminar
    // - revisar cada nodo hijo y llamar a eliminar allí
    // - si no se encontro en ningun hijo, retornar false
    // Se elimina desde el padre porque es el padre quien tiene en su lista el
    // apuntador al hijo; así se puede quitar de la lista además de liberarlo.
    if (nodo->eliminarDesc(val)) {
        return true;
    }
    typename std::list<NodoGeneral<T>*>::iterator it;
    for (it = nodo->obtenerDesc().begin(); it != nodo->obtenerDesc().end(); it++) {
        if (this->eliminarNodo(*it, val)) {
            return true;
        }
    }
    return false;
}

template <class T>
bool ArbolGeneral<T>::buscar(T n) {
    // en un árbol vacío no hay nada que buscar
    if (this->esVacio()) {
        return false;
    }
    return this->buscar(this->raiz, n);
}

template <class T>
bool ArbolGeneral<T>::buscar(NodoGeneral<T>* nodo, T n) {
    // comparo dato en el nodo actual con dato parametro
    // si es ese, retorno que lo encontre
    // si no, para cada nodo hijo hacer el llamado a buscar
    if (nodo->obtenerDato() == n) {
        return true;
    }
    typename std::list<NodoGeneral<T>*>::iterator it;
    for (it = nodo->obtenerDesc().begin(); it != nodo->obtenerDesc().end(); it++) {
        if (this->buscar(*it, n)) {
            return true; // apenas un hijo lo encuentra se deja de buscar
        }
    }
    return false;
}

template <class T>
int ArbolGeneral<T>::altura() {
    // Se usa int (no unsigned) porque el árbol vacío tiene altura -1
    if (esVacio()) {
        return -1;
    } else {
        return this->altura(this->raiz);
    }
}

template <class T>
int ArbolGeneral<T>::altura(NodoGeneral<T>* nodo) {
    // La altura de un nodo es la cantidad de niveles que hay debajo de él:
    // una hoja tiene altura 0 y cualquier otro nodo tiene 1 + la altura de su hijo más alto
    int alt = -1;
    if (nodo->esHoja()) {
        alt = 0;
    } else {
        int alth; // altura del hijo que se está revisando
        typename std::list<NodoGeneral<T>*>::iterator it;
        for (it = nodo->obtenerDesc().begin(); it != nodo->obtenerDesc().end(); it++) {
            alth = this->altura(*it);
            // se queda con el mayor valor de (altura del hijo + 1)
            if (alt < alth + 1) {
                alt = alth + 1;
            }
        }
    }
    return alt;
}

template <class T>
unsigned int ArbolGeneral<T>::tamano() {
    // si esta vacio, retornar 0
    if (this->esVacio()) {
        return 0;
    }
    return this->tamano(this->raiz);
}

template <class T>
unsigned int ArbolGeneral<T>::tamano(NodoGeneral<T>* nodo) {
    // para cada uno de los hijos, llamo a tamaño
    // acumulo esos tamaños en una varibal  
    // retorno ese valor acumulado mas 1 (por el nodo actual)
    // (en una hoja no se entra al ciclo y retorna 0 + 1 = 1)
    unsigned int tam = 0;
    typename std::list<NodoGeneral<T>*>::iterator it;
    for (it = nodo->obtenerDesc().begin(); it != nodo->obtenerDesc().end(); it++) {
        tam += this->tamano(*it);
    }
    return tam + 1;
}

template <class T>
void ArbolGeneral<T>::preOrden() {
    if (!this->esVacio()) {
        this->preOrden(this->raiz);
    }
}

template <class T>
void ArbolGeneral<T>::preOrden(NodoGeneral<T>* nodo) {
    // PREorden: primero se imprime el nodo actual...
    std::cout << nodo->obtenerDato() << " ";
    // ...y después se recorre en preorden cada hijo, de izquierda a derecha
    typename std::list<NodoGeneral<T>*>::iterator it;
    for (it = nodo->obtenerDesc().begin(); it != nodo->obtenerDesc().end(); it++) {
        this->preOrden(*it);
    }
}

template <class T>
void ArbolGeneral<T>::posOrden() {
    // llamar a posorden sobre cada hijo
    // imprimo en pantalla el dato del nodo actual
    if (!this->esVacio()) {
        this->posOrden(this->raiz);
    }
}

template <class T>
void ArbolGeneral<T>::posOrden(NodoGeneral<T>* nodo) {
    // POSorden: primero se recorre en posorden cada hijo, de izquierda a derecha...
    typename std::list<NodoGeneral<T>*>::iterator it;
    for (it = nodo->obtenerDesc().begin(); it != nodo->obtenerDesc().end(); it++) {
        this->posOrden(*it);
    }
    // ...y al final se imprime el nodo actual (por eso la raíz sale de última)
    std::cout << nodo->obtenerDato() << " ";
}

template <class T>
void ArbolGeneral<T>::nivelOrden() {
    // NO ES RECURSIVO
    // ubicarme en la raiz
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
        typename std::list<NodoGeneral<T>*>::iterator it;
        for (it = nodo->obtenerDesc().begin(); it != nodo->obtenerDesc().end(); it++) {
            cola.push(*it); // los hijos quedan al final de la cola, detrás del nivel actual
        }
    }
}
