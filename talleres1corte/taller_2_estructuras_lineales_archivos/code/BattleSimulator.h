/**
 * @file BattleSimulator.h
 * @brief Definición del Tipo Abstracto de Datos BattleSimulator.
 *
 * Curso: Estructuras de Datos
 * Autor: Alejandro Castro Martínez
 * Fecha: 12 de agosto de 2026
 */

#ifndef BATTLE_SIMULATOR_H
#define BATTLE_SIMULATOR_H

#include "Battle.h"
#include "Trainer.h"

#include <deque>
#include <string>
#include <vector>

/**
 * @brief Almacena el resultado de un equipo en la última comparación.
 */
struct TeamResult {

    /** Nombre del entrenador propietario del equipo. */
    std::string trainerName;

    /** Nombre del equipo evaluado. */
    std::string teamName;

    /** Cantidad total de batallas disputadas por el equipo. */
    unsigned int battles;

    /** Cantidad de batallas ganadas por el equipo. */
    unsigned int victories;

    /** Porcentaje de victorias obtenido por el equipo. */
    double winPercentage;
};

/**
 * @brief Administra entrenadores, batallas y comparaciones entre equipos.
 */
class BattleSimulator {

private:

    /** Vector que almacena los entrenadores registrados. */
    std::vector<Trainer> trainerList;

    /** Historial de todas las batallas ejecutadas por el simulador. */
    std::deque<Battle> battleHistory;

    /** Resultados producidos por la comparación más reciente. */
    std::vector<TeamResult> comparisonResults;

    /**
     * @brief Busca el resultado de un equipo en la comparación actual.
     *
     * @param trainerName Nombre del entrenador propietario.
     * @param teamName Nombre del equipo buscado.
     * @return Posición del resultado dentro del vector o -1 si no existe.
     */
    int findComparisonResult(
        const std::string& trainerName,
        const std::string& teamName
    ) const;

    /**
     * @brief Crea los resultados iniciales de dos entrenadores.
     *
     * Agrega al vector un resultado con cero batallas y cero victorias por
     * cada equipo perteneciente a los entrenadores comparados.
     *
     * @param firstTrainer Primer entrenador de la comparación.
     * @param secondTrainer Segundo entrenador de la comparación.
     */
    void initializeComparisonResults(
        const Trainer& firstTrainer,
        const Trainer& secondTrainer
    );

    /**
     * @brief Registra el resultado de una batalla para un equipo.
     *
     * La función aumenta la cantidad de batallas disputadas y, cuando
     * corresponde, también aumenta la cantidad de victorias.
     *
     * @param trainerName Nombre del entrenador propietario.
     * @param teamName Nombre del equipo que participó.
     * @param won Indica si el equipo ganó la batalla.
     */
    void registerTeamResult(
        const std::string& trainerName,
        const std::string& teamName,
        bool won
    );

    /**
     * @brief Calcula los porcentajes de todos los resultados almacenados.
     */
    void calculateWinPercentages();

public:

    /**
     * @brief Construye un simulador inicialmente vacío.
     */
    BattleSimulator();

    /**
     * @brief Retorna la cantidad de entrenadores registrados.
     *
     * @return Número de entrenadores almacenados.
     */
    unsigned int getTrainerCount() const;

    /**
     * @brief Retorna la cantidad de batallas ejecutadas.
     *
     * @return Número de batallas almacenadas en el historial.
     */
    unsigned int getBattleCount() const;

    /**
     * @brief Indica si el simulador no contiene entrenadores.
     *
     * @return true si no hay entrenadores; false en caso contrario.
     */
    bool isEmpty() const;

    /**
     * @brief Busca un entrenador mediante su nombre.
     *
     * @param trainerName Nombre del entrenador buscado.
     * @return Posición dentro del vector o -1 si no existe.
     */
    int findTrainer(const std::string& trainerName) const;

    /**
     * @brief Indica si un entrenador está registrado.
     *
     * @param trainerName Nombre del entrenador consultado.
     * @return true si existe; false en caso contrario.
     */
    bool containsTrainer(const std::string& trainerName) const;

    /**
     * @brief Agrega un entrenador al final del vector.
     *
     * El entrenador no se agrega si existe otro con el mismo nombre.
     *
     * @param trainer Entrenador que se desea agregar.
     * @return true si fue agregado; false si su nombre ya existía.
     */
    bool addTrainer(const Trainer& trainer);

    /**
     * @brief Elimina un entrenador mediante su nombre.
     *
     * @param trainerName Nombre del entrenador que se desea eliminar.
     * @return true si fue eliminado; false si no fue encontrado.
     */
    bool removeTrainer(const std::string& trainerName);

    /**
     * @brief Retorna un entrenador que puede consultarse y modificarse.
     *
     * La posición debe corresponder a un valor válido obtenido mediante
     * findTrainer().
     *
     * @param position Posición del entrenador dentro del vector.
     * @return Referencia modificable al entrenador.
     */
    Trainer& getTrainer(int position);

    /**
     * @brief Retorna un entrenador únicamente para consultar su información.
     *
     * La referencia retornada no permite modificar al entrenador.
     *
     * @param position Posición del entrenador dentro del vector.
     * @return Referencia constante al entrenador.
     */
    const Trainer& getTrainer(int position) const;

    /**
     * @brief Retorna una batalla almacenada en el historial.
     *
     * La batalla puede consultarse, pero no modificarse.
     *
     * @param position Posición de la batalla dentro del historial.
     * @return Referencia constante a la batalla.
     */
    const Battle& getBattle(int position) const;

    /**
     * @brief Retorna los resultados de la comparación más reciente.
     *
     * @return Referencia constante al vector de resultados.
     */
    const std::vector<TeamResult>& getComparisonResults() const;

    /**
     * @brief Ejecuta una batalla entre dos equipos seleccionados por nombre.
     *
     * Los entrenadores y equipos deben existir. La batalla se ejecuta y se
     * agrega al final del historial.
     *
     * @param firstTrainerName Nombre del primer entrenador.
     * @param firstTeamName Nombre del equipo del primer entrenador.
     * @param secondTrainerName Nombre del segundo entrenador.
     * @param secondTeamName Nombre del equipo del segundo entrenador.
     * @return true si la batalla fue ejecutada; false si algún dato no existe.
     */
    bool executeBattle(
        const std::string& firstTrainerName,
        const std::string& firstTeamName,
        const std::string& secondTrainerName,
        const std::string& secondTeamName
    );

    /**
     * @brief Compara todos los equipos de dos entrenadores.
     *
     * Cada equipo del primer entrenador se enfrenta una vez contra cada equipo
     * del segundo. Las batallas se conservan en el historial.
     *
     * Los resultados anteriores se reemplazan, pero las batallas anteriores
     * permanecen almacenadas.
     *
     * La comparación calcula resultados tanto para los equipos del primer
     * entrenador como para los equipos del segundo entrenador.
     *
     * @param firstTrainerName Nombre del primer entrenador.
     * @param secondTrainerName Nombre del segundo entrenador.
     * @return true si la comparación fue ejecutada; false si los entrenadores
     *         no existen, son el mismo o alguno no tiene equipos.
     */
    bool compareTrainers(
        const std::string& firstTrainerName,
        const std::string& secondTrainerName
    );

    /**
     * @brief Retorna todos los mejores equipos de un entrenador.
     *
     * Se consideran mejores los equipos que tengan el porcentaje de victorias
     * más alto dentro de la comparación más reciente. Si varios equipos tienen
     * el mismo porcentaje máximo, todos son incluidos.
     *
     * @param trainerName Nombre del entrenador consultado.
     * @return Vector con los nombres de los mejores equipos.
     */
    std::vector<std::string> getBestTeams(
        const std::string& trainerName
    ) const;

    /**
     * @brief Imprime todos los entrenadores registrados.
     */
    void printTrainers() const;

    /**
     * @brief Imprime los resultados de la comparación más reciente.
     */
    void printComparisonResults() const;

    /**
     * @brief Imprime el historial completo de batallas.
     */
    void printBattleHistory() const;
};

#endif
