/**
 * @file Team.cxx
 * @brief Implementación del Tipo Abstracto de Datos Team.
 *
 * Curso: Estructuras de Datos
 * Autor: Alejandro Castro Martínez
 * Fecha: 12 de agosto de 2026
 */

#include "Team.h"

#include <iostream>

// Inicializa el límite compartido por todos los equipos.
unsigned int Team::maxPokemon = 6;

// Construye un equipo vacío con el nombre recibido.
Team::Team(const std::string& teamName)
    : name(teamName) {
}

// Retorna el nombre que identifica al equipo.
const std::string& Team::getName() const {
    return name;
}

// Retorna la cantidad actual de Pokémon del equipo.
unsigned int Team::getPokemonCount() const {
    return static_cast<unsigned int>(pokemonList.size());
}

// Determina si la lista de Pokémon está vacía.
bool Team::isEmpty() const {
    return pokemonList.empty();
}

// Determina si el equipo alcanzó la cantidad máxima de Pokémon.
bool Team::isFull() const {
    return getPokemonCount() >= maxPokemon;
}

// Retorna el final de la lista para representar una búsqueda fallida.
std::list<Pokemon>::iterator Team::getNotFoundPosition() {
    return pokemonList.end();
}

// Retorna el final constante de la lista para búsquedas de solo consulta.
std::list<Pokemon>::const_iterator Team::getNotFoundPosition() const {
    return pokemonList.end();
}

// Busca un Pokémon y retorna un iterador que permite modificarlo.
std::list<Pokemon>::iterator Team::findPokemon(
    const std::string& pokemonName
) {
    //TODO #01 (Buscar un Pokemon y retornar su posicion modificable)
    /*
     * Recorra pokemonList desde el inicio hasta el final utilizando un
     * iterador modificable.
     *
     * Compare el nombre de cada Pokemon con pokemonName. Si encuentra una
     * coincidencia, retorne el iterador correspondiente a esa posicion.
     *
     * Si termina el recorrido sin encontrar el Pokemon, retorne la posicion
     * utilizada por el equipo para representar una busqueda fallida.
     *
     * La funcion debe retornar un iterator y permitir que otras operaciones
     * modifiquen el Pokemon encontrado.
     */
    std::list<Pokemon>::iterator itPokemon = pokemonList.begin();
    for(;itPokemon!=pokemonList.end();itPokemon++){
        if(pokemonName == itPokemon->getName()){
            return itPokemon;
        } 
    }

    return getNotFoundPosition();
}

// Busca un Pokémon y retorna un iterador que solo permite consultarlo.
std::list<Pokemon>::const_iterator Team::findPokemon(
    const std::string& pokemonName
) const {
    //TODO #02 (Buscar un Pokemon sin permitir su modificacion)
    /*
     * Recorra pokemonList desde el inicio hasta el final utilizando un
     * iterador constante.
     *
     * Compare el nombre de cada Pokemon con pokemonName. Si encuentra una
     * coincidencia, retorne el iterador constante correspondiente.
     *
     * Si termina el recorrido sin encontrar el Pokemon, retorne la posicion
     * constante utilizada para representar una busqueda fallida.
     *
     * Esta version de la funcion no debe permitir la modificacion de los
     * Pokemon almacenados. Analice la diferencia entre esta operacion y la
     * version modificable implementada en el TODO anterior.
     */
    std::list<Pokemon>::const_iterator itPokemon = pokemonList.begin();
    for(;itPokemon!=pokemonList.end();itPokemon++){
        if(pokemonName == itPokemon->getName()){
            return itPokemon;
        } 
    }
    return getNotFoundPosition();
}

// Comprueba si ya existe un Pokémon con el nombre recibido.
bool Team::containsPokemon(const std::string& pokemonName) const {
    return findPokemon(pokemonName) != getNotFoundPosition();
}

// Inserta un Pokémon en una posición válida de la lista.
bool Team::addPokemon(
    const Pokemon& pokemon,
    unsigned int position
) {
    //TODO #03 (Agregar un Pokemon en una posicion valida del equipo)
    /*
     * Valide inicialmente que el equipo no se encuentre lleno y que no
     * exista otro Pokemon con el mismo nombre. Si alguna de estas condiciones
     * no se cumple, la insercion debe rechazarse.
     *
     * Compruebe que position sea una posicion valida. Se permite insertar
     * desde la posicion cero hasta la posicion correspondiente a la cantidad
     * actual de Pokemon. Esta ultima representa una insercion al final.
     *
     * Construya un iterador modificable que comience en pokemonList.begin()
     * y avancelo hasta alcanzar la posicion solicitada.
     *
     * Inserte el Pokemon antes del iterador obtenido. La operacion debe
     * conservar el orden de los elementos que ya pertenecen al equipo.
     *
     * Retorne true solamente cuando la insercion sea realizada. Retorne
     * false cuando el equipo este lleno, el nombre este repetido o la
     * posicion se encuentre fuera del rango permitido.
     */
    
    //Verificar que el equipo no esta lleno
    if( isFull() == true){
        //std::cout<<"El equipo esta lleno"<<std::endl;
        return false;
    }

    //Verificar que no exista otro Pokemon con el mismo nombre
    if(containsPokemon(pokemon.getName()) == true){
        //std::cout<<"Este Pokemon ya existe en el equipo"<<std::endl;
        return false;
    }

    //Verificar que position sea valido
    if (position > getPokemonCount()){
        //std::cout<<"Esta posicion no es valida"<<std::endl;
        return false;
    }

// Iterador modificable
std::list<Pokemon>::iterator itPokemon = pokemonList.begin();

// Avanzar el iterador hasta la posicion solicitada
unsigned int currentPosition = 0;

while (currentPosition < position) {
    ++itPokemon;
    ++currentPosition;
}

// Insertar el Pokemon antes del iterador obtenido
pokemonList.insert(itPokemon, pokemon);

return true;
}


// Elimina un Pokémon cuando su nombre se encuentra en el equipo.
bool Team::removePokemon(const std::string& pokemonName) {
    std::list<Pokemon>::iterator pokemonPosition = findPokemon(pokemonName);

    if (pokemonPosition == getNotFoundPosition()) {
        return false;
    }

    pokemonList.erase(pokemonPosition);
    return true;
}

// Extrae un Pokémon y lo inserta nuevamente en la posición solicitada.
bool Team::changePokemonPosition(
    const std::string& pokemonName,
    unsigned int newPosition
) {
    if (newPosition >= getPokemonCount()) {
        return false;
    }

    std::list<Pokemon>::iterator pokemonPosition = findPokemon(pokemonName);

    if (pokemonPosition == getNotFoundPosition()) {
        return false;
    }

    Pokemon pokemonToMove = *pokemonPosition;
    pokemonList.erase(pokemonPosition);

    std::list<Pokemon>::iterator insertionPosition = pokemonList.begin();
    unsigned int currentPosition = 0;

    while (currentPosition < newPosition) {
        ++insertionPosition;
        ++currentPosition;
    }

    pokemonList.insert(insertionPosition, pokemonToMove);
    return true;
}

// Restaura la salud de todos los Pokémon almacenados.
void Team::restoreTeam() {
    std::list<Pokemon>::iterator pokemonPosition = pokemonList.begin();

    while (pokemonPosition != pokemonList.end()) {
        pokemonPosition->restoreHealth();
        ++pokemonPosition;
    }
}

// Comprueba si no queda ningún Pokémon con puntos de salud.
bool Team::isDefeated() const {
    //TODO #04 (Determinar si el equipo fue derrotado)
    /*
     * Determine si el equipo no tiene ningun Pokemon disponible para
     * continuar una batalla.
     *
     * Utilice getFirstAvailablePokemon() para buscar el primer Pokemon que
     * conserve puntos de salud. No realice un nuevo recorrido directo sobre
     * pokemonList, pues la operacion de busqueda ya se encuentra disponible.
     *
     * Compare el iterador retornado con la posicion constante utilizada para
     * representar que no se encontro ningun Pokemon.
     *
     * Retorne true cuando todos los Pokemon esten debilitados o cuando el
     * equipo este vacio. Retorne false cuando exista al menos un Pokemon que
     * todavia pueda combatir.
     *
     * Tenga en cuenta que este metodo es constante, por lo que debe utilizar
     * las versiones de consulta de las operaciones involucradas.
     */

    std::list<Pokemon>::const_iterator pokemonPosition =
        getFirstAvailablePokemon();

    return pokemonPosition == getNotFoundPosition();
}


// Retorna el primer Pokémon ordenado que todavía conserva puntos de salud.
std::list<Pokemon>::iterator Team::getFirstAvailablePokemon() {
    std::list<Pokemon>::iterator pokemonPosition = pokemonList.begin();

    while (pokemonPosition != pokemonList.end()) {
        if (!pokemonPosition->isFainted()) {
            return pokemonPosition;
        }

        ++pokemonPosition;
    }

    return getNotFoundPosition();
}

// Retorna para consulta el primer Pokémon que conserva puntos de salud.
std::list<Pokemon>::const_iterator Team::getFirstAvailablePokemon() const {
    std::list<Pokemon>::const_iterator pokemonPosition = pokemonList.begin();

    while (pokemonPosition != pokemonList.end()) {
        if (!pokemonPosition->isFainted()) {
            return pokemonPosition;
        }

        ++pokemonPosition;
    }

    return getNotFoundPosition();
}

// Imprime el nombre del equipo y las tarjetas de sus Pokémon en orden.
void Team::print() const {
    std::cout << "==================================================\n";
    std::cout << "EQUIPO: " << name << '\n';
    std::cout << "Cantidad de Pokemon: " << getPokemonCount()
              << " / " << maxPokemon << '\n';
    std::cout << "==================================================\n";

    if (isEmpty()) {
        std::cout << "El equipo no contiene Pokemon.\n";
        return;
    }

    std::list<Pokemon>::const_iterator pokemonPosition = pokemonList.begin();
    unsigned int position = 0;

    while (pokemonPosition != pokemonList.end()) {
        std::cout << "\nPosicion " << position << '\n';
        pokemonPosition->print();

        ++pokemonPosition;
        ++position;
    }
}
