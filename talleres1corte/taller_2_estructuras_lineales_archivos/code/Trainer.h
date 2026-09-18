/**
 * @file Trainer.h
 * @brief Definición del Tipo Abstracto de Datos Trainer.
 *
 * Curso: Estructuras de Datos
 * Autor: Alejandro Castro Martínez
 * Fecha: 12 de agosto de 2026
 */

#ifndef TRAINER_H
#define TRAINER_H

#include "Team.h"

#include <string>
#include <vector>

/**
 * @brief Representa un entrenador con una colección de equipos Pokémon.
 */
class Trainer {

private:

    /** Nombre que identifica al entrenador. */
    std::string name;

    /** Vector que almacena los equipos pertenecientes al entrenador. */
    std::vector<Team> teamList;

public:

    /**
     * @brief Construye un entrenador inicialmente sin equipos.
     *
     * @param trainerName Nombre que identificará al entrenador.
     */
    Trainer(const std::string& trainerName);

    /**
     * @brief Retorna el nombre del entrenador.
     *
     * @return Nombre almacenado en el entrenador.
     */
    const std::string& getName() const;

    /**
     * @brief Retorna la cantidad de equipos almacenados.
     *
     * @return Número de equipos pertenecientes al entrenador.
     */
    unsigned int getTeamCount() const;

    /**
     * @brief Indica si el entrenador no tiene equipos registrados.
     *
     * @return true si el vector de equipos está vacío; false en caso contrario.
     */
    bool isEmpty() const;

    /**
     * @brief Busca un equipo mediante su nombre.
     *
     * La posición retornada puede utilizarse posteriormente con getTeam().
     *
     * @param teamName Nombre del equipo que se desea buscar.
     * @return Posición del equipo dentro del vector o -1 si no existe.
     */
    int findTeam(const std::string& teamName) const;

    /**
     * @brief Indica si un equipo pertenece al entrenador.
     *
     * @param teamName Nombre del equipo que se desea consultar.
     * @return true si el equipo existe; false en caso contrario.
     */
    bool containsTeam(const std::string& teamName) const;

    /**
     * @brief Agrega un equipo al final del vector.
     *
     * El equipo no se agrega si existe otro con el mismo nombre.
     *
     * @param team Equipo que se desea agregar.
     * @return true si el equipo fue agregado; false si ya existía.
     */
    bool addTeam(const Team& team);

    /**
     * @brief Elimina un equipo mediante su nombre.
     *
     * @param teamName Nombre del equipo que se desea eliminar.
     * @return true si el equipo fue eliminado; false si no fue encontrado.
     */
    bool removeTeam(const std::string& teamName);

    /**
     * @brief Retorna un equipo que puede consultarse y modificarse.
     *
     * La posición suministrada debe corresponder a una posición válida del
     * vector, obtenida previamente mediante findTeam().
     *
     * @param position Posición del equipo dentro del vector.
     * @return Referencia modificable al equipo encontrado.
     */
    Team& getTeam(int position);

    /**
     * @brief Retorna un equipo únicamente para consultar su información.
     *
     * Esta versión se utiliza cuando el entrenador es constante y no permite
     * modificar el equipo retornado. La posición debe ser válida.
     *
     * @param position Posición del equipo dentro del vector.
     * @return Referencia constante al equipo encontrado.
     */
    const Team& getTeam(int position) const;

    /**
     * @brief Restaura la salud de todos los Pokémon de todos los equipos.
     */
    void restoreAllTeams();

    /**
     * @brief Imprime el entrenador y todos sus equipos en orden.
     */
    void print() const;
};

#endif
