//archivo para implementar los metodos de la clase ArbolAVL, separado de su declaracion (.h)

//inclusion del archivo de cabecera de la clase ArbolAVL, para implementar los metodos segun su declaracion
#include "ArbolAVL.h"

//como en el nodo, cada metodo de una clase plantilla se implementa escribiendo
//template< class T > y luego ArbolAVL<T>:: seguido del nombre del metodo

template< class T >
ArbolAVL<T>::ArbolAVL() { //constructor que crea un arbol vacio
    this->raiz = NULL; //se fija la raiz en NULL para garantizar que no vamos a tener problemas despues con ese apuntador
}

template< class T >
ArbolAVL<T>::~ArbolAVL() { //destructor que libera todo el arbol
    //solo se hace delete si hay raiz; al borrar la raiz se llama al destructor del nodo,
    //que borra en cascada a sus hijos, asi que con una sola instruccion se libera el arbol completo
    if (!this->esVacio())
        delete this->raiz;
    this->raiz = NULL; //la raiz queda en NULL para no apuntar a memoria que ya se libero
}

template< class T >
bool ArbolAVL<T>::esVacio() {
    return this->raiz == NULL; //el arbol esta vacio cuando no hay raiz
}

template< class T >
T ArbolAVL<T>::datoRaiz() {
    //se retorna solo el dato de tipo T guardado en la raiz, no el nodo raiz como tal.
    //OJO: si el arbol esta vacio, raiz es NULL y esto hace caer el programa; hay que revisar esVacio() antes
    return (this->raiz)->obtenerDato();
}

// recurrente
template< class T >
int ArbolAVL<T>::altura() {
    if (this->esVacio())
        return -1; //por convencion, la altura de un arbol vacio es -1
    else
        return (this->raiz)->altura(); //a la raiz se le pide que calcule su altura, y esa es la altura del arbol
}

// recurrente
template< class T >
int ArbolAVL<T>::tamano() {
    if (this->esVacio())
        return 0; //un arbol vacio no tiene nodos
    else
        return (this->raiz)->tamano(); //la raiz cuenta todos los nodos de su subarbol, que es el arbol completo
}

// recurrente (CAMBIA en el AVL: la hace el nodo y balancea toda la ruta)
template< class T >
bool ArbolAVL<T>::insertar(T val) {
    //si el arbol esta vacio, el nuevo dato pasa a ser la raiz (un solo nodo siempre cumple AVL)
    if (this->esVacio()) {
        this->raiz = new NodoAVL<T>(val); //new reserva memoria para el nodo; el constructor le guarda val
        return true;
    }

    bool insertado = false; //variable que el nodo va a modificar (se pasa por referencia) para avisar si inserto
    //la raiz inserta en su subarbol y balancea la ruta. Lo que devuelve es la nueva raiz del arbol,
    //porque si hubo una rotacion en la raiz, otro nodo pudo quedar arriba
    this->raiz = (this->raiz)->insertar(val, insertado);
    return insertado; //false si val ya estaba en el arbol
}

// recurrente (CAMBIA en el AVL: la hace el nodo y balancea toda la ruta)
template< class T >
bool ArbolAVL<T>::eliminar(T val) {
    if (this->esVacio())
        return false; //en un arbol vacio no hay nada que eliminar

    bool eliminado = false; //variable que el nodo va a modificar para avisar si elimino
    //la raiz elimina val de su subarbol y balancea la ruta. Devuelve la nueva raiz del arbol:
    //puede ser otro nodo (por una rotacion o porque se elimino la raiz) o NULL si el arbol quedo vacio
    this->raiz = (this->raiz)->eliminar(val, eliminado);
    return eliminado; //false si val no estaba en el arbol
}

// iterativa (igual que en el binario ordenado)
template< class T >
bool ArbolAVL<T>::buscar(T val) {
    //Como en la busqueda binaria: al comparar con el dato del nodo se descarta una de las dos ramas
    //completa, por eso no hace falta recursion. Buscar no modifica el arbol, asi que no hay que balancear
    NodoAVL<T>* nodo = this->raiz; //apuntador con el que se va bajando; se arranca desde la raiz
    bool encontrado = false; //se inicia en falso: todavia no se ha encontrado

    //se sigue bajando mientras haya nodo (no sea NULL) y todavia no se haya encontrado
    while (nodo != NULL && !encontrado) {
        if (val < nodo->obtenerDato()) {
            nodo = nodo->obtenerHijoIzq(); //val es menor: si esta, tiene que estar a la izquierda
        } else if (val > nodo->obtenerDato()) {
            nodo = nodo->obtenerHijoDer(); //val es mayor: si esta, tiene que estar a la derecha
        } else {
            encontrado = true; //no es menor ni mayor: es igual, se encontro
        }
    }
    //si val no esta, en algun momento nodo llega a NULL (ya no se puede bajar mas), el ciclo termina
    //y encontrado sigue en false
    return encontrado;
}

// recurrente
template< class T >
void ArbolAVL<T>::preOrden() {
    //en el arbol solo se verifica que no este vacio (si no hay raiz, no hay recorrido que hacer)
    if (!this->esVacio())
        (this->raiz)->preOrden(); //la raiz empieza el recorrido y ella se encarga del resto
}

// recurrente
template< class T >
void ArbolAVL<T>::inOrden() {
    if (!this->esVacio())
        (this->raiz)->inOrden();
}

// recurrente
template< class T >
void ArbolAVL<T>::posOrden() {
    if (!this->esVacio())
        (this->raiz)->posOrden();
}

// iterativa (igual que en el binario ordenado)
template< class T >
void ArbolAVL<T>::nivelOrden() {
    //NO ES RECURRENTE: se usa una cola, donde el primero que entra es el primero que sale.
    //Se saca un nodo, se imprime y se meten sus hijos al final de la cola; asi se termina
    //de imprimir un nivel completo antes de pasar al siguiente
    if (!this->esVacio()) {
        std::queue< NodoAVL<T>* > cola; //cola que almacena apuntadores a nodos pendientes por imprimir
        cola.push(this->raiz); //paso 1: se pone en la cola el nodo por el que arranca el recorrido, la raiz
        NodoAVL<T>* nodo; //nodo temporal para guardar lo que se va sacando de la cola

        while (!cola.empty()) { //mientras la cola no este vacia, hay algo para sacar
            nodo = cola.front(); //front() solo consulta cual es el primero de la cola...
            cola.pop(); //...y pop() lo saca; pop no retorna el elemento, por eso se consulta antes con front
            std::cout << nodo->obtenerDato() << " "; //se imprime su dato con un espacio

            //se ponen en la cola los hijos del nodo, verificando que existan (si es NULL no se mete)
            if (nodo->obtenerHijoIzq() != NULL)
                cola.push(nodo->obtenerHijoIzq()); //primero el izquierdo, para que salga antes que el derecho
            if (nodo->obtenerHijoDer() != NULL)
                cola.push(nodo->obtenerHijoDer());
        }
        //si un nodo es hoja no mete nada a la cola; en algun punto la cola se vacia y termina el recorrido
    }
}
