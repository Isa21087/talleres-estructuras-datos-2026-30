//proteccion de inclusion multiple: si otro archivo ya incluyo este .h, el compilador se salta todo
//hasta el #endif, evitando que la clase ArbolAVL se declare dos veces (error de compilacion)
#ifndef __ARBOLAVL_H__
#define __ARBOLAVL_H__

#include <queue> //se incluye la libreria queue para poder usar una cola en el recorrido por niveles
#include "NodoAVL.h" //el arbol esta formado por nodos AVL, asi que necesita conocer esa clase (ya trae <iostream>)

/* El ArbolAVL (de Adelson-Velsky y Landis) es un arbol binario ordenado que ademas se mantiene BALANCEADO:
   para cada nodo, las alturas de sus dos subarboles difieren maximo en 1. Asi el arbol nunca termina
   todo cargado hacia un lado (como una lista), y buscar, insertar y eliminar bajan por pocos niveles.

   Segun el TAD:
   - Todas las operaciones son iguales al TAD Arbol Binario Ordenado, salvo la insercion y la eliminacion.
   - Se agrega una operacion de balanceo, que verifica si en un nodo se cumple o no la propiedad,
     y si no se cumple hace el llamado a las rotaciones.
   - Se agregan las rotaciones.
   - En la insercion y la eliminacion se hace el llamado a balanceo en toda la ruta de modificacion.
   El balanceo, las rotaciones y la diferencia de alturas estan en el NODO (NodoAVL), que es donde se ejecutan.

   El arbol solo guarda un apuntador a la raiz. Como una rotacion puede cambiar quien queda arriba,
   despues de insertar o eliminar la raiz se actualiza con lo que devuelva el nodo. */

template< class T > //el arbol tambien es una plantilla: guarda datos de cualquier tipo T
class ArbolAVL {

    protected: //solo la clase y sus clases hijas pueden acceder a la raiz directamente
        NodoAVL<T>* raiz; //apuntador al nodo raiz; vale NULL cuando el arbol esta vacio

    public: //operaciones que el usuario puede usar
        ArbolAVL(); //constructor que crea un arbol vacio (sin raiz)
        ~ArbolAVL(); //destructor que libera todos los nodos del arbol

        bool esVacio(); //true si el arbol no tiene raiz
        T datoRaiz(); //devuelve el dato guardado en la raiz (solo usar si el arbol NO esta vacio)
        int altura(); //altura del arbol: -1 si esta vacio, 0 si solo tiene la raiz
        int tamano(); //cantidad de nodos del arbol

        bool insertar(T val); //inserta val y rebalancea; false si val ya estaba (no se permiten repetidos)
        bool eliminar(T val); //elimina val y rebalancea; false si val no esta en el arbol
        bool buscar(T val); //true si val esta en el arbol

        void preOrden(); //imprime: nodo, subarbol izquierdo, subarbol derecho
        void inOrden(); //imprime: subarbol izquierdo, nodo, subarbol derecho (de menor a mayor)
        void posOrden(); //imprime: subarbol izquierdo, subarbol derecho, nodo
        void nivelOrden(); //imprime nivel por nivel, de izquierda a derecha
};

//como el arbol es una plantilla, la implementacion se incluye aqui al final del .h
#include "ArbolAVL.hxx"

#endif //fin de la proteccion de inclusion multiple
