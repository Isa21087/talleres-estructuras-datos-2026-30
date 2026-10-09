//para compilar y ejecutar:  g++ -std=c++11 ejemploSet.cpp -o ejemploSet && ./ejemploSet

/* ARBOL ROJINEGRO CON std::set
   Un arbol rojinegro es un arbol binario ordenado que se mantiene balanceado cumpliendo 5 propiedades:
   1. Todos los nodos tienen un color: rojo o negro.
   2. La raiz y las hojas son negras. OJO: aqui las hojas son los NULOS (los hijos vacios), no los numeros.
   3. Si un nodo es rojo, su padre es negro (no puede haber dos rojos seguidos).
   4. Cada nodo rojo tiene exactamente dos hijos negros.
   5. Todas las rutas desde un nodo hasta cualquiera de sus hojas descendientes (nulos)
      tienen la misma cantidad de nodos negros. Es la mas dificil de mantener.

   Por eso todo nodo nuevo se inserta de color ROJO (si se insertara negro, esa ruta quedaria con un negro
   de mas y se romperia la propiedad 5). Si el padre tambien es rojo se rompe la propiedad 3, y se arregla
   con cambios de color y rotaciones (las mismas rotaciones del AVL), revisando desde donde se inserto hacia arriba.

   Implementar la eliminacion a mano es muy complicado, asi que, como dijo la profe, NO se implementa:
   ya viene hecho en la STL (libreria estandar de plantillas de C++). Hay cuatro contenedores que por
   debajo son un arbol rojinegro: set, multiset, map y multimap. Este archivo muestra el set.

   El set guarda elementos UNICOS y, por como esta implementado, "se ve" como una lista ordenada,
   pero por debajo es un arbol rojinegro. Insertar, eliminar y buscar son O(log n) en el peor caso,
   y el set hace solito todos los cambios de color y las rotaciones. */

#include <iostream> //para std::cout
#include <set> //libreria donde esta definido std::set

int main() {
    //std::set<T> recibe un unico tipo de dato T (int, string, una clase propia...).
    //Ese tipo T debe tener definido el operador menor que (<), porque el arbol lo usa para decidir
    //si un dato va a la izquierda (menor) o a la derecha (mayor). int ya lo tiene definido
    std::set<int> arbol; //arbol rojinegro vacio que guarda enteros

    //----- INSERTAR -----
    //mismos datos del ejemplo de clase: el arbol 11, 2, 14, 1, 7, 15, 5, 8 y despues se inserta el 4
    int datos[] = {11, 2, 14, 1, 7, 15, 5, 8, 4};
    for (int i = 0; i < 9; i++) {
        //insert busca el lugar como en un binario ordenado, pone el nodo y hace los cambios de color
        //y rotaciones que hagan falta. No se le dice "al principio" o "al final": va donde le corresponda en el arbol
        arbol.insert(datos[i]);
    }

    //insert devuelve una pareja (std::pair): .first es un iterador al elemento y .second es un bool
    //que dice si de verdad se inserto. Como el set no admite repetidos, insertar el 7 otra vez da false
    std::pair<std::set<int>::iterator, bool> resultado = arbol.insert(7);
    std::cout << "insertar 7 otra vez: " << (resultado.second ? "se inserto" : "NO se inserto (ya estaba)") << "\n";

    std::cout << "tamano del arbol (size): " << arbol.size() << "\n"; //cantidad de elementos guardados

    //----- RECORRER -----
    //Como se ve como una lista ordenada, se recorre con iteradores: begin() apunta al primero (el menor)
    //y end() es la posicion DESPUES del ultimo (no es un elemento, sirve para saber cuando parar).
    //Este recorrido de begin a end en el arbol es el recorrido INORDEN: sale de menor a mayor
    std::cout << "recorrido de begin a end (inorden): ";
    std::set<int>::iterator it; //iterador: "señala" una posicion del set
    for (it = arbol.begin(); it != arbol.end(); it++) //se avanza de uno en uno hasta llegar a end
        std::cout << *it << " "; //*it es el dato que esta en esa posicion
    std::cout << "\n";

    //rbegin() y rend() sirven para recorrerlo al reves (de mayor a menor)
    std::cout << "recorrido de rbegin a rend (al reves): ";
    std::set<int>::reverse_iterator rit; //iterador que avanza hacia atras
    for (rit = arbol.rbegin(); rit != arbol.rend(); rit++)
        std::cout << *rit << " ";
    std::cout << "\n";

    //----- BUSCAR -----
    //la busqueda es igual que en un binario ordenado (no modifica el arbol, no hay que balancear).
    //find devuelve un iterador al elemento, o end() si no lo encontro
    if (arbol.find(5) != arbol.end())
        std::cout << "buscar 5: si esta\n";
    //count devuelve cuantas veces esta el dato; en un set solo puede ser 0 o 1
    std::cout << "buscar 100 con count: " << arbol.count(100) << " (0 = no esta)\n";

    //----- ELIMINAR -----
    //erase borra el dato y tambien hace todas las comprobaciones, cambios de color y rotaciones.
    //erase(valor) devuelve cuantos elementos borro (0 si no estaba)
    std::cout << "eliminar 14: borro " << arbol.erase(14) << " elemento(s)\n";
    std::cout << "eliminar 99: borro " << arbol.erase(99) << " elemento(s)\n";

    std::cout << "despues de eliminar: ";
    for (it = arbol.begin(); it != arbol.end(); it++)
        std::cout << *it << " ";
    std::cout << "\n";

    //el menor de todos esta "a toda la izquierda" del arbol (begin) y el mayor a toda la derecha (rbegin)
    std::cout << "menor: " << *arbol.begin() << "  mayor: " << *arbol.rbegin() << "\n";

    arbol.clear(); //borra todos los elementos
    std::cout << "despues de clear, esta vacio (empty): " << (arbol.empty() ? "si" : "no") << "\n";

    return 0;
}
