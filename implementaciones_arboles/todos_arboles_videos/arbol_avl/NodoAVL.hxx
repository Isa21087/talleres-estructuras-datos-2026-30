//archivo para implementar los metodos de la clase NodoAVL; se separa de la declaracion (.h)
//para que sea mas facil leer por un lado QUE hace la clase y por otro COMO lo hace

//inclusion del archivo de cabecera de la clase NodoAVL, para implementar los metodos segun su declaracion
//(gracias a la proteccion #ifndef del .h no se genera una inclusion infinita)
#include "NodoAVL.h"

//Cada vez que implementamos una funcion que pertenece a una clase generica (template),
//debemos volver a escribir template< class T > antes de la definicion de la funcion,
//y luego el nombre de la clase con el tipo generico NodoAVL<T>:: seguido del nombre de la funcion.

//==================== metodos que vienen igual del binario ordenado ====================

template< class T >
NodoAVL<T>::NodoAVL() { //constructor que crea un nodo sin hijos
    //un apuntador que no se inicializa guarda una direccion basura; por eso se ponen en NULL,
    //para que quede claro que el nodo todavia no tiene hijos
    this->hijoIzq = NULL; //this-> se refiere al nodo que se esta creando; su hijo izquierdo no apunta a nada
    this->hijoDer = NULL; //su hijo derecho tampoco apunta a nada
}

template< class T >
NodoAVL<T>::NodoAVL(T val) { //constructor que crea un nodo sin hijos pero ya con un dato
    this->dato = val; //se guarda el dato que llega como parametro
    this->hijoIzq = NULL; //sin hijo izquierdo
    this->hijoDer = NULL; //sin hijo derecho
}

template< class T >
NodoAVL<T>::~NodoAVL() { //destructor que elimina el nodo junto con todo su subarbol
    //delete libera la memoria del nodo AL QUE APUNTA el apuntador (no el apuntador como tal).
    //Al borrar el hijo se llama al destructor de ese hijo, que a su vez borra a sus hijos,
    //y asi en cascada se libera todo el subarbol.
    //Hacer delete de un apuntador NULL no hace nada, por eso no hace falta preguntar antes si el hijo existe.
    delete this->hijoIzq; //se libera el subarbol izquierdo completo
    delete this->hijoDer; //se libera el subarbol derecho completo
    this->hijoIzq = NULL; //los apuntadores siguen guardando la direccion vieja (ya liberada), por eso se ponen en NULL
    this->hijoDer = NULL;
}

template< class T >
T NodoAVL<T>::obtenerDato() {
    return this->dato; //devuelve una copia del dato almacenado en el nodo (atributo dato)
}

template< class T >
void NodoAVL<T>::fijarDato(T val) {
    this->dato = val; //reemplaza el dato del nodo; los hijos siguen siendo los mismos
}

template< class T >
NodoAVL<T>* NodoAVL<T>::obtenerHijoIzq() {
    return this->hijoIzq; //devuelve la direccion del hijo izquierdo (NULL si no tiene)
}

template< class T >
NodoAVL<T>* NodoAVL<T>::obtenerHijoDer() {
    return this->hijoDer; //devuelve la direccion del hijo derecho (NULL si no tiene)
}

template< class T >
void NodoAVL<T>::fijarHijoIzq(NodoAVL<T>* izq) {
    //solo cambia el apuntador: si ya habia un hijo izquierdo, NO se libera su memoria,
    //simplemente el nodo deja de apuntarlo
    this->hijoIzq = izq;
}

template< class T >
void NodoAVL<T>::fijarHijoDer(NodoAVL<T>* der) {
    //igual que fijarHijoIzq pero para el lado derecho
    this->hijoDer = der;
}

template< class T >
bool NodoAVL<T>::esHoja() {
    //el nodo es hoja si NO tiene hijo izquierdo Y TAMPOCO tiene hijo derecho
    return (this->hijoIzq == NULL && this->hijoDer == NULL);
}

// recurrente
template< class T >
int NodoAVL<T>::altura() {
    int valt; //variable donde se guarda la altura que se va a retornar

    if (this->esHoja()) {
        valt = 0; //un nodo sin hijos tiene altura 0 (un arbol con un unico nodo tiene altura 0)
    } else {
        //si no es hoja tiene al menos un hijo: se calcula la altura de cada hijo,
        //se escoge la mayor y se le suma 1 para contar el nodo en el que estoy
        int valt_izq = -1; //altura del subarbol izquierdo; se inicia en -1 por si no hay hijo izquierdo
        int valt_der = -1; //altura del subarbol derecho; se inicia en -1 por si no hay hijo derecho

        //se verifica que el hijo exista ANTES de llamar altura() sobre el (llamarla sobre NULL hace caer el programa)
        if (this->hijoIzq != NULL)
            valt_izq = (this->hijoIzq)->altura(); //el hijo izquierdo calcula su propia altura
        if (this->hijoDer != NULL)
            valt_der = (this->hijoDer)->altura(); //el hijo derecho calcula su propia altura

        if (valt_izq > valt_der) //me quedo con la mayor de las dos alturas...
            valt = valt_izq + 1; //...y le sumo 1 por este nodo
        else
            valt = valt_der + 1; //si son iguales da lo mismo cual se escoja
    }

    return valt;
}

// recurrente
template< class T >
int NodoAVL<T>::tamano() {
    int tam = 1; //se empieza contando este nodo

    if (this->hijoIzq != NULL)
        tam = tam + (this->hijoIzq)->tamano(); //se suman todos los nodos del subarbol izquierdo
    if (this->hijoDer != NULL)
        tam = tam + (this->hijoDer)->tamano(); //se suman todos los nodos del subarbol derecho

    return tam; //en una hoja no entra a ningun if y retorna 1
}

// recurrente
template< class T >
void NodoAVL<T>::preOrden() {
    //PREorden: el nodo se visita ANTES que sus hijos
    std::cout << this->dato << " "; //1. visitar: imprimir el dato de este nodo con un espacio
    if (this->hijoIzq != NULL)
        (this->hijoIzq)->preOrden(); //2. recorrer en preorden el subarbol izquierdo
    if (this->hijoDer != NULL)
        (this->hijoDer)->preOrden(); //3. recorrer en preorden el subarbol derecho
}

// recurrente
template< class T >
void NodoAVL<T>::inOrden() {
    //INorden: el nodo se visita EN MEDIO de sus dos hijos; en un arbol ordenado imprime de menor a mayor
    if (this->hijoIzq != NULL)
        (this->hijoIzq)->inOrden(); //1. recorrer en inorden el subarbol izquierdo
    std::cout << this->dato << " "; //2. visitar: imprimir el dato de este nodo
    if (this->hijoDer != NULL)
        (this->hijoDer)->inOrden(); //3. recorrer en inorden el subarbol derecho
}

// recurrente
template< class T >
void NodoAVL<T>::posOrden() {
    //POSorden: el nodo se visita DESPUES de sus hijos (por eso la raiz sale de ultima)
    if (this->hijoIzq != NULL)
        (this->hijoIzq)->posOrden(); //1. recorrer en posorden el subarbol izquierdo
    if (this->hijoDer != NULL)
        (this->hijoDer)->posOrden(); //2. recorrer en posorden el subarbol derecho
    std::cout << this->dato << " "; //3. visitar: imprimir el dato de este nodo
}

//==================== metodos que cambian en el AVL: insertar y eliminar ====================

// recurrente
template< class T >
NodoAVL<T>* NodoAVL<T>::insertar(T val, bool& insertado) {
    //Se baja igual que en el binario ordenado (menor a la izquierda, mayor a la derecha) hasta encontrar
    //un espacio vacio (NULL). La diferencia es que se hace con recursion: cuando cada llamado termina y
    //"regresa" hacia arriba, se balancea el nodo en el que estaba. Asi se verifica la propiedad AVL en
    //TODA la ruta de modificacion, desde donde se inserto hasta la raiz.

    if (val < this->dato) { //val es menor: va por el subarbol izquierdo
        if (this->hijoIzq == NULL) { //no hay hijo izquierdo: este es el espacio donde va val
            this->hijoIzq = new NodoAVL<T>(val); //new reserva memoria para el nodo nuevo y queda conectado como hijo izquierdo
            insertado = true; //se avisa a quien llamo que si se inserto
        } else {
            //hay hijo izquierdo: se le pide que inserte en su subarbol. Ese llamado devuelve la nueva raiz
            //de ese subarbol (puede haber cambiado por una rotacion), y se vuelve a conectar como hijo izquierdo
            this->hijoIzq = (this->hijoIzq)->insertar(val, insertado);
        }
    } else if (val > this->dato) { //val es mayor: va por el subarbol derecho
        if (this->hijoDer == NULL) { //no hay hijo derecho: este es el espacio donde va val
            this->hijoDer = new NodoAVL<T>(val); //se crea el nodo nuevo como hijo derecho
            insertado = true;
        } else {
            this->hijoDer = (this->hijoDer)->insertar(val, insertado); //se inserta en el subarbol derecho y se reconecta
        }
    } else {
        //no es menor ni mayor: es igual. En un arbol ordenado no se permiten datos repetidos,
        //asi que no se inserta y el subarbol queda exactamente igual (no hace falta balancear)
        insertado = false;
        return this; //este nodo sigue siendo la raiz de su subarbol
    }

    //despues de insertar en alguno de los hijos, la altura de este lado pudo crecer:
    //se verifica la propiedad AVL en este nodo y se devuelve quien quede como raiz del subarbol
    return this->balancear();
}

// recurrente
template< class T >
NodoAVL<T>* NodoAVL<T>::eliminar(T val, bool& eliminado) {
    //Se busca val bajando igual que en el binario ordenado. Al regresar de cada llamado se balancea
    //el nodo, para verificar la propiedad AVL en toda la ruta, desde donde se elimino hasta la raiz.

    if (val < this->dato) { //si val esta, tiene que estar a la izquierda
        if (this->hijoIzq != NULL) //si no hay hijo izquierdo, val no esta en el arbol y no se hace nada
            this->hijoIzq = (this->hijoIzq)->eliminar(val, eliminado); //se elimina en el subarbol izquierdo y se reconecta su nueva raiz
    } else if (val > this->dato) { //si val esta, tiene que estar a la derecha
        if (this->hijoDer != NULL)
            this->hijoDer = (this->hijoDer)->eliminar(val, eliminado); //se elimina en el subarbol derecho y se reconecta su nueva raiz
    } else {
        //este nodo es el que hay que eliminar
        eliminado = true;

        //verificar situacion de eliminacion:
        //1. nodo hoja, borrarlo
        //2. nodo con un solo hijo, usar hijo para reemplazar nodo
        //3. nodo con dos hijos, usar maximo del subarbol izquierdo para reemplazar nodo

        if (this->hijoIzq != NULL && this->hijoDer != NULL) {
            //situacion 3: el maximo del subarbol izquierdo se encuentra bajando una vez a la izquierda
            //y luego todo lo que se pueda a la derecha. Ese maximo es mayor que todo el resto del subarbol
            //izquierdo y menor que todo el derecho, asi que puede ocupar este lugar sin dañar el orden
            NodoAVL<T>* maximo = this->hijoIzq; //se arranca en el hijo izquierdo
            while (maximo->obtenerHijoDer() != NULL) //mientras se pueda bajar a la derecha...
                maximo = maximo->obtenerHijoDer(); //...se baja (cada vez el dato es mas grande)

            this->dato = maximo->obtenerDato(); //este nodo se queda con el dato del maximo (el dato a eliminar desaparece)
            //ahora el dato del maximo quedo repetido: se elimina el nodo original del maximo en el subarbol izquierdo.
            //Se hace con el mismo eliminar, para que tambien se balancee la ruta hasta ese maximo
            this->hijoIzq = (this->hijoIzq)->eliminar(this->dato, eliminado);
        } else {
            //situaciones 1 y 2: se escoge con que se reemplaza este nodo en su padre
            NodoAVL<T>* reemplazo; //el nodo que va a quedar en el lugar de este
            if (this->hijoIzq != NULL)
                reemplazo = this->hijoIzq; //situacion 2: solo tiene hijo izquierdo, ese hijo sube a este lugar
            else
                reemplazo = this->hijoDer; //situacion 2 con hijo derecho, o situacion 1 (hoja: hijoDer es NULL y el padre queda sin ese hijo)

            //antes de borrar este nodo se desconectan sus hijos, porque el destructor borra todo el subarbol
            //y se perderia el reemplazo que acaba de subir
            this->hijoIzq = NULL;
            this->hijoDer = NULL;
            //delete this libera este mismo nodo. Es valido porque el nodo se creo con new y,
            //despues de esta linea, ya no se usa ningun atributo del nodo (solo la variable local reemplazo)
            delete this;
            //el reemplazo ya cumplia la propiedad AVL (era un subarbol que no se modifico), por eso se devuelve tal cual
            return reemplazo;
        }
    }

    //despues de eliminar en alguno de los hijos, la altura de este lado pudo bajar:
    //se verifica la propiedad AVL en este nodo y se devuelve quien quede como raiz del subarbol
    return this->balancear();
}

//==================== metodos nuevos del AVL ====================

template< class T >
int NodoAVL<T>::diferenciaAltura() {
    //diferencia = altura del hijo izquierdo - altura del hijo derecho
    //  si da  2: el lado izquierdo es mas alto (desbalanceado hacia la izquierda)
    //  si da -2: el lado derecho es mas alto (desbalanceado hacia la derecha)
    //  si da -1, 0 o 1: este nodo cumple la propiedad AVL
    //(si se hiciera derecho - izquierdo, todos los signos de balancear se tendrian que voltear)
    int altIzq = -1; //altura de un subarbol vacio: -1 (por si no hay hijo izquierdo)
    int altDer = -1; //lo mismo para el lado derecho
    if (this->hijoIzq != NULL)
        altIzq = (this->hijoIzq)->altura(); //se usa la funcion altura que ya teniamos del binario
    if (this->hijoDer != NULL)
        altDer = (this->hijoDer)->altura();
    return altIzq - altDer; //se restan las dos alturas
}

template< class T >
NodoAVL<T>* NodoAVL<T>::rotarDerecha() {
    //Se usa cuando el lado IZQUIERDO es demasiado alto. En la rotacion hacia la derecha
    //siempre sube el hijo de la izquierda y este nodo baja a la derecha:
    /*
            this                   nPadre
            /    \                 /      \
        nPadre    C     ==>       A       this
        /    \                            /   \
        A      B                          B     C
    */
    //A y C no se mueven de su padre. B, el subarbol "del centro", cambia de padre: pasa a ser hijo
    //izquierdo de this. El orden se mantiene porque todo B es mayor que nPadre y menor que this.
    //Son solo tres lineas, y el orden importa para no perder referencias:
    NodoAVL<T>* nPadre = this->hijoIzq; //1. se guarda el hijo izquierdo, que va a ser el nuevo padre del subarbol
    this->hijoIzq = nPadre->hijoDer; //2. this adopta como hijo izquierdo al subarbol del centro (B)
    nPadre->hijoDer = this; //3. this baja y queda como hijo derecho del nuevo padre
    //se llama nPadre y no nRaiz porque la rotacion no siempre ocurre en la raiz del arbol:
    //puede ocurrir en la mitad, y lo que cambia es solo ese subarbol
    return nPadre; //quien llamo debe conectar este nuevo padre en lugar de this
}

template< class T >
NodoAVL<T>* NodoAVL<T>::rotarIzquierda() {
    //Es el espejo de rotarDerecha. Se usa cuando el lado DERECHO es demasiado alto:
    //sube el hijo de la derecha y este nodo baja a la izquierda:
/*
        this                         nPadre
       /    \                       /      \
      A    nPadre       ==>       this      C
           /    \                /    \
          B      C              A      B
*/
    //B, el subarbol del centro, pasa a ser hijo derecho de this (todo B es mayor que this y menor que nPadre)
    NodoAVL<T>* nPadre = this->hijoDer; //1. se guarda el hijo derecho, que va a ser el nuevo padre
    this->hijoDer = nPadre->hijoIzq; //2. this adopta como hijo derecho al subarbol del centro (B)
    nPadre->hijoIzq = this; //3. this baja y queda como hijo izquierdo del nuevo padre
    //si se hiciera primero nPadre->hijoIzq = this, se perderia la referencia a B; por eso el orden importa
    return nPadre;
}

template< class T >
NodoAVL<T>* NodoAVL<T>::rotarIzqDer() {
    //Se usa cuando el lado izquierdo es demasiado alto pero lo que crecio fue la parte DEL CENTRO
    //(el subarbol derecho del hijo izquierdo). Ahi una sola rotacion a la derecha no arregla nada,
    //solo pasa el problema al otro lado. Por eso se hace en dos pasos, reutilizando las rotaciones simples:
/*
         this                  this                    n3
        /    \                /    \                 /    \
      n2      D    ==>      n3      D     ==>      n2      this
     /  \                  /  \                   /  \     /  \
    A    n3               n2   C                 A    B   C    D
        /  \             /  \
       B    C           A    B
*/
    //paso 1: rotacion a la izquierda sobre el hijo izquierdo (n2); devuelve el nuevo padre de ese subarbol (n3)
    NodoAVL<T>* aux = (this->hijoIzq)->rotarIzquierda();
    this->hijoIzq = aux; //2. this ya no apunta a n2 sino a n3, que fue el que quedo arriba
    return this->rotarDerecha(); //3. rotacion a la derecha sobre this; devuelve el nuevo padre (n3)
}

template< class T >
NodoAVL<T>* NodoAVL<T>::rotarDerIzq() {
    //Es el espejo de rotarIzqDer. Se usa cuando el lado derecho es demasiado alto pero lo que crecio
    //fue la parte del centro (el subarbol izquierdo del hijo derecho)
    //paso 1: rotacion a la derecha sobre el hijo derecho; devuelve el nuevo padre de ese subarbol
    //(se hace sobre this->hijoDer y no "directamente sobre n2", porque las referencias siempre
    //se manejan desde el padre: this es quien tiene el apuntador a su hijo derecho)
    NodoAVL<T>* aux = (this->hijoDer)->rotarDerecha();
    this->hijoDer = aux; //2. se cambia la referencia del hijo derecho de this por ese nuevo padre
    return this->rotarIzquierda(); //3. rotacion a la izquierda sobre this; devuelve el nuevo padre
}

template< class T >
NodoAVL<T>* NodoAVL<T>::balancear() {
    //Verificacion: se mira si este nodo cumple la propiedad AVL y, si no, se escoge la rotacion con dos if.
    //Devuelve la raiz que queda en este subarbol: this si no se roto, o el nuevo padre si se roto.
    int diferencia = this->diferenciaAltura(); //altura izquierda - altura derecha

    if (diferencia > 1) {
        //diferencia de 2: el lado IZQUIERDO es mas alto. Puede ser rotacion derecha o izquierda-derecha.
        //Para saber cual, se mira la diferencia de alturas del hijo izquierdo (ese hijo si cumple AVL,
        //pero nos dice de que lado de el esta lo que crecio)
        if ((this->hijoIzq)->diferenciaAltura() >= 0)
            //el hijo izquierdo es mas alto por SU izquierda: crecio el de afuera, basta una rotacion a la derecha.
            //Si da 0 (ambos lados del hijo iguales, solo pasa al eliminar) tambien sirve la rotacion simple
            return this->rotarDerecha();
        else
            //el hijo izquierdo es mas alto por SU derecha: crecio el del centro, hace falta la doble rotacion
            return this->rotarIzqDer();
    } else if (diferencia < -1) {
        //diferencia de -2: el lado DERECHO es mas alto. Puede ser rotacion izquierda o derecha-izquierda.
        //Se mira la diferencia de alturas del hijo derecho
        if ((this->hijoDer)->diferenciaAltura() <= 0)
            //el hijo derecho es mas alto por SU derecha (o igual): basta una rotacion a la izquierda
            return this->rotarIzquierda();
        else
            //el hijo derecho es mas alto por SU izquierda: crecio el del centro, doble rotacion
            return this->rotarDerIzq();
    }

    //la diferencia es -1, 0 o 1: este nodo cumple AVL y no hay que rotar
    return this;
}
