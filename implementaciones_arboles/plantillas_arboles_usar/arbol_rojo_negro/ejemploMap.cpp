//para compilar y ejecutar:  g++ -std=c++11 ejemploMap.cpp -o ejemploMap && ./ejemploMap

/* ARBOL ROJINEGRO CON std::map (ejemplo de los meses visto en clase)
   El map recibe DOS clases: map<llave, valor>. Guarda parejas llave-valor, por ejemplo
   placa -> carro, cedula -> datos de la persona, o en este ejemplo: nombre del mes -> dias que tiene.

   Por debajo tambien es un arbol rojinegro, pero el arbol se arma SOLO con la LLAVE:
   cada nodo guarda la llave y el valor, y la llave decide si se va a la izquierda o a la derecha.
   El valor no se usa para armar el arbol, solo para guardar la informacion.
   Por eso la que debe tener definido el operador menor que (<) es la llave, y las llaves deben ser UNICAS.

   El map "se ve" como un vector dinamico donde los indices no son 0, 1, 2... sino las llaves:
   meses["june"] es como pedir la posicion "june" del vector. */

#include <iostream> //para std::cout
#include <map> //libreria donde esta definido std::map
#include <string> //para std::string
#include <cstring> //para strcmp, que compara el contenido de dos cadenas de caracteres

//La llave de este map es const char*, que es un APUNTADOR a una cadena de caracteres.
//Para los apuntadores el < si existe, pero compara DIRECCIONES DE MEMORIA, no el texto.
//Como se quiere ordenar por el contenido (orden alfabetico), se define esta estructura con un operador ()
//que le dice al map como comparar dos llaves. strcmp devuelve un numero negativo si s1 va antes que s2
struct ltstr { //"lt" = less than = menor que
    bool operator()(const char* s1, const char* s2) const {
        return strcmp(s1, s2) < 0; //true si s1 va antes que s2 en orden alfabetico
    }
};

int main() {
    //map<tipo de la llave, tipo del valor, comparador>: el tercer parametro solo hace falta porque
    //const char* no compara bien por si solo
    std::map<const char*, int, ltstr> meses;

    //con [] se inserta: si la llave NO existe, se crea y se añade al arbol (con cambios de color y rotaciones);
    //si la llave YA existe, se SOBRESCRIBE su valor
    meses["january"] = 31;
    meses["february"] = 28;
    meses["march"] = 31;
    meses["april"] = 30;
    meses["may"] = 31;
    meses["june"] = 30;
    meses["july"] = 31;
    meses["august"] = 31;
    meses["september"] = 30;
    meses["october"] = 31;
    meses["november"] = 30;
    meses["december"] = 31;

    //con [] tambien se consulta: el map va al arbol, busca el nodo con la llave "june"
    //y saca el valor que tiene guardado (el int), es decir 30
    std::cout << "june -> " << meses["june"] << "\n";

    //find busca la llave pero NO devuelve el valor sino un ITERADOR a la posicion donde esta
    std::map<const char*, int, ltstr>::iterator actual = meses.find("june");
    std::map<const char*, int, ltstr>::iterator anterior = actual; //otro iterador en la misma posicion
    std::map<const char*, int, ltstr>::iterator siguiente = actual; //y otro mas
    ++siguiente; //se mueve una posicion hacia adelante
    --anterior; //se mueve una posicion hacia atras
    //adelante y atras no es izquierda y derecha en el arbol: como se ve como un vector ordenado,
    //el anterior y el siguiente son en orden alfabetico segun la llave.
    //Cada posicion es una pareja: con first se accede a la llave y con second al valor
    std::cout << "anterior (en orden alfabetico): " << anterior->first << "\n";
    std::cout << "siguiente (en orden alfabetico): " << siguiente->first << "\n";

    //las llaves son unicas: poner otra vez "may" no crea otro nodo, sobrescribe el valor
    meses["may"] = 10;
    std::cout << "may despues de sobrescribir: " << meses["may"] << " (sigue habiendo " << meses.size() << " meses)\n";
    meses["may"] = 31; //se deja otra vez bien

    //recorrido de begin a end: igual que en el set, es el recorrido INORDEN del arbol (orden alfabetico),
    //por eso empieza en april y termina en september
    std::cout << "recorrido completo:\n";
    std::map<const char*, int, ltstr>::iterator it;
    for (it = meses.begin(); it != meses.end(); it++)
        std::cout << "  " << it->first << " -> " << it->second << "\n";

    //si la llave es std::string NO hace falta el comparador, porque string ya tiene definido el <
    std::map<std::string, int> diasSemana; //llave: nombre del dia, valor: numero del dia
    diasSemana["lunes"] = 1;
    diasSemana["martes"] = 2;
    diasSemana["miercoles"] = 3;
    std::cout << "map con llave string, primero en orden alfabetico: " << diasSemana.begin()->first << "\n";

    //eliminar por llave: tambien rebalancea el arbol por debajo
    diasSemana.erase("martes");
    std::cout << "despues de borrar martes quedan " << diasSemana.size() << " dias\n";

    return 0;
}
