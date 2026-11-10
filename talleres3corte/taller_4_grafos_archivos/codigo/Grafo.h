#ifndef GRAFO_H
#define GRAFO_H

#include <string>
#include <vector>

#include "Planeta.h"

class Grafo {
private:
    std::vector<Planeta> planetas;
    std::vector<std::vector<double>> pesos;
    std::vector<std::vector<bool>> peligrosas;

public:
    Grafo();

    bool agregarPlaneta(const Planeta& planeta);

    int cantidadPlanetas() const;

    int buscarPlaneta(const std::string& nombre) const;

    const Planeta& obtenerPlaneta(int indice) const;

    void establecerPeso(int origen, int destino, double peso);

    double obtenerPeso(int origen, int destino) const;

    void marcarPeligrosa(int origen, int destino);

    bool esPeligrosa(int origen, int destino) const;
};

#endif