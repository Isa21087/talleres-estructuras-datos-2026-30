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
    // Devuelve la lista original de hijos (no una copia)
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

template <class T>
bool NodoGeneral<T>::insertarNodo(T padre, T n) {
    // - revisar si este nodo coincide con padre
    // - si es padre, insertar nuevo nodo como hijo
    // - si no es el padre, llamar a insertar en cada nodo hijo
    if (this->dato == padre) {
        this->adicionarDesc(n);
        return true;
    }
    typename std::list<NodoGeneral<T>*>::iterator it;
    for (it = this->desc.begin(); it != this->desc.end(); it++) {
        // (*it)-> llama el método sobre el hijo: el hijo repite el proceso en su subárbol
        if ((*it)->insertarNodo(padre, n)) {
            return true; // ya se insertó, no hace falta seguir con los demás hijos
        }
    }
    // el padre no está en este subárbol
    return false;
}

template <class T>
bool NodoGeneral<T>::eliminarNodo(T val) {
    // - si alguno de los hijos es el que quiero eliminar, eliminarlo
    // - si no, llamar a eliminar en cada nodo hijo
    // - si no se encontro en ningun hijo, retornar false
    // Un nodo no se puede eliminar a sí mismo: lo elimina su padre, que es quien
    // tiene en su lista el apuntador hacia él. Por eso el caso de la raíz
    // (que no tiene padre) lo resuelve el árbol.
    if (this->eliminarDesc(val)) {
        return true;
    }
    typename std::list<NodoGeneral<T>*>::iterator it;
    for (it = this->desc.begin(); it != this->desc.end(); it++) {
        if ((*it)->eliminarNodo(val)) {
            return true;
        }
    }
    return false;
}

template <class T>
bool NodoGeneral<T>::buscar(T n) {
    // - si el dato de este nodo es el buscado, retorno que lo encontre
    // - si no, llamar a buscar en cada nodo hijo
    if (this->dato == n) {
        return true;
    }
    typename std::list<NodoGeneral<T>*>::iterator it;
    for (it = this->desc.begin(); it != this->desc.end(); it++) {
        if ((*it)->buscar(n)) {
            return true; // apenas un hijo lo encuentra se deja de buscar
        }
    }
    return false;
}

template <class T>
int NodoGeneral<T>::altura() {
    // La altura de un nodo es la cantidad de niveles que hay debajo de él:
    // una hoja tiene altura 0 y cualquier otro nodo tiene 1 + la altura de su hijo más alto
    int alt = -1;
    if (this->esHoja()) {
        alt = 0;
    } else {
        int alth; // altura del hijo que se está revisando
        typename std::list<NodoGeneral<T>*>::iterator it;
        for (it = this->desc.begin(); it != this->desc.end(); it++) {
            alth = (*it)->altura();
            // se queda con el mayor valor de (altura del hijo + 1)
            if (alt < alth + 1) {
                alt = alth + 1;
            }
        }
    }
    return alt;
}

template <class T>
unsigned int NodoGeneral<T>::tamano() {
    // - acumular el tamaño de cada nodo hijo
    // - retornar ese valor acumulado mas 1 (por este nodo)
    // (en una hoja no se entra al ciclo y retorna 0 + 1 = 1)
    unsigned int tam = 0;
    typename std::list<NodoGeneral<T>*>::iterator it;
    for (it = this->desc.begin(); it != this->desc.end(); it++) {
        tam += (*it)->tamano();
    }
    return tam + 1;
}

template <class T>
void NodoGeneral<T>::preOrden() {
    // PREorden: primero se imprime este nodo...
    std::cout << this->obtenerDato() << " ";
    // ...y después cada hijo se recorre a sí mismo en preorden, de izquierda a derecha
    typename std::list<NodoGeneral<T>*>::iterator it;
    for (it = this->desc.begin(); it != this->desc.end(); it++) {
        (*it)->preOrden();
    }
}

template <class T>
void NodoGeneral<T>::posOrden() {
    // - llamar a posorden sobre cada hijo
    // - imprimir el dato de este nodo
    // POSorden: primero cada hijo se recorre a sí mismo en posorden...
    typename std::list<NodoGeneral<T>*>::iterator it;
    for (it = this->desc.begin(); it != this->desc.end(); it++) {
        (*it)->posOrden();
    }
    // ...y al final se imprime este nodo (por eso la raíz sale de última)
    std::cout << this->obtenerDato() << " ";
}
