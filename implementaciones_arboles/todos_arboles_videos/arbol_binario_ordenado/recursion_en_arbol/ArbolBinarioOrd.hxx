// Implementación de ArbolBinarioOrd con la recursión hecha EN EL ÁRBOL.
// Las operaciones marcadas "iterativa" son iguales en la otra versión
// (arbolBinarioOrd_RecursionEnNodo); solo cambian las "recurrente".
#include "ArbolBinarioOrd.h"

template <class T>
ArbolBinarioOrd<T>::ArbolBinarioOrd() {
    // Árbol vacío: se fija la raíz en NULL para no tener problemas después con ese apuntador
    this->raiz = NULL;
}

template <class T>
ArbolBinarioOrd<T>::~ArbolBinarioOrd() {
    // Si hay raíz, borrarla llama al destructor del nodo, que borra en cascada
    // a sus dos hijos; así se libera el árbol completo
    if (!this->esVacio()) {
        delete this->raiz;
    }
    this->raiz = NULL;
}

template <class T>
bool ArbolBinarioOrd<T>::esVacio() {
    return this->raiz == NULL;
}

template <class T>
T ArbolBinarioOrd<T>::datoRaiz() {
    // Retorna solo el dato (de tipo T) guardado en la raíz, no el nodo raíz como tal.
    // Ojo: si el árbol está vacío, raiz es NULL y esto falla; hay que revisar esVacio() antes.
    return (this->raiz)->obtenerDato();
}

// recurrente
template <class T>
int ArbolBinarioOrd<T>::altura() {
    // Por convención, la altura de un árbol vacío es -1
    if (this->esVacio()) {
        return -1;
    } else {
        return this->altura(this->raiz);
    }
}

template <class T>
int ArbolBinarioOrd<T>::altura(NodoBinario<T>* nodo) {
    int valt;

    if (nodo->esHoja()) {
        // un nodo sin hijos tiene altura 0
        valt = 0;
    } else {
        // Al menos tiene un hijo: se calcula la altura de cada hijo, se escoge
        // la mayor y se le suma 1 para contar el nodo actual.
        // Se inician en -1 por si falta alguno de los hijos.
        int valt_izq = -1;
        int valt_der = -1;
        // A diferencia del árbol general (donde los hijos estaban en una lista),
        // aquí los hijos son apuntadores sueltos que pueden ser NULL, y llamar
        // a altura sobre NULL causaría una violación de segmento. Por eso se verifica antes.
        if (nodo->obtenerHijoIzq() != NULL)
            valt_izq = this->altura(nodo->obtenerHijoIzq());
        if (nodo->obtenerHijoDer() != NULL)
            valt_der = this->altura(nodo->obtenerHijoDer());
        if (valt_izq > valt_der)
            valt = valt_izq + 1;
        else
            valt = valt_der + 1;
    }

    return valt;
}

// recurrente
template <class T>
int ArbolBinarioOrd<T>::tamano() {
    // Si el árbol está vacío no hay nodos; tamano(NULL) ya retorna 0
    return this->tamano(this->raiz);
}

template <class T>
int ArbolBinarioOrd<T>::tamano(NodoBinario<T>* nodo) {
    // Un subárbol vacío no tiene nodos
    if (nodo == NULL)
        return 0;
    // 1 por el nodo actual + los nodos del subárbol izquierdo + los del derecho
    return 1 + this->tamano(nodo->obtenerHijoIzq()) + this->tamano(nodo->obtenerHijoDer());
}

// iterativa
template <class T>
bool ArbolBinarioOrd<T>::insertar(T val) {
    // Se baja desde la raíz buscando el lugar donde debería ir val, como en buscar,
    // pero guardando también al padre: cuando nodo llegue a NULL, el padre es
    // el nodo al que hay que conectarle el nuevo hijo.
    NodoBinario<T>* nodo = this->raiz;
    NodoBinario<T>* padre = this->raiz;
    bool insertado = false;
    bool duplicado = false;

    while (nodo != NULL) {
        padre = nodo; // el padre se queda en el nodo actual y nodo baja un nivel
        if (val < nodo->obtenerDato()) {
            nodo = nodo->obtenerHijoIzq();
        } else if (val > nodo->obtenerDato()) {
            nodo = nodo->obtenerHijoDer();
        } else {
            // no es menor ni mayor: es igual, y no se permiten datos repetidos
            duplicado = true;
            break; // corta el ciclo, no hace falta seguir bajando
        }
    }

    if (!duplicado) {
        // el constructor con parámetro crea el nodo y de una vez le asigna el dato
        NodoBinario<T>* nuevo = new NodoBinario<T>(val);
        if (nuevo != NULL) {
            if (padre == NULL) {
                // el árbol estaba vacío (el ciclo no se ejecutó): el nuevo nodo es la raíz
                this->raiz = nuevo;
            } else if (val < padre->obtenerDato()) {
                // se compara contra el padre para saber de qué lado conectarlo
                padre->fijarHijoIzq(nuevo);
            } else {
                padre->fijarHijoDer(nuevo);
            }
            insertado = true;
        }
    }

    return insertado;
}

// iterativa
template <class T>
bool ArbolBinarioOrd<T>::eliminar(T val) {
    // comparar con dato en nodo para bajar por izquierda o derecha
    // y para saber si val esta en el arbol.
    // Igual que en insertar, se necesita el padre para poder cambiar su
    // apuntador hacia el nodo que se va a eliminar.
    NodoBinario<T>* nodo = this->raiz;
    NodoBinario<T>* padre = NULL; // la raíz no tiene padre
    bool encontrado = false;

    while (nodo != NULL && !encontrado) {
        if (val < nodo->obtenerDato()) {
            padre = nodo;
            nodo = nodo->obtenerHijoIzq();
        } else if (val > nodo->obtenerDato()) {
            padre = nodo;
            nodo = nodo->obtenerHijoDer();
        } else {
            encontrado = true;
        }
    }

    // si val no esta en el arbol, no hay nada que eliminar
    if (!encontrado)
        return false;

    // si val esta en el arbol
    // verificar situacion de eliminacion:
    // 1. nodo hoja, borrarlo
    // 2. nodo con un solo hijo, usar hijo para reemplazar nodo
    // 3. nodo con dos hijos, usar maximo del subarbol izquierdo
    //    para reemplazar nodo

    // Situación 3: se busca el máximo del subárbol izquierdo (bajar una vez a
    // la izquierda y luego todo lo posible a la derecha). Ese máximo es mayor que
    // todo el resto del subárbol izquierdo y menor que todo el derecho, así que
    // puede ocupar el lugar del nodo sin dañar el orden.
    if (nodo->obtenerHijoIzq() != NULL && nodo->obtenerHijoDer() != NULL) {
        NodoBinario<T>* padreMax = nodo;
        NodoBinario<T>* maximo = nodo->obtenerHijoIzq();
        while (maximo->obtenerHijoDer() != NULL) {
            padreMax = maximo;
            maximo = maximo->obtenerHijoDer();
        }
        // se copia el dato del máximo en el nodo que se quería eliminar...
        nodo->fijarDato(maximo->obtenerDato());
        // ...y ahora el que hay que quitar del árbol es el máximo. Como el máximo
        // no tiene hijo derecho, quedó en la situación 1 o 2, que se resuelven abajo.
        padre = padreMax;
        nodo = maximo;
    }

    // Situaciones 1 y 2: se escoge con qué se reemplaza el nodo en su padre
    NodoBinario<T>* reemplazo;
    if (nodo->esHoja()) {
        // 1. nodo hoja: el padre simplemente se queda sin ese hijo
        reemplazo = NULL;
    } else if (nodo->obtenerHijoIzq() != NULL) {
        // 2. nodo con un solo hijo (el izquierdo): ese hijo sube a su lugar
        reemplazo = nodo->obtenerHijoIzq();
    } else {
        // 2. nodo con un solo hijo (el derecho): ese hijo sube a su lugar
        reemplazo = nodo->obtenerHijoDer();
    }

    // se conecta el reemplazo en el lugar donde estaba el nodo
    if (padre == NULL) {
        this->raiz = reemplazo; // el nodo eliminado era la raíz
    } else if (padre->obtenerHijoIzq() == nodo) {
        padre->fijarHijoIzq(reemplazo);
    } else {
        padre->fijarHijoDer(reemplazo);
    }

    // Antes del delete se desconectan los hijos del nodo, porque el destructor
    // borra todo el subárbol y se perderían los nodos que acaban de subir.
    nodo->fijarHijoIzq(NULL);
    nodo->fijarHijoDer(NULL);
    delete nodo;

    return true;
}

// iterativa
template <class T>
bool ArbolBinarioOrd<T>::buscar(T val) {
    // Como en la búsqueda binaria: al comparar con el dato del nodo se descarta
    // una de las dos ramas completa, por eso no hace falta recursión.
    NodoBinario<T>* nodo = this->raiz; // se arranca desde la raíz
    bool encontrado = false;

    // se baja mientras haya nodo y todavía no se haya encontrado
    while (nodo != NULL && !encontrado) {
        if (val < nodo->obtenerDato()) {
            // val es menor: si está, tiene que estar a la izquierda
            nodo = nodo->obtenerHijoIzq();
        } else if (val > nodo->obtenerDato()) {
            // val es mayor: si está, tiene que estar a la derecha
            nodo = nodo->obtenerHijoDer();
        } else {
            // no es menor ni mayor: es igual
            encontrado = true;
        }
    }
    // si val no está, en algún momento nodo llega a NULL, el ciclo termina
    // y encontrado sigue en false
    return encontrado;
}

// recurrente
template <class T>
void ArbolBinarioOrd<T>::preOrden() {
    if (!this->esVacio())
        this->preOrden(this->raiz);
}

template <class T>
void ArbolBinarioOrd<T>::preOrden(NodoBinario<T>* nodo) {
    // Se verifica que el nodo recibido no sea NULL; así se puede llamar
    // sobre los hijos sin preguntar antes si existen
    if (nodo != NULL) {
        std::cout << nodo->obtenerDato() << " "; // 1. visitar el nodo
        this->preOrden(nodo->obtenerHijoIzq()); // 2. recorrer el izquierdo
        this->preOrden(nodo->obtenerHijoDer()); // 3. recorrer el derecho
    }
}

// recurrente
template <class T>
void ArbolBinarioOrd<T>::inOrden() {
    // Si el árbol está vacío no hay recorrido que hacer
    if (!this->esVacio())
        this->inOrden(this->raiz);
}

template <class T>
void ArbolBinarioOrd<T>::inOrden(NodoBinario<T>* nodo) {
    // Si el nodo es NULL simplemente se sale de la función
    if (nodo != NULL) {
        this->inOrden(nodo->obtenerHijoIzq()); // 1. recorrer el izquierdo
        std::cout << nodo->obtenerDato() << " "; // 2. visitar el nodo
        this->inOrden(nodo->obtenerHijoDer()); // 3. recorrer el derecho
    }
}

// recurrente
template <class T>
void ArbolBinarioOrd<T>::posOrden() {
    if (!this->esVacio())
        this->posOrden(this->raiz);
}

template <class T>
void ArbolBinarioOrd<T>::posOrden(NodoBinario<T>* nodo) {
    if (nodo != NULL) {
        this->posOrden(nodo->obtenerHijoIzq()); // 1. recorrer el izquierdo
        this->posOrden(nodo->obtenerHijoDer()); // 2. recorrer el derecho
        std::cout << nodo->obtenerDato() << " "; // 3. visitar el nodo
    }
}

// iterativa
template <class T>
void ArbolBinarioOrd<T>::nivelOrden() {
    // Se usa una cola: se saca un nodo, se imprime y se meten sus hijos.
    // Como la cola atiende en orden de llegada, se termina un nivel antes de pasar al siguiente.
    if (!this->esVacio()) {
        std::queue<NodoBinario<T>*> cola; // cola de apuntadores a nodos binarios
        cola.push(this->raiz); // se arranca por la raíz
        NodoBinario<T>* nodo; // nodo temporal para lo que se va sacando de la cola
        while (!cola.empty()) {
            nodo = cola.front(); // front() consulta el primero de la cola...
            cola.pop(); // ...y pop() lo saca (pop no lo retorna, por eso se usa front antes)
            std::cout << nodo->obtenerDato() << " ";
            // solo se meten a la cola los hijos que existen
            if (nodo->obtenerHijoIzq() != NULL)
                cola.push(nodo->obtenerHijoIzq());
            if (nodo->obtenerHijoDer() != NULL)
                cola.push(nodo->obtenerHijoDer());
        }
    }
}
