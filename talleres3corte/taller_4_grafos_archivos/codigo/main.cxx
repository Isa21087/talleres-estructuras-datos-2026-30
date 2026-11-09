#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

#include "Grafo.h"

using namespace std;

int main()
{
    Grafo grafo;
    string nombreArchivo;

    double k, lambda;
    int cantidadPlanetas;

    cout << "Ingrese el archivo de entrada: ";
    cin >> nombreArchivo;

    ifstream archivo(nombreArchivo);

    if (!archivo.is_open())
    {
        cout << "No se pudo abrir el archivo" << endl;
        return 1;
    }

    archivo >> k >> lambda;
    archivo >> cantidadPlanetas;

    if (!archivo || cantidadPlanetas <= 0 || k <= 0 || lambda < 0)
    {
        cout << "Los datos iniciales del archivo no son validos" << endl;
        return 1;
    }

    // guardamos los nombres de las conexiones peligrosas
    // porque algunos planetas pueden aparecer mas adelante en el archivo
    vector<vector<string>> conexionesPeligrosas;

    for (int i = 0; i < cantidadPlanetas; i++)
    {
        Planeta planeta;
        int cantidadPeligrosas;

        archivo >> planeta.nombre >> planeta.x >> planeta.y >> planeta.z >> planeta.factorTemporal >> cantidadPeligrosas;

        if (!archivo || cantidadPeligrosas < 0)
        {
            cout << "Error al leer los datos de un planeta" << endl;
            return 1;
        }

        if (!grafo.agregarPlaneta(planeta))
        {
            cout << "Datos invalidos del planeta: "
                 << planeta.nombre << endl;
            return 1;
        }

        vector<string> destinos;

        // leemos los nombres sin marcar todavia las conexiones
        // primero necesitamos tener todos los planetas registrados
        for (int j = 0; j < cantidadPeligrosas; j++)
        {
            string destino;
            archivo >> destino;

            if (!archivo)
            {
                cout << "Error al leer una conexion peligrosa" << endl;
                return 1;
            }

            destinos.push_back(destino);
        }

        conexionesPeligrosas.push_back(destinos);
    }

    archivo.close();

    // comprobamos que los destinos existan
    // y que las conexiones peligrosas aparezcan en ambos sentidos
    for (int i = 0; i < grafo.cantidadPlanetas(); i++)
    {
        for (int j = 0; j < (int)conexionesPeligrosas[i].size(); j++)
        {
            string nombreDestino = conexionesPeligrosas[i][j];
            int destino = grafo.buscarPlaneta(nombreDestino);

            if (destino == -1 || destino == i)
            {
                cout << "Conexion peligrosa invalida desde "
                     << grafo.obtenerPlaneta(i).nombre
                     << " hacia " << nombreDestino << endl;
                return 1;
            }

            // revisamos que un mismo destino no aparezca repetido
            for (int p = 0; p < j; p++)
            {
                if (conexionesPeligrosas[i][p] == nombreDestino)
                {
                    cout << "Conexion peligrosa repetida desde "
                         << grafo.obtenerPlaneta(i).nombre
                         << " hacia " << nombreDestino << endl;
                    return 1;
                }
            }

            // buscamos la misma conexion desde el otro planeta
            bool encontrada = false;

            for (int p = 0; p < (int)conexionesPeligrosas[destino].size(); p++)
            {
                if (conexionesPeligrosas[destino][p] ==
                    grafo.obtenerPlaneta(i).nombre)
                {
                    encontrada = true;
                }
            }

            if (!encontrada)
            {
                cout << "La conexion peligrosa no aparece "
                     << "en ambos sentidos" << endl;
                return 1;
            }
        }
    }

    // despues de comprobarlas marcamos las conexiones peligrosas
    // en la matriz que ya tiene nuestro grafo
    for (int i = 0; i < grafo.cantidadPlanetas(); i++)
    {
        for (int j = 0; j < (int)conexionesPeligrosas[i].size(); j++)
        {
            int destino = grafo.buscarPlaneta(conexionesPeligrosas[i][j]);
            grafo.marcarPeligrosa(i, destino);
        }
    }

    cout << "Conexiones peligrosas verificadas" << endl;

    // calculamos el combustible entre cada par de planetas
    // usando las coordenadas y los factores temporales
    for (int i = 0; i < grafo.cantidadPlanetas(); i++)
    {
        for (int j = i + 1; j < grafo.cantidadPlanetas(); j++)
        {
            Planeta origen = grafo.obtenerPlaneta(i);
            Planeta destino = grafo.obtenerPlaneta(j);

            double diferenciaX = origen.x - destino.x;
            double diferenciaY = origen.y - destino.y;
            double diferenciaZ = origen.z - destino.z;

            double distancia = sqrt(
                diferenciaX * diferenciaX +
                diferenciaY * diferenciaY +
                diferenciaZ * diferenciaZ);

            // el factor gravitacional modifica el combustible necesario
            double factor = 1 + lambda *
                                    ((origen.factorTemporal - 1) + (destino.factorTemporal - 1)) / 2;

            double combustible = k * distancia * factor;

            // guardamos el combustible en los dos sentidos
            grafo.establecerPeso(i, j, combustible);
        }
    }

    cout << "Combustible de las conexiones calculado" << endl;

    // mostramos la matriz para comprobar los valores calculados
    cout << endl
         << "Matriz de combustible" << endl;

    for (int i = 0; i < grafo.cantidadPlanetas(); i++)
    {
        for (int j = 0; j < grafo.cantidadPlanetas(); j++)
        {
            cout << grafo.obtenerPeso(i, j) << " ";
        }
        cout << endl;
    }

    cout << endl;
    cout << "Cantidad de planetas: "
         << grafo.cantidadPlanetas() << endl;

    for (int i = 0; i < grafo.cantidadPlanetas(); i++)
    {
        cout << "Planeta: "
             << grafo.obtenerPlaneta(i).nombre << endl;
    }

    int tierra = grafo.buscarPlaneta("Tierra");

    if (tierra == -1)
    {
        cout << "No se encontro la Tierra" << endl;
        return 1;
    }

    int cantidad = grafo.cantidadPlanetas();
    vector<int> visitados(cantidad, 0);

    int actual = tierra;
    double combustibleTotal = 0;
    double distanciaTotal = 0;

    int conexionesSeguras = 0;
    int conexionesPeligrosasUsadas = 0;
    int desplazamientos = 0;

    double mayorCombustible = 0;
    double menorCombustible = 0;

    string origenMayor;
    string destinoMayor;
    string origenMenor;
    string destinoMenor;

    // guardamos los planetas en el orden en que los visita la nave
    vector<int> recorrido;
    recorrido.push_back(tierra);

    // abrimos el archivo donde guardaremos el detalle del recorrido
    ofstream detalle("detalle_recorrido.txt");

    if (!detalle.is_open())
    {
        cout << "No se pudo crear el archivo de detalle" << endl;
        return 1;
    }

    // mostramos los valores numericos con dos decimales
    detalle.setf(ios::fixed);
    detalle.precision(2);

    detalle << "MISIÓN LÁZARO - DETALLE DEL RECORRIDO" << endl;

    visitados[tierra] = 1;

    cout << endl
         << "Recorrido de la nave" << endl;

    // visitamos todos los planetas pendientes
    // sin contar la tierra porque ya es nuestro punto de partida
    for (int paso = 1; paso < cantidad; paso++)
    {
        int elegido = -1;

        // primero buscamos conexiones seguras
        // solamente si no hay ninguna buscamos las peligrosas
        for (int tipo = 0; tipo < 2 && elegido == -1; tipo++)
        {
            for (int i = 0; i < cantidad; i++)
            {
                if (visitados[i] == 0 &&
                    grafo.esPeligrosa(actual, i) == tipo)
                {
                    if (elegido == -1 ||
                        grafo.obtenerPeso(actual, i) <
                            grafo.obtenerPeso(actual, elegido))
                    {
                        elegido = i;
                    }
                    else if (grafo.obtenerPeso(actual, i) ==
                                 grafo.obtenerPeso(actual, elegido) &&
                             grafo.obtenerPlaneta(i).nombre <
                                 grafo.obtenerPlaneta(elegido).nombre)
                    {
                        // si gastan lo mismo elegimos el planeta
                        // cuyo nombre aparezca primero alfabeticamente
                        elegido = i;
                    }
                }
            }
        }

        if (elegido == -1)
        {
            cout << "No se encontro otro planeta" << endl;
            return 1;
        }

        double combustible = grafo.obtenerPeso(actual, elegido);
        bool peligrosa = grafo.esPeligrosa(actual, elegido);

        cout << grafo.obtenerPlaneta(actual).nombre
             << " -> " << grafo.obtenerPlaneta(elegido).nombre
             << " | combustible: " << combustible << " | ";

        if (peligrosa)
        {
            cout << "peligrosa" << endl;
        }
        else
        {
            cout << "segura" << endl;
        }

        combustibleTotal += combustible;

        Planeta origen = grafo.obtenerPlaneta(actual);
        Planeta destino = grafo.obtenerPlaneta(elegido);

        double diferenciaX = origen.x - destino.x;
        double diferenciaY = origen.y - destino.y;
        double diferenciaZ = origen.z - destino.z;

        double distancia = sqrt(
            diferenciaX * diferenciaX +
            diferenciaY * diferenciaY +
            diferenciaZ * diferenciaZ);

        double factor = 1 + lambda *
                                ((origen.factorTemporal - 1) + (destino.factorTemporal - 1)) / 2;

        // sumamos la distancia y contamos las conexiones utilizadas
        distanciaTotal += distancia;

        if (peligrosa)
        {
            conexionesPeligrosasUsadas++;
        }
        else
        {
            conexionesSeguras++;
        }

        // guardamos los desplazamientos de mayor y menor consumo
        if (desplazamientos == 0 || combustible > mayorCombustible)
        {
            mayorCombustible = combustible;
            origenMayor = origen.nombre;
            destinoMayor = destino.nombre;
        }

        if (desplazamientos == 0 || combustible < menorCombustible)
        {
            menorCombustible = combustible;
            origenMenor = origen.nombre;
            destinoMenor = destino.nombre;
        }

        desplazamientos++;
        recorrido.push_back(elegido);

        // guardamos los datos antes de cambiar el planeta actual
        detalle << endl;
        detalle << "Desplazamiento " << paso << endl;
        detalle << "Origen: " << origen.nombre << endl;
        detalle << "Destino: " << destino.nombre << endl;
        detalle << "Distancia: " << distancia << endl;
        detalle << "Factor gravitacional: " << factor << endl;
        detalle << "Combustible consumido: " << combustible << endl;

        if (peligrosa)
        {
            detalle << "Tipo de conexión: Peligrosa" << endl;
        }
        else
        {
            detalle << "Tipo de conexión: Segura" << endl;
        }

        detalle << "Combustible acumulado: "
                << combustibleTotal << endl;

        visitados[elegido] = 1;
        actual = elegido;
    }

    // cuando terminamos las visitas regresamos directamente a tierra
    // aunque la conexion de regreso sea peligrosa
    if (actual != tierra)
    {
        double combustibleRegreso = grafo.obtenerPeso(actual, tierra);
        bool peligrosa = grafo.esPeligrosa(actual, tierra);

        cout << grafo.obtenerPlaneta(actual).nombre
             << " -> Tierra"
             << " | combustible: " << combustibleRegreso << " | ";

        if (peligrosa)
        {
            cout << "peligrosa" << endl;
        }
        else
        {
            cout << "segura" << endl;
        }

        combustibleTotal += combustibleRegreso;

        Planeta origen = grafo.obtenerPlaneta(actual);
        Planeta destino = grafo.obtenerPlaneta(tierra);

        double diferenciaX = origen.x - destino.x;
        double diferenciaY = origen.y - destino.y;
        double diferenciaZ = origen.z - destino.z;

        double distancia = sqrt(
            diferenciaX * diferenciaX +
            diferenciaY * diferenciaY +
            diferenciaZ * diferenciaZ);

        double factor = 1 + lambda *
                                ((origen.factorTemporal - 1) + (destino.factorTemporal - 1)) / 2;

        // el regreso tambien suma distancia y combustible
        // y cuenta para las conexiones utilizadas
        distanciaTotal += distancia;

        if (peligrosa)
        {
            conexionesPeligrosasUsadas++;
        }
        else
        {
            conexionesSeguras++;
        }

        if (desplazamientos == 0 || combustibleRegreso > mayorCombustible)
        {
            mayorCombustible = combustibleRegreso;
            origenMayor = origen.nombre;
            destinoMayor = destino.nombre;
        }

        if (desplazamientos == 0 || combustibleRegreso < menorCombustible)
        {
            menorCombustible = combustibleRegreso;
            origenMenor = origen.nombre;
            destinoMenor = destino.nombre;
        }

        desplazamientos++;
        recorrido.push_back(tierra);

        // registramos el regreso como el ultimo desplazamiento
        detalle << endl;
        detalle << "Desplazamiento " << cantidad << endl;
        detalle << "Origen: " << origen.nombre << endl;
        detalle << "Destino: " << destino.nombre << endl;
        detalle << "Distancia: " << distancia << endl;
        detalle << "Factor gravitacional: " << factor << endl;
        detalle << "Combustible consumido: "
                << combustibleRegreso << endl;

        if (peligrosa)
        {
            detalle << "Tipo de conexión: Peligrosa" << endl;
        }
        else
        {
            detalle << "Tipo de conexión: Segura" << endl;
        }

        detalle << "Combustible acumulado: "
                << combustibleTotal << endl;
    }

    detalle.close();

    // creamos el segundo archivo con el resumen de la mision
    ofstream resumen("resumen.txt");

    if (!resumen.is_open())
    {
        cout << "No se pudo crear el archivo de resumen" << endl;
        return 1;
    }

    // usamos dos decimales para las distancias y el combustible
    resumen.setf(ios::fixed);
    resumen.precision(2);

    resumen << "MISIÓN LÁZARO - RESUMEN" << endl;
    resumen << endl;

    resumen << "Planetas registrados: " << cantidad << endl;
    resumen << "Planetas explorados: " << cantidad - 1 << endl;

    resumen << endl;
    resumen << "Recorrido:" << endl;

    // mostramos los planetas en el mismo orden del recorrido
    for (int i = 0; i < (int)recorrido.size(); i++)
    {
        resumen << grafo.obtenerPlaneta(recorrido[i]).nombre;

        if (i < (int)recorrido.size() - 1)
        {
            resumen << " -> ";
        }
    }

    resumen << endl
            << endl;

    resumen << "Desplazamientos realizados: "
            << desplazamientos << endl;
    resumen << "Distancia total: " << distanciaTotal << endl;
    resumen << "Combustible total: " << combustibleTotal << endl;
    resumen << "Conexiones seguras utilizadas: "
            << conexionesSeguras << endl;
    resumen << "Conexiones peligrosas utilizadas: "
            << conexionesPeligrosasUsadas << endl;

    if (desplazamientos > 0)
    {
        resumen << endl;
        resumen << "Mayor consumo:" << endl;
        resumen << origenMayor << " -> " << destinoMayor << endl;
        resumen << "Combustible consumido: " << mayorCombustible << endl;

        resumen << endl;
        resumen << "Menor consumo:" << endl;
        resumen << origenMenor << " -> " << destinoMenor << endl;
        resumen << "Combustible consumido: " << menorCombustible << endl;
    }

    resumen << endl;
    resumen << "Estado de la misión: COMPLETADA" << endl;

    if (recorrido[recorrido.size() - 1] == tierra)
    {
        resumen << "Regreso a la Tierra: SI" << endl;
    }
    else
    {
        resumen << "Regreso a Tierra: No" << endl;
    }

    resumen.close();

    cout << "Combustible total: " << combustibleTotal << endl;
    cout << "Archivo detalle_recorrido.txt generado" << endl;
    cout << "Archivo resumen.txt generado" << endl;

    return 0;
}