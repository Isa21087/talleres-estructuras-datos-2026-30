
#include "Grafo.h"

Grafo::Grafo()
{
}

bool Grafo::agregarPlaneta(const Planeta &planeta)
{
    // verificamos que el planeta tenga nombre, que su factor temporal
    // sea mayor o igual a uno y que no exista otro planeta con el mismo nombre
    if (planeta.obtenerNombre().empty() || planeta.obtenerFactorTemporal() < 1 ||
        buscarPlaneta(planeta.obtenerNombre()) != -1)
    {
        return false;
    }

    planetas.push_back(planeta);

    // agregamos una columna a cada fila que ya existe porque
    // ahora hay un planeta más con el que se pueden conectar
    for (int i = 0; i < (int)pesos.size(); i++)
    {
        pesos[i].push_back(0);
        peligrosas[i].push_back(false);
    }

    // agregamos la fila del nuevo planeta con sus conexiones
    // inicialmente en cero y sin peligros marcados
    int cantidad = planetas.size();
    pesos.push_back(std::vector<double>(cantidad, 0));
    peligrosas.push_back(std::vector<bool>(cantidad, false));

    return true;
}

int Grafo::cantidadPlanetas() const
{
    return planetas.size();
}

int Grafo::buscarPlaneta(const std::string &nombre) const
{
    // buscamos el nombre y devolvemos su posición
    // esa posición también identifica al planeta en las matrices
    for (int i = 0; i < (int)planetas.size(); i++)
    {
        if (planetas[i].obtenerNombre() == nombre)
        {
            return i;
        }
    }

    return -1;
}

const Planeta &Grafo::obtenerPlaneta(int indice) const
{
    return planetas[indice];
}

void Grafo::establecerPeso(int origen, int destino, double peso)
{
    // guardamos el mismo peso en ambas direcciones
    // porque las conexiones entre planetas son bidireccionales
    pesos[origen][destino] = peso;
    pesos[destino][origen] = peso;
}

double Grafo::obtenerPeso(int origen, int destino) const
{
    return pesos[origen][destino];
}

void Grafo::marcarPeligrosa(int origen, int destino)
{
    // si una conexión es peligrosa de ida también lo es de vuelta
    peligrosas[origen][destino] = true;
    peligrosas[destino][origen] = true;
}

bool Grafo::esPeligrosa(int origen, int destino) const
{
    return peligrosas[origen][destino];
}
