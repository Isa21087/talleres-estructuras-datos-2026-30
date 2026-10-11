//para compilar y ejecutar:  g++ -std=c++11 ejemploCarros.cpp -o ejemploCarros && ./ejemploCarros

/* ARBOL ROJINEGRO CON UNA CLASE PROPIA (como en el taller: carros con placas)
   - set<Carro>: como solo hay un valor (el carro), se usa el set. Funciona porque Carro tiene definido el <.
   - map<string, Carro>: si se quisiera buscar el carro a partir de su placa, la placa seria la llave
     y el carro el valor. Aqui la llave es string, que ya tiene <, asi que Carro no necesitaria el <. */

#include <iostream> //para std::cout
#include <set> //para std::set
#include <map> //para std::map
#include <string> //para std::string
#include "Carro.h" //clase Carro con el operador < definido

int main() {
    //----- set de carros -----
    std::set<Carro> parqueadero; //arbol rojinegro de carros, ordenado por placa (usa Carro::operator<)

    parqueadero.insert(Carro("KJL482", "Mazda", 2019)); //se crea un carro y se inserta en el arbol
    parqueadero.insert(Carro("ABC123", "Renault", 2015));
    parqueadero.insert(Carro("XYZ999", "Chevrolet", 2022));
    parqueadero.insert(Carro("FGH256", "Toyota", 2020));

    //otro carro con una placa que ya existe: para el set son "iguales" (ninguno es menor que el otro),
    //asi que no lo inserta aunque la marca sea distinta
    bool insertado = parqueadero.insert(Carro("ABC123", "Kia", 2024)).second; //.second dice si se inserto
    std::cout << "insertar otra vez la placa ABC123: " << (insertado ? "si" : "no, la placa ya estaba") << "\n";

    //recorrido de begin a end: sale en orden de placa (inorden del arbol)
    std::cout << "carros en el parqueadero (ordenados por placa):\n";
    std::set<Carro>::iterator it;
    for (it = parqueadero.begin(); it != parqueadero.end(); it++)
        //it-> accede a los metodos del carro que esta en esa posicion
        std::cout << "  " << it->obtenerPlaca() << " " << it->obtenerMarca() << " " << it->obtenerModelo() << "\n";

    //para buscar con find hay que pasarle un Carro; como se compara solo por placa, basta con llenar la placa
    std::set<Carro>::iterator encontrado = parqueadero.find(Carro("FGH256", "", 0));
    if (encontrado != parqueadero.end())
        std::cout << "buscar placa FGH256: es un " << encontrado->obtenerMarca() << "\n";

    parqueadero.erase(Carro("KJL482", "", 0)); //eliminar tambien compara por placa
    std::cout << "despues de sacar KJL482 quedan " << parqueadero.size() << " carros\n";

    //----- map de placa -> carro -----
    std::map<std::string, Carro> registro; //llave: placa (string), valor: el carro completo
    registro["ABC123"] = Carro("ABC123", "Renault", 2015); //[] crea la llave y le asigna el carro
    registro["XYZ999"] = Carro("XYZ999", "Chevrolet", 2022);

    //consulta por llave: el arbol se recorre comparando placas y se saca el carro (el valor)
    std::cout << "registro[\"XYZ999\"] es un " << registro["XYZ999"].obtenerMarca() << "\n";

    std::map<std::string, Carro>::iterator itMap;
    for (itMap = registro.begin(); itMap != registro.end(); itMap++)
        //first es la llave (la placa) y second es el valor (el carro)
        std::cout << "  llave " << itMap->first << " -> modelo " << itMap->second.obtenerModelo() << "\n";

    return 0;
}
