#include <iostream>
#include <string>

#include "SistemaExploracionLazaro.h"

using namespace std;

int main()
{
    SistemaExploracionLazaro sistema;
    string nombreArchivo;

    // pedimos el archivo que contiene los datos de la mision
    // el TAD principal se encarga de leerlo y construir el grafo
    cout << "Ingrese el archivo de entrada: ";
    cin >> nombreArchivo;

    if (!sistema.cargarPlanetas(nombreArchivo))
    {
        return 1;
    }

    // primero calculamos los pesos de las conexiones
    // porque el recorrido necesita conocer su consumo de combustible
    sistema.calcularCombustible();

    if (!sistema.realizarExploracion())
    {
        return 1;
    }

    // generamos los dos archivos usando el recorrido
    // que el sistema guardo durante la exploracion
    if (!sistema.generarDetalle())
    {
        return 1;
    }

    if (!sistema.generarResumen())
    {
        return 1;
    }

    return 0;
}
