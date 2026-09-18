/**
 * @file Battle.h
 * @brief Definición del Tipo Abstracto de Datos Battle.
 *
 * Curso: Estructuras de Datos
 * Autor: Alejandro Castro Martínez
 * Fecha: 12 de agosto de 2026
 */

#ifndef BATTLE_H
#define BATTLE_H

#include "Team.h"

#include <deque>
#include <string>

/**
 * @brief Representa una batalla entre dos equipos Pokémon.
 *
 * La batalla trabaja con copias de los equipos originales, por lo que los
 * cambios de salud no afectan los equipos almacenados por los entrenadores.
 */
class Battle {

private:

    /** Nombre del entrenador propietario del primer equipo. */
    std::string firstTrainerName;

    /** Nombre del entrenador propietario del segundo equipo. */
    std::string secondTrainerName;

    /** Copia del primer equipo participante en la batalla. */
    Team firstTeam;

    /** Copia del segundo equipo participante en la batalla. */
    Team secondTeam;

    /** Historial ordenado de los acontecimientos de la batalla. */
    std::deque<std::string> battleHistory;

    /** Nombre del equipo ganador de la batalla. */
    std::string winnerTeamName;

    /** Nombre del entrenador propietario del equipo ganador. */
    std::string winnerTrainerName;

    /** Indica si la batalla ya fue ejecutada y finalizada. */
    bool finished;

    /**
     * @brief Calcula el multiplicador correspondiente a la relación de tipos.
     *
     * @param attackerType Tipo del Pokémon atacante.
     * @param defenderType Tipo del Pokémon defensor.
     * @return 2.0 si el ataque es fuerte, 0.5 si es débil o 1.0 si es normal.
     */
    double getTypeMultiplier(
        PokemonType attackerType,
        PokemonType defenderType
    ) const;

    /**
     * @brief Calcula el daño causado por un Pokémon a otro.
     *
     * El daño se calcula mediante la fórmula:
     *
     * daño = max(1, ataque × multiplicador - defensa / 2)
     *
     * @param attacker Pokémon que realiza el ataque.
     * @param defender Pokémon que recibe el ataque.
     * @return Cantidad de puntos de daño calculados.
     */
    int calculateDamage(
        const Pokemon& attacker,
        const Pokemon& defender
    ) const;

    /**
     * @brief Ejecuta el ataque de un Pokémon contra otro.
     *
     * La función calcula el daño, modifica la salud del defensor y registra
     * en el historial qué Pokémon atacó a cuál. Si el defensor queda sin
     * salud, también registra su debilitamiento.
     *
     * @param attacker Pokémon que realiza el ataque.
     * @param defender Pokémon que recibe el ataque.
     */
    void executeAttack(
        Pokemon& attacker,
        Pokemon& defender
    );

public:

    /**
     * @brief Construye una batalla utilizando copias de dos equipos.
     *
     * Los equipos copiados conservan inicialmente la salud que tienen al
     * momento de construir la batalla.
     *
     * @param trainerOneName Nombre del entrenador del primer equipo.
     * @param teamOne Primer equipo participante.
     * @param trainerTwoName Nombre del entrenador del segundo equipo.
     * @param teamTwo Segundo equipo participante.
     */
    Battle(
        const std::string& trainerOneName,
        const Team& teamOne,
        const std::string& trainerTwoName,
        const Team& teamTwo
    );

    /** @brief Retorna el nombre del entrenador del primer equipo. */
    const std::string& getFirstTrainerName() const;

    /** @brief Retorna el nombre del entrenador del segundo equipo. */
    const std::string& getSecondTrainerName() const;

    /**
     * @brief Retorna el primer equipo utilizado en la batalla.
     *
     * La referencia permite consultar el estado del equipo después de
     * combatir, pero no modificarlo desde fuera de Battle.
     *
     * @return Referencia constante al primer equipo.
     */
    const Team& getFirstTeam() const;

    /**
     * @brief Retorna el segundo equipo utilizado en la batalla.
     *
     * La referencia permite consultar el estado del equipo después de
     * combatir, pero no modificarlo desde fuera de Battle.
     *
     * @return Referencia constante al segundo equipo.
     */
    const Team& getSecondTeam() const;

    /**
     * @brief Indica si la batalla ya finalizó.
     *
     * @return true si la batalla terminó; false si aún no se ha ejecutado.
     */
    bool isFinished() const;

    /**
     * @brief Retorna el nombre del equipo ganador.
     *
     * Si la batalla no se ha ejecutado o terminó sin ganador, retorna una
     * cadena vacía.
     *
     * @return Nombre del equipo ganador.
     */
    const std::string& getWinnerTeamName() const;

    /** @brief Retorna el nombre del entrenador ganador. */
    const std::string& getWinnerTrainerName() const;

    /**
     * @brief Retorna el historial completo de la batalla.
     *
     * El historial puede consultarse, pero no modificarse desde fuera de
     * la clase.
     *
     * @return Referencia constante al historial de eventos.
     */
    const std::deque<std::string>& getBattleHistory() const;

    /**
     * @brief Ejecuta la batalla completa entre los dos equipos.
     *
     * En cada enfrentamiento combaten los primeros Pokémon disponibles. El
     * Pokémon con mayor velocidad ataca primero. Si tienen igual velocidad,
     * comienza el Pokémon del primer equipo.
     *
     * Cuando un Pokémon queda debilitado, es reemplazado por el siguiente
     * Pokémon disponible de su equipo. La batalla termina cuando uno de los
     * equipos se queda sin Pokémon con salud.
     *
     * La batalla no puede ejecutarse nuevamente hasta llamar resetBattle().
     *
     * @return true si la batalla fue ejecutada; false si ya había finalizado.
     */
    bool runBattle();

    /**
     * @brief Restablece la batalla para permitir una nueva ejecución.
     *
     * Restaura la salud de los Pokémon de ambos equipos, elimina el historial,
     * borra el nombre del ganador y cambia el estado a no finalizado.
     */
    void resetBattle();

    /**
     * @brief Imprime todos los acontecimientos almacenados en el historial.
     */
    void printBattleHistory() const;
};

#endif
