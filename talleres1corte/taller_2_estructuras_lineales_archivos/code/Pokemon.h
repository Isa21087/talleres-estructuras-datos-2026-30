/**
 * @file Pokemon.h
 * @brief Definición del Tipo Abstracto de Datos Pokemon.
 *
 * Curso: Estructuras de Datos
 * Autor: Alejandro Castro Martínez
 * Fecha: 12 de agosto de 2026
 */

#ifndef POKEMON_H
#define POKEMON_H

#include <string>

/**
 * @brief Tipos de Pokémon permitidos en el simulador.
 */
enum class PokemonType {
    FIRE,
    WATER,
    GRASS,
    ELECTRIC,
    GROUND,
    FLYING
};

/**
 * @brief Convierte un tipo de Pokémon en una cadena de texto.
 *
 * @param type Tipo de Pokémon que se desea convertir.
 * @return Nombre del tipo en español.
 */
std::string pokemonTypeToString(PokemonType type);

/**
 * @brief Representa un Pokémon con sus estadísticas básicas de batalla.
 */
class Pokemon {

private:

    /** Nombre que identifica al Pokémon. */
    std::string name;

    /** Tipo elemental al que pertenece el Pokémon. */
    PokemonType type;

    /** Cantidad máxima de puntos de salud del Pokémon. */
    int maximumHealth;

    /** Cantidad de puntos de salud disponibles actualmente. */
    int currentHealth;

    /** Capacidad ofensiva utilizada para calcular el daño causado. */
    int attack;

    /** Capacidad defensiva utilizada para reducir el daño recibido. */
    int defense;

    /** Velocidad utilizada para determinar el orden de ataque. */
    int speed;

public:

    /**
     * @brief Construye un Pokémon con sus estadísticas iniciales.
     *
     * La salud actual inicia con el mismo valor de la salud máxima.
     *
     * @param pokemonName Nombre del Pokémon.
     * @param pokemonType Tipo elemental del Pokémon.
     * @param pokemonHealth Puntos máximos de salud.
     * @param pokemonAttack Valor de ataque.
     * @param pokemonDefense Valor de defensa.
     * @param pokemonSpeed Valor de velocidad.
     */
    Pokemon(
        const std::string& pokemonName,
        PokemonType pokemonType,
        int pokemonHealth,
        int pokemonAttack,
        int pokemonDefense,
        int pokemonSpeed
    );

    /**
     * @brief Retorna el nombre del Pokémon.
     */
    const std::string& getName() const;

    /**
     * @brief Retorna el tipo elemental del Pokémon.
     */
    PokemonType getType() const;

    /**
     * @brief Retorna la cantidad máxima de puntos de salud.
     */
    int getMaximumHealth() const;

    /**
     * @brief Retorna la cantidad actual de puntos de salud.
     */
    int getCurrentHealth() const;

    /**
     * @brief Retorna el valor de ataque.
     */
    int getAttack() const;

    /**
     * @brief Retorna el valor de defensa.
     */
    int getDefense() const;

    /**
     * @brief Retorna el valor de velocidad.
     */
    int getSpeed() const;

    /**
     * @brief Reduce la salud actual según el daño recibido.
     *
     * @param damage Cantidad de puntos de daño.
     */
    void receiveDamage(int damage);

    /**
     * @brief Restaura completamente la salud del Pokémon.
     */
    void restoreHealth();

    /**
     * @brief Indica si el Pokémon se encuentra debilitado.
     *
     * @return true si su salud actual es cero; false en caso contrario.
     */
    bool isFainted() const;

    /**
     * @brief Imprime todos los datos del Pokémon con formato de tarjeta.
     */
    void print() const;
};

#endif
