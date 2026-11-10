#ifndef SISTEMA_EXPLORACION_LAZARO_H
#define SISTEMA_EXPLORACION_LAZARO_H

#include <string>
#include <vector>
#include "Grafo.h"

class SistemaExploracionLazaro
{
private:
    Grafo grafo;
    double k;
    double lambda;
    std::vector<Planeta> recorrido;
    double combustibleTotal;

public:
    SistemaExploracionLazaro();

    bool cargarPlanetas(const std::string& nombreArchivo);
    void calcularCombustible();
    bool realizarExploracion();
    bool generarDetalle();
    bool generarResumen();
};

#endif
