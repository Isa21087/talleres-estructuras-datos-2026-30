//para compilar y ejecutar:  g++ -std=c++11 ejemploMonticuloManual.cpp -o ejemploMonticuloManual && ./ejemploMonticuloManual

/* MONTICULO MAXIMO HECHO A MANO (para ver paso a paso lo que hacen push_heap y pop_heap)
   La profe pidio aprenderse de memoria el proceso de SUBIR (al insertar) y de BAJAR (al eliminar).
   Este programa hace ese proceso con un vector y las formulas, e imprime cada intercambio.

   Formulas (raiz en la posicion 0):
   - hijo izquierdo de i: 2*i + 1
   - hijo derecho de i:   2*i + 2
   - padre de i:          (i - 1) / 2   (en division entera de C++ ya se aproxima hacia abajo)

   INSERTAR: se pone el dato al final (completando el ultimo nivel) y se SUBE: mientras sea mayor que
   su padre, se intercambia con el. No hay rotaciones, solo intercambios.
   ELIMINAR (siempre la raiz): se toma el ultimo elemento (el de mas a la derecha del ultimo nivel),
   se pone en la raiz, se quita del final y se BAJA: mientras sea menor que alguno de sus hijos,
   se intercambia con el MAYOR de sus hijos. */

#include <iostream> //para std::cout
#include <vector> //el monticulo se guarda en un vector (arreglo dinamico)

//formulas para moverse por el arbol sin apuntadores
int padre(int i) { return (i - 1) / 2; }
int hijoIzq(int i) { return 2 * i + 1; }
int hijoDer(int i) { return 2 * i + 2; }

//imprime el arreglo completo
void mostrar(const std::vector<int>& m) {
    std::cout << "[ ";
    for (unsigned int i = 0; i < m.size(); i++)
        std::cout << m[i] << " ";
    std::cout << "]";
}

//intercambia los datos de dos posiciones del vector
void intercambiar(std::vector<int>& m, int a, int b) {
    int temporal = m[a]; //se guarda uno de los dos para no perderlo
    m[a] = m[b];
    m[b] = temporal;
}

//INSERTAR en un monticulo maximo (lo mismo que hacen push_back + push_heap)
void insertar(std::vector<int>& m, int val) {
    m.push_back(val); //1. el dato nuevo va al final: asi se sigue completando el ultimo nivel
    int i = m.size() - 1; //posicion donde quedo el dato nuevo
    std::cout << "insertar " << val << " al final: "; mostrar(m); std::cout << "\n";

    //2. SUBIR: mientras no sea la raiz (i > 0) y sea mayor que su padre, se intercambia con el padre
    while (i > 0 && m[i] > m[padre(i)]) {
        std::cout << "   " << m[i] << " es mayor que su padre " << m[padre(i)] << ", se intercambian: ";
        intercambiar(m, i, padre(i));
        i = padre(i); //el dato ahora esta donde estaba el padre; se sigue revisando desde ahi
        mostrar(m); std::cout << "\n";
    }
}

//ELIMINAR LA RAIZ de un monticulo maximo (lo mismo que hacen pop_heap + back + pop_back)
int eliminarRaiz(std::vector<int>& m) {
    int raiz = m[0]; //el dato que se va a sacar: el mayor de todos
    m[0] = m.back(); //1. el ultimo (el de mas a la derecha del ultimo nivel) se pone en la raiz
    m.pop_back(); //2. y se quita del final; asi el ultimo nivel se va liberando por la derecha
    std::cout << "eliminar la raiz " << raiz << ", el ultimo sube a la raiz: "; mostrar(m); std::cout << "\n";

    //3. BAJAR: mientras el dato tenga algun hijo mayor que el, se intercambia con el MAYOR de sus hijos
    //(con el mayor para que el nuevo padre quede mayor que los dos)
    int i = 0;
    int n = m.size();
    while (hijoIzq(i) < n) { //si no tiene hijo izquierdo tampoco tiene derecho: es hoja, ya no baja mas
        int mayor = hijoIzq(i); //se supone que el mayor es el izquierdo...
        if (hijoDer(i) < n && m[hijoDer(i)] > m[mayor]) //...pero si existe el derecho y es mas grande, es ese
            mayor = hijoDer(i);
        if (m[i] >= m[mayor]) //si ya es mayor o igual que sus hijos, cumple la propiedad: se para
            break;
        std::cout << "   " << m[i] << " es menor que su hijo " << m[mayor] << ", se intercambian: ";
        intercambiar(m, i, mayor);
        i = mayor; //se sigue revisando desde la posicion a la que bajo
        mostrar(m); std::cout << "\n";
    }
    return raiz;
}

int main() {
    std::vector<int> monticulo; //monticulo maximo vacio

    //TAREA de clase: insertar 12, 6, 14, 2, 13 en un monticulo maximo
    int datos[] = {12, 6, 14, 2, 13};
    for (int i = 0; i < 5; i++)
        insertar(monticulo, datos[i]);
    std::cout << "monticulo final: "; mostrar(monticulo); std::cout << "\n\n";

    //se elimina la raiz dos veces para ver como baja el dato
    eliminarRaiz(monticulo);
    std::cout << "\n";
    eliminarRaiz(monticulo);
    std::cout << "monticulo final: "; mostrar(monticulo); std::cout << "\n";

    return 0;
}
