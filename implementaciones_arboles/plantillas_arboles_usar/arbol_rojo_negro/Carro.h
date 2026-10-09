//proteccion de inclusion multiple: evita que la clase Carro se declare dos veces si se incluye en varios lados
#ifndef __CARRO_H__
#define __CARRO_H__

#include <string> //para std::string

/* TAREA DE CLASE: como se define el operador menor que (<) dentro de una clase.
   Para poder guardar objetos de una clase propia dentro de un set (o usarlos como llave de un map),
   la clase debe tener definido el operador <, porque el arbol rojinegro lo usa para decidir si un dato
   va a la izquierda (menor) o a la derecha (mayor). Si no esta definido, el programa NO compila.
   OJO: tiene que ser el menor que; definir solo el mayor que (>) no sirve.

   Aqui los carros se comparan por su PLACA, asi que en un set no puede haber dos carros con la misma placa. */

class Carro {

    protected: //atributos del carro
        std::string placa; //placa del carro; es lo que se usa para ordenar
        std::string marca; //marca del carro
        int modelo; //año del modelo

    public:
        //constructor vacio: el map lo necesita para poder crear el valor cuando se usa [] con una llave nueva
        Carro() {
            this->placa = "";
            this->marca = "";
            this->modelo = 0;
        }

        //constructor con todos los datos
        Carro(std::string placa, std::string marca, int modelo) {
            this->placa = placa; //this->placa es el atributo; placa (sin this) es el parametro
            this->marca = marca;
            this->modelo = modelo;
        }

        std::string obtenerPlaca() const { return this->placa; } //const: el metodo no modifica el carro
        std::string obtenerMarca() const { return this->marca; }
        int obtenerModelo() const { return this->modelo; }

        //DEFINICION DEL OPERADOR MENOR QUE:
        //- se llama operator< y devuelve bool (true si este carro es "menor" que el otro);
        //- recibe el otro carro por referencia constante (const Carro&): por referencia para no copiarlo
        //  y constante para prometer que no se modifica;
        //- el const del final dice que este metodo tampoco modifica al carro que lo llama.
        //  El set lo exige asi, porque los datos guardados en el arbol no se pueden cambiar
        //  (si se cambiaran, el arbol quedaria desordenado)
        bool operator<(const Carro& otro) const {
            return this->placa < otro.placa; //se compara por placa (los string ya tienen su propio <)
        }
};

#endif //fin de la proteccion de inclusion multiple
