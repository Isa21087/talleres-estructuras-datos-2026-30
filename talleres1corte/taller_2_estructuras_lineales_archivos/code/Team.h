/**
 * @file Team.h
 * @brief Definición del Tipo Abstracto de Datos Team.
 *
 * Curso: Estructuras de Datos
 * Autor: Alejandro Castro Martínez
 * Fecha: 12 de agosto de 2026
 */

#ifndef TEAM_H
#define TEAM_H

#include "Pokemon.h"

#include <list>
#include <string>

/**
 * @brief Representa un equipo ordenado de máximo seis Pokémon.
 */
class Team { //clase llamada team 

private: //es privado por ende no se puede como tal trabaajr con lo que este aqui dentro q es nombre, cantidas max y la lisyta ordenada 

    /** Cantidad máxima de Pokémon permitidos dentro de un equipo. */
    static unsigned int maxPokemon;

    /** Nombre que identifica al equipo. */
    std::string name;

    /** Lista ordenada de Pokémon que pertenecen al equipo. */
    std::list<Pokemon> pokemonList;

public:
// froma en como se declara una fucnion en el .h dentro de una clase 
// tipoQueDevuelve nombreFuncion(parametros);
    /**
     * @brief Construye un equipo inicialmente vacío.
     *
     * @param teamName Nombre que identificará al equipo.
     */
    Team(const std::string& teamName); //contructor de la clase privada Team que recibe un string por referencia para evitar copias inncesarias, puede leerlo pero no modificarlo
    // debido al const  y ps lo otro es el nombre del parametro que recibe 
    
    /**
     * @brief Retorna el nombre del equipo.
     */
     
    const std::string& getName() const;
// ↑                            ↑
// No permite modificar        La funcion no modifica
// el texto retornado           el objeto Team

    /**
     * @brief Retorna la cantidad de Pokémon almacenados.
     */
    unsigned int getPokemonCount() const; // Función pública llamada getPokemonCount, 
    // que no recibe parámetros, no modifica el equipo y devuelve un entero sin signo

    /**
     * @brief Indica si el equipo no contiene Pokémon.
     *
     * @return true si el equipo está vacío; false en caso contrario.
     */
    bool isEmpty() const;

    /**
     * @brief Indica si el equipo alcanzó el límite de seis Pokémon.
     *
     * @return true si el equipo está lleno; false en caso contrario.
     */
    bool isFull() const;

    /**
     * @brief Retorna la posición que representa una búsqueda fallida.
     *
     * El iterador retornado se utiliza para comparar resultados de búsquedas
     * que permiten modificar el Pokémon encontrado.
     *
     * @return Iterador modificable correspondiente al final de la lista.
     */
    std::list<Pokemon>::iterator getNotFoundPosition();

    /**
     * @brief Retorna la posición constante que representa una búsqueda fallida.
     *
     * El iterador retornado se utiliza en búsquedas de solo consulta y no
     * permite modificar los Pokémon del equipo.
     *
     * @return Iterador constante correspondiente al final de la lista.
     */
    std::list<Pokemon>::const_iterator getNotFoundPosition() const;

    /**
     * @brief Busca un Pokémon por su nombre.
     *
     * El iterador retornado permite consultar y modificar el Pokémon
     * encontrado.
     *
     * @param pokemonName Nombre del Pokémon que se desea buscar.
     * @return Iterador modificable a la posición encontrada o
     *         getNotFoundPosition() si el Pokémon no existe.
     */
    std::list<Pokemon>::iterator findPokemon(
        const std::string& pokemonName
    );

    /**
     * @brief Busca un Pokémon por su nombre para consultar su información.
     *
     * El iterador retornado permite consultar el Pokémon, pero no modificarlo.
     *
     * @param pokemonName Nombre del Pokémon que se desea buscar.
     * @return Iterador constante a la posición encontrada o
     *         getNotFoundPosition() si el Pokémon no existe.
     */
    std::list<Pokemon>::const_iterator findPokemon(
        const std::string& pokemonName
    ) const;

    /**
     * @brief Indica si un Pokémon pertenece al equipo.
     *
     * @param pokemonName Nombre del Pokémon que se desea consultar.
     * @return true si el Pokémon existe; false en caso contrario.
     */
    bool containsPokemon(const std::string& pokemonName) const;

    /**
     * @brief Inserta un Pokémon en una posición específica del equipo.
     *
     * La posición cero representa el inicio de la lista. La inserción no se
     * realiza si el equipo está lleno, el Pokémon ya existe o la posición
     * está fuera del rango permitido.
     *
     * @param pokemon Pokémon que se desea insertar.
     * @param position Posición donde se insertará el Pokémon.
     * @return true si la inserción fue realizada; false en caso contrario.
     */
    bool addPokemon(
        const Pokemon& pokemon,
        unsigned int position
    );

    /**
     * @brief Elimina del equipo un Pokémon identificado por su nombre.
     *
     * @param pokemonName Nombre del Pokémon que se desea eliminar.
     * @return true si el Pokémon fue eliminado; false si no fue encontrado.
     */
    bool removePokemon(const std::string& pokemonName);

    /**
     * @brief Cambia la posición de un Pokémon dentro del equipo.
     *
     * La posición cero representa el inicio de la lista.
     *
     * @param pokemonName Nombre del Pokémon que se desea mover.
     * @param newPosition Nueva posición que ocupará dentro de la lista.
     * @return true si el cambio fue realizado; false en caso contrario.
     */
    bool changePokemonPosition(
        const std::string& pokemonName,
        unsigned int newPosition
    );

    /**
     * @brief Restaura completamente la salud de todos los Pokémon.
     */
    void restoreTeam();

    /**
     * @brief Indica si todos los Pokémon del equipo están debilitados.
     *
     * @return true si no quedan Pokémon disponibles; false en caso contrario.
     */
    bool isDefeated() const;

    /**
     * @brief Busca el primer Pokémon disponible para modificarlo en batalla.
     *
     * El iterador retornado permite aplicar daño o restaurar la salud del
     * Pokémon encontrado.
     *
     * @return Iterador modificable al primer Pokémon no debilitado o
     *         getNotFoundPosition() si no existe.
     */
    std::list<Pokemon>::iterator getFirstAvailablePokemon();

    /**
     * @brief Busca el primer Pokémon disponible para consultar su información.
     *
     * El iterador retornado permite consultar el Pokémon, pero no modificarlo.
     *
     * @return Iterador constante al primer Pokémon no debilitado o
     *         getNotFoundPosition() si no existe.
     */
    std::list<Pokemon>::const_iterator getFirstAvailablePokemon() const;

    /**
     * @brief Imprime el nombre y todos los Pokémon del equipo en orden.
     */
    void print() const;
};

#endif
