//para compilar y ejecutar:  g++ -std=c++11 ejemploMonticuloSTL.cpp -o ejemploMonticuloSTL && ./ejemploMonticuloSTL

/* MONTICULOS (HEAPS) CON LA STL
   Un monticulo es un arbol BINARIO (maximo dos hijos) pero NO ordenado: no existe la propiedad de
   "menores a la izquierda y mayores a la derecha". Lo que existe es una propiedad entre PADRES e HIJOS
   (nunca entre hermanos). Los dos mas usados son:
   - Monticulo maximo (max heap): el padre siempre es MAYOR O IGUAL que sus hijos.
     Por transitividad, el mayor de todos queda en la raiz.
   - Monticulo minimo (min heap): el padre siempre es MENOR O IGUAL que sus hijos.
     Por transitividad, el menor de todos queda en la raiz.
   Ademas esta basado en los arboles COMPLETOS: se va llenando el ultimo nivel de izquierda a derecha,
   y siempre se inserta y se quita por el ultimo nivel, asi que siempre queda balanceado.

   Es el unico arbol que se implementa con un ARREGLO y no con nodos y apuntadores.
   Con la raiz en la posicion 0, para cualquier posicion i:
   - hijo izquierdo: 2*i + 1
   - hijo derecho:   2*i + 2
   - padre:          piso((i - 1) / 2)   (se aproxima siempre hacia abajo)
   Asi no hay que preocuparse por apuntadores ni por nulos: las formulas dan las "flechas".

   En la STL los monticulos no son un contenedor sino ALGORITMOS (libreria <algorithm>), y los algoritmos
   no funcionan solitos: operan sobre un contenedor (vector, deque...) que uno crea y llena.
   - make_heap(inicio, fin): organiza como monticulo todo lo que haya en el contenedor;
   - push_heap(inicio, fin): el dato nuevo ya se puso al final, y esto lo va subiendo hasta su lugar;
   - pop_heap(inicio, fin): pasa la raiz al final y reorganiza el resto (el dato NO se borra todavia).
   Por defecto son monticulos MAXIMOS. */

#include <iostream> //para std::cout
#include <deque> //contenedor deque (cola doble), el mismo del ejemplo de clase
#include <vector> //contenedor vector
#include <algorithm> //aqui estan make_heap, push_heap, pop_heap e is_heap
#include <functional> //aqui esta std::greater, que sirve para armar monticulos minimos

//imprime el contenedor como arreglo y luego, usando las formulas, quien es hijo de quien.
//Es una plantilla para que sirva tanto con deque como con vector
template< class Contenedor >
void mostrar(const Contenedor& c) {
    std::cout << "  arreglo: [ ";
    for (unsigned int i = 0; i < c.size(); i++)
        std::cout << c[i] << " "; //se puede usar [] porque deque y vector se ven como arreglos
    std::cout << "]\n";
    for (unsigned int i = 0; i < c.size(); i++) {
        unsigned int izq = 2 * i + 1; //formula del hijo izquierdo
        unsigned int der = 2 * i + 2; //formula del hijo derecho
        if (izq < c.size()) { //si la posicion se sale del arreglo, ese hijo no existe
            std::cout << "  hijos de " << c[i] << " (posicion " << i << "): " << c[izq];
            if (der < c.size())
                std::cout << " y " << c[der];
            std::cout << "\n";
        }
    }
}

int main() {
    //===== MONTICULO MAXIMO con deque (como en el ejemplo de clase) =====
    std::cout << "TAREA: insertar 12, 6, 14, 2, 13 en un monticulo MAXIMO\n";
    std::deque<int> maximo; //contenedor sobre el que van a trabajar los algoritmos
    int datos[] = {12, 6, 14, 2, 13};
    for (int i = 0; i < 5; i++) {
        //INSERTAR: en un monticulo el dato nuevo siempre va al final (completando el ultimo nivel),
        //por eso se mete por detras con push_back...
        maximo.push_back(datos[i]);
        //...y luego push_heap lo va intercambiando con su padre mientras sea mayor, hasta que quede bien puesto.
        //Se le dice el inicio y el fin porque organiza todo el contenedor, del principio al final
        std::push_heap(maximo.begin(), maximo.end());
    }
    mostrar(maximo);
    std::cout << "  la raiz (front) es el mayor: " << maximo.front() << "\n";

    //ELIMINAR: en un monticulo no se elimina cualquier nodo (habria que buscarlo y eso es O(n)),
    //sino la RAIZ, porque ya se sabe quien es (el mayor o el menor).
    //pop_heap intercambia la raiz con el ultimo y baja ese ultimo hasta su lugar; asi el dato que se quiere
    //eliminar queda al FINAL del contenedor, donde se consulta con back() y se quita con pop_back()
    std::pop_heap(maximo.begin(), maximo.end());
    std::cout << "eliminar la raiz: sale el " << maximo.back() << "\n";
    maximo.pop_back(); //ahora si se quita del contenedor
    mostrar(maximo);

    //===== MONTICULO MINIMO =====
    //se le pasa std::greater<int>() como comparador: asi el padre queda menor o igual que sus hijos
    std::cout << "\nTAREA: insertar 12, 6, 14, 2, 13 en un monticulo MINIMO\n";
    std::deque<int> minimo;
    for (int i = 0; i < 5; i++) {
        minimo.push_back(datos[i]); //igual: al final
        std::push_heap(minimo.begin(), minimo.end(), std::greater<int>()); //y se sube, pero comparando al reves
    }
    mostrar(minimo);
    std::cout << "  la raiz (front) es el menor: " << minimo.front() << "\n";

    //===== make_heap: organizar de una vez un contenedor que ya tiene datos =====
    std::cout << "\nmake_heap sobre un vector con datos en desorden: 5 13 2 25 7 17 20 8 4\n";
    std::vector<int> v;
    int otros[] = {5, 13, 2, 25, 7, 17, 20, 8, 4};
    for (int i = 0; i < 9; i++)
        v.push_back(otros[i]);
    std::make_heap(v.begin(), v.end()); //reorganiza todo el vector para que cumpla la propiedad de maximo
    mostrar(v);

    //eliminar un elemento de la MITAD: se borra como en cualquier vector, pero se daña el monticulo,
    //asi que despues toca organizarlo otra vez con make_heap
    v.erase(v.begin() + 2); //borra la posicion 2
    std::make_heap(v.begin(), v.end());
    std::cout << "despues de borrar la posicion 2 y volver a hacer make_heap:\n";
    mostrar(v);
    //is_heap verifica si el contenedor cumple la propiedad de monticulo maximo
    std::cout << "  sigue siendo monticulo maximo (is_heap): " << (std::is_heap(v.begin(), v.end()) ? "si" : "no") << "\n";

    return 0;
}
