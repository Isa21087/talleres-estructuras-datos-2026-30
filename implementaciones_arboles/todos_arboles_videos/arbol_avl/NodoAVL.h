//Estas dos lineas se llaman proteccion de inclusion multiple: la primera vez que se incluye este archivo,
//__NODOAVL_H__ no esta definido, entonces se define y se lee la clase. Si otro archivo lo vuelve a incluir,
//ya esta definido y el compilador se salta todo hasta el #endif, evitando que la clase se declare dos veces (error de compilacion)
#ifndef __NODOAVL_H__
#define __NODOAVL_H__

#include <cstddef> //se incluye para poder usar NULL (apuntador que no apunta a nada)
#include <iostream> //se incluye para poder usar std::cout en los recorridos, que imprimen en pantalla

/* El NodoAVL es una copia del NodoBinario del arbol binario ordenado (version con recursion en el nodo),
   al que se le agregan las funciones propias del AVL:
   - diferenciaAltura: altura del hijo izquierdo MENOS altura del hijo derecho;
   - las cuatro rotaciones: derecha, izquierda, izquierda-derecha y derecha-izquierda;
   - balancear: la verificacion que, con unos if, decide si hace falta rotar y cual rotacion usar.
   Todas van en el nodo porque es ahi donde se ejecutan las rotaciones y las verificaciones.

   PROPIEDAD AVL: para CADA nodo del arbol, las alturas de sus dos subarboles pueden diferir MAXIMO en 1.
   Es decir, diferenciaAltura() solo puede dar -1, 0 o 1. Si da 2 o -2, el nodo esta desbalanceado y hay que rotar.
   Recordar que la altura de un subarbol vacio (hijo NULL) es -1.

   El nodo solo sabe cual es su dato y quienes son sus dos hijos. No sabe si es raiz ni conoce a su padre:
   cualquier estructura de arbol solo tiene referencia a los hijos desde el padre. */

//template< class T > dice que la clase es una plantilla: puede guardar cualquier tipo de dato (int, char, string...)
//y el tipo real se define cuando se crea el objeto, por ejemplo NodoAVL<int>
template< class T > //el nodo guarda un unico tipo de dato T, por eso se usa una plantilla

//como esta definido como una clase vamos a tener un constructor y un destructor
class NodoAVL { //nodo con un dato de tipo T y dos apuntadores a sus hijos

    protected: //los atributos son protected para que la clase y sus clases hijas puedan acceder, pero el resto del programa (el usuario) no

        T dato; //atributo que guarda el dato del nodo

        //se lee de adentro hacia afuera: NodoAVL<T> es un nodo que guarda datos tipo T
        //y el * indica que no se guarda el nodo como tal sino un apuntador (la direccion de memoria) a ese nodo
        NodoAVL<T>* hijoIzq; //apuntador al hijo izquierdo (datos MENORES); vale NULL si no tiene hijo izquierdo
        NodoAVL<T>* hijoDer; //apuntador al hijo derecho (datos MAYORES); vale NULL si no tiene hijo derecho

    public: //los metodos son public para que el resto del programa los pueda usar

        //----- metodos que vienen igual del binario ordenado -----
        NodoAVL(); //constructor que crea un nodo sin hijos (los dos apuntadores en NULL)
        NodoAVL(T val); //constructor que crea un nodo sin hijos y de una vez le guarda el dato val
        ~NodoAVL(); //destructor que elimina el nodo y tambien todo su subarbol

        T obtenerDato(); //metodo que permite consultar el dato del nodo; devuelve una copia del dato
        void fijarDato(T val); //metodo que permite cambiar el dato del nodo, sin cambiar la conexion con sus hijos

        NodoAVL<T>* obtenerHijoIzq(); //metodo que devuelve el apuntador al hijo izquierdo (puede ser NULL)
        NodoAVL<T>* obtenerHijoDer(); //metodo que devuelve el apuntador al hijo derecho (puede ser NULL)
        void fijarHijoIzq(NodoAVL<T>* izq); //metodo que conecta el nodo izq como hijo izquierdo
        void fijarHijoDer(NodoAVL<T>* der); //metodo que conecta el nodo der como hijo derecho

        bool esHoja(); //metodo que dice si el nodo es hoja, es decir que no tiene ni hijo izquierdo ni hijo derecho

        int altura(); //altura del subarbol: 0 si el nodo es hoja, si no 1 + la altura de su hijo mas alto
        int tamano(); //cantidad de nodos del subarbol, contando a este nodo
        void preOrden(); //imprime: primero este nodo, luego el subarbol izquierdo, luego el derecho
        void inOrden(); //imprime: subarbol izquierdo, este nodo, subarbol derecho (sale ordenado de menor a mayor)
        void posOrden(); //imprime: subarbol izquierdo, subarbol derecho, y al final este nodo

        //----- metodos que cambian en el AVL: insertar y eliminar -----
        //Ahora son recurrentes y devuelven la NUEVA RAIZ del subarbol, porque despues de insertar o eliminar
        //se balancea cada nodo de la ruta y una rotacion puede cambiar quien queda arriba en ese subarbol.
        //El bool& es un parametro por referencia: la funcion puede cambiar la variable original de quien la llama,
        //asi se avisa si de verdad se inserto o se elimino algo.
        NodoAVL<T>* insertar(T val, bool& insertado); //inserta val en este subarbol; insertado queda en false si val ya estaba
        NodoAVL<T>* eliminar(T val, bool& eliminado); //elimina val de este subarbol; eliminado queda en false si val no estaba

        //----- metodos nuevos del AVL -----
        int diferenciaAltura(); //altura del hijo izquierdo menos altura del hijo derecho (un hijo NULL tiene altura -1)
        NodoAVL<T>* rotarDerecha(); //sube el hijo izquierdo y baja este nodo a la derecha; devuelve el nuevo padre del subarbol
        NodoAVL<T>* rotarIzquierda(); //sube el hijo derecho y baja este nodo a la izquierda; devuelve el nuevo padre del subarbol
        NodoAVL<T>* rotarIzqDer(); //doble rotacion: izquierda sobre el hijo izquierdo y luego derecha sobre este nodo
        NodoAVL<T>* rotarDerIzq(); //doble rotacion: derecha sobre el hijo derecho y luego izquierda sobre este nodo
        NodoAVL<T>* balancear(); //verifica la propiedad AVL en este nodo y, si no se cumple, aplica la rotacion necesaria
};

//como el nodo es una plantilla, el compilador necesita ver la implementacion junto con la declaracion,
//por eso el archivo de implementacion (.hxx) se incluye aqui al final del .h y no se compila aparte
#include "NodoAVL.hxx"

#endif //fin de la proteccion de inclusion multiple
