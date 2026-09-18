/**
 * @file Trainer.cxx
 * @brief Implementación del Tipo Abstracto de Datos Trainer.
 *
 * Curso: Estructuras de Datos
 * Autor: Alejandro Castro Martínez
 * Fecha: 12 de agosto de 2026
 */

#include "Trainer.h"

#include <iostream>

// Construye un entrenador vacío con el nombre recibido.
Trainer::Trainer(const std::string& trainerName)
    : name(trainerName) {
}

// Retorna el nombre que identifica al entrenador.
const std::string& Trainer::getName() const {
    return name;
}

// Retorna la cantidad actual de equipos del entrenador.
unsigned int Trainer::getTeamCount() const {
    return teamList.size();
}

// Determina si el vector de equipos está vacío.
bool Trainer::isEmpty() const {
    return teamList.empty();
}

// Busca un equipo y retorna su posición dentro del vector.
int Trainer::findTeam(const std::string& teamName) const {
    std::vector<Team>::const_iterator teamPosition = teamList.begin();
    int position = 0;

    while (teamPosition != teamList.end()) {
        if (teamPosition->getName() == teamName) {
            return position;
        }

        ++teamPosition;
        ++position;
    }

    return -1;
}

// Comprueba si ya existe un equipo con el nombre recibido.
bool Trainer::containsTeam(const std::string& teamName) const {
    return findTeam(teamName) != -1;
}

// Agrega un equipo al final del vector si su nombre no está repetido.
bool Trainer::addTeam(const Team& team) {
    if (containsTeam(team.getName())) {
        return false;
    }

    teamList.push_back(team);
    return true;
}

// Elimina un equipo cuando su nombre se encuentra en el entrenador.
bool Trainer::removeTeam(const std::string& teamName) {
    int position = findTeam(teamName);

    if (position == -1) {
        return false;
    }

    std::vector<Team>::iterator teamPosition = teamList.begin();
    int currentPosition = 0;

    while (currentPosition < position) {
        ++teamPosition;
        ++currentPosition;
    }

    teamList.erase(teamPosition);
    return true;
}

// Retorna una referencia que permite modificar el equipo solicitado.
Team& Trainer::getTeam(int position) {
    return teamList[position];
}

// Retorna una referencia constante para consultar el equipo solicitado.
const Team& Trainer::getTeam(int position) const {
    return teamList[position];
}

// Restaura la salud de todos los Pokémon de todos los equipos.
void Trainer::restoreAllTeams() {
    std::vector<Team>::iterator teamPosition = teamList.begin();

    while (teamPosition != teamList.end()) {
        teamPosition->restoreTeam();
        ++teamPosition;
    }
}

// Imprime el entrenador y todos sus equipos en el orden almacenado.
void Trainer::print() const {
    std::cout << "##################################################\n";
    std::cout << "ENTRENADOR: " << name << '\n';
    std::cout << "Cantidad de equipos: " << getTeamCount() << '\n';
    std::cout << "##################################################\n";

    if (isEmpty()) {
        std::cout << "El entrenador no tiene equipos registrados.\n";
        return;
    }

    std::vector<Team>::const_iterator teamPosition = teamList.begin();
    int position = 0;

    while (teamPosition != teamList.end()) {
        std::cout << "\nEquipo en la posicion " << position << '\n';
        teamPosition->print();

        ++teamPosition;
        ++position;
    }
}
