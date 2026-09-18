/**
 * @file Pokemon.cxx
 * @brief Implementación del Tipo Abstracto de Datos Pokemon.
 *
 * Curso: Estructuras de Datos
 * Autor: Alejandro Castro Martínez
 * Fecha: 12 de agosto de 2026
 */

#include "Pokemon.h"

#include <iomanip>
#include <iostream>

// Construye el Pokémon e inicializa su salud actual con la salud máxima.
Pokemon::Pokemon(
    const std::string& pokemonName,
    PokemonType pokemonType,
    int pokemonHealth,
    int pokemonAttack,
    int pokemonDefense,
    int pokemonSpeed
) : name(pokemonName),
    type(pokemonType),
    maximumHealth(pokemonHealth),
    currentHealth(pokemonHealth),
    attack(pokemonAttack),
    defense(pokemonDefense),
    speed(pokemonSpeed) {
}

// Retorna el nombre almacenado.
const std::string& Pokemon::getName() const {
    return name;
}

// Retorna el tipo elemental almacenado.
PokemonType Pokemon::getType() const {
    return type;
}

// Retorna la salud máxima con la que el Pokémon inicia una batalla.
int Pokemon::getMaximumHealth() const {
    return maximumHealth;
}

// Retorna la cantidad de salud que el Pokémon conserva actualmente.
int Pokemon::getCurrentHealth() const {
    return currentHealth;
}

// Retorna la estadística utilizada para calcular el daño causado.
int Pokemon::getAttack() const {
    return attack;
}

// Retorna la estadística utilizada para reducir el daño recibido.
int Pokemon::getDefense() const {
    return defense;
}

// Retorna la estadística utilizada para decidir el orden de ataque.
int Pokemon::getSpeed() const {
    return speed;
}

// Reduce la salud actual sin permitir que quede por debajo de cero.
void Pokemon::receiveDamage(int damage) {
    currentHealth -= damage;

    if (currentHealth < 0) {
        currentHealth = 0;
    }
}

// Recupera todos los puntos de salud originales del Pokémon.
void Pokemon::restoreHealth() {
    currentHealth = maximumHealth;
}

// Determina si el Pokémon se quedó sin puntos de salud.
bool Pokemon::isFainted() const {
    return currentHealth == 0;
}

// Imprime todos los atributos con un formato similar a una tarjeta.
void Pokemon::print() const {
    const std::string healthInformation =
        std::to_string(currentHealth) + " / " + std::to_string(maximumHealth);

    std::cout << "+--------------------------------+\n";
    std::cout << "|          POKEMON CARD          |\n";
    std::cout << "+--------------------------------+\n";
    std::cout << "| Nombre:    " << std::left << std::setw(20) << name << "|\n";
    std::cout << "| Tipo:      " << std::left << std::setw(20)
              << pokemonTypeToString(type) << "|\n";
    std::cout << "| Salud:     " << std::left << std::setw(20)
              << healthInformation << "|\n";
    std::cout << "| Ataque:    " << std::left << std::setw(20) << attack << "|\n";
    std::cout << "| Defensa:   " << std::left << std::setw(20) << defense << "|\n";
    std::cout << "| Velocidad: " << std::left << std::setw(20) << speed << "|\n";
    std::cout << "+--------------------------------+\n";
}

// Convierte el tipo enumerado en una cadena fácil de leer.
std::string pokemonTypeToString(PokemonType type) {
    switch (type) {
        case PokemonType::FIRE:
            return "Fuego";
        case PokemonType::WATER:
            return "Agua";
        case PokemonType::GRASS:
            return "Planta";
        case PokemonType::ELECTRIC:
            return "Electrico";
        case PokemonType::GROUND:
            return "Tierra";
        case PokemonType::FLYING:
            return "Volador";
    }

    return "Desconocido";
}
