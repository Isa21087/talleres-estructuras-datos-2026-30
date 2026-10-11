//para compilar y ejecutar:  g++ -std=c++11 ejemploMultisetMultimap.cpp -o ejemploMultisetMultimap && ./ejemploMultisetMultimap

/* TAREA DE CLASE: multiset y multimap
   Son los otros dos contenedores de la STL que por debajo son un arbol rojinegro.
   La unica diferencia con set y map es que SI permiten repetidos:
   - multiset<T>: como el set, pero el mismo dato puede estar varias veces;
   - multimap<llave, valor>: como el map, pero la misma llave puede tener varios valores.
   Siguen ordenados (el recorrido de begin a end sigue siendo inorden) y siguen siendo O(log n). */

#include <iostream> //para std::cout
#include <set> //aqui esta std::multiset (en la misma libreria que set)
#include <map> //aqui esta std::multimap (en la misma libreria que map)
#include <string> //para std::string
#include <utility> //para std::make_pair

int main() {
    //----- multiset -----
    std::multiset<int> notas; //arbol rojinegro de enteros que admite repetidos
    int datos[] = {4, 3, 5, 3, 4, 3, 2};
    for (int i = 0; i < 7; i++)
        notas.insert(datos[i]); //en un multiset insert SIEMPRE inserta, aunque el dato ya este

    std::cout << "multiset (ordenado, con repetidos): ";
    std::multiset<int>::iterator it;
    for (it = notas.begin(); it != notas.end(); it++)
        std::cout << *it << " ";
    std::cout << "\n";

    //count dice cuantas veces esta un dato (en un set solo podia ser 0 o 1)
    std::cout << "cuantas veces esta el 3: " << notas.count(3) << "\n";

    //OJO con erase: erase(valor) borra TODAS las copias de ese valor...
    std::cout << "erase(4) borro " << notas.erase(4) << " elementos\n";
    //...y erase(iterador) borra solo la copia de esa posicion. find devuelve la primera copia
    notas.erase(notas.find(3));
    std::cout << "despues de borrar un solo 3, quedan " << notas.count(3) << " treses\n";

    //----- multimap -----
    //llave: materia, valor: nombre del estudiante. Una materia puede tener varios estudiantes
    std::multimap<std::string, std::string> inscritos;

    //el multimap NO tiene el operador [], porque una llave puede tener varios valores y no sabria cual devolver.
    //Se inserta con insert pasandole la pareja (llave, valor), que se arma con make_pair
    inscritos.insert(std::make_pair("Estructuras", "Ana"));
    inscritos.insert(std::make_pair("Calculo", "Luis"));
    inscritos.insert(std::make_pair("Estructuras", "Pedro"));
    inscritos.insert(std::make_pair("Estructuras", "Sofia"));
    inscritos.insert(std::make_pair("Calculo", "Maria"));

    std::cout << "inscritos en Estructuras: " << inscritos.count("Estructuras") << "\n";

    //equal_range devuelve una pareja de iteradores: el primero apunta al primer elemento con esa llave
    //y el segundo a la posicion DESPUES del ultimo. Asi se recorren todos los valores de una misma llave
    std::pair<std::multimap<std::string, std::string>::iterator,
              std::multimap<std::string, std::string>::iterator> rango = inscritos.equal_range("Estructuras");
    std::cout << "estudiantes de Estructuras: ";
    std::multimap<std::string, std::string>::iterator itMap;
    for (itMap = rango.first; itMap != rango.second; itMap++)
        std::cout << itMap->second << " "; //second es el valor (el estudiante)
    std::cout << "\n";

    //recorrido completo: queda ordenado por llave (las materias), y los de la misma llave quedan juntos
    std::cout << "todo el multimap:\n";
    for (itMap = inscritos.begin(); itMap != inscritos.end(); itMap++)
        std::cout << "  " << itMap->first << " -> " << itMap->second << "\n";

    return 0;
}
