#include "SistemaExploracionLazaro.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

SistemaExploracionLazaro::SistemaExploracionLazaro()
{
    // iniciamos estos valores en cero porque todavia no hemos
    // leido el archivo ni calculado el combustible de la mision
    k = 0;
    lambda = 0;
    combustibleTotal = 0;
}

bool SistemaExploracionLazaro::cargarPlanetas(const string &nombreArchivo)
{
    ifstream archivo(nombreArchivo);

    // si el archivo no existe o no se puede abrir
    // no podemos construir el grafo de la mision
    if (!archivo.is_open())
    {
        cout << "No se pudo abrir el archivo" << endl;
        return false;
    }

    int cantidadPlanetas;

    archivo >> k >> lambda;
    archivo >> cantidadPlanetas;

    // k debe ser positivo y lambda no puede ser negativa
    // tambien necesitamos al menos un planeta para iniciar la exploracion
    if (!archivo || cantidadPlanetas <= 0 || k <= 0 || lambda < 0)
    {
        cout << "Los datos iniciales del archivo no son validos" << endl;
        return false;
    }

    // guardamos temporalmente los nombres de las conexiones peligrosas
    // porque al leer un planeta todavia pueden faltar otros por registrar
    // entonces primero cargamos todos y despues verificamos sus conexiones
    vector<vector<string>> conexionesPeligrosas;

    for (int i = 0; i < cantidadPlanetas; i++)
    {
        Planeta planeta;
        int cantidadPeligrosas;

        string nombre;
        double x, y, z, factorTemporal;

        archivo >> nombre >> x >> y >> z >> factorTemporal >> cantidadPeligrosas;

        if (!archivo || cantidadPeligrosas < 0)
        {
            cout << "Error al leer los datos de un planeta" << endl;
            return false;
        }

        // usamos las operaciones del TAD Planeta para guardar sus datos
        // asi el sistema no necesita acceder directamente a sus atributos
        planeta.asignarNombre(nombre);
        planeta.asignarCoordenadas(x, y, z);
        planeta.asignarFactorTemporal(factorTemporal);

        // el grafo comprueba que el nombre no este vacio ni repetido
        // y que el factor temporal del planeta sea positivo
        if (!grafo.agregarPlaneta(planeta))
        {
            cout << "Datos invalidos del planeta: "
                 << planeta.obtenerNombre() << endl;
            return false;
        }

        vector<string> destinos;

        // por ahora solo guardamos los nombres de los destinos
        // todavia no marcamos nada porque puede que esos planetas
        // aparezcan mas adelante en el archivo
        for (int j = 0; j < cantidadPeligrosas; j++)
        {
            string destino;
            archivo >> destino;

            if (!archivo)
            {
                cout << "Error al leer una conexion peligrosa" << endl;
                return false;
            }

            destinos.push_back(destino);
        }

        // cada posicion corresponde a las conexiones peligrosas
        // del planeta que acabamos de agregar al grafo
        conexionesPeligrosas.push_back(destinos);
    }

    archivo.close();

    // ahora que conocemos todos los planetas podemos revisar
    // si las conexiones peligrosas del archivo tienen sentido
    for (int i = 0; i < grafo.cantidadPlanetas(); i++)
    {
        for (int j = 0; j < (int)conexionesPeligrosas[i].size(); j++)
        {
            string nombreDestino = conexionesPeligrosas[i][j];
            int destino = grafo.buscarPlaneta(nombreDestino);

            // no podemos tener una conexion hacia un planeta inexistente
            // ni una conexion peligrosa de un planeta consigo mismo
            if (destino == -1 || destino == i)
            {
                cout << "Conexion peligrosa invalida desde "
                     << grafo.obtenerPlaneta(i).obtenerNombre()
                     << " hacia " << nombreDestino << endl;
                return false;
            }

            // revisamos los destinos anteriores del mismo planeta
            // para evitar que una conexion peligrosa aparezca repetida
            for (int p = 0; p < j; p++)
            {
                if (conexionesPeligrosas[i][p] == nombreDestino)
                {
                    cout << "Conexion peligrosa repetida desde "
                         << grafo.obtenerPlaneta(i).obtenerNombre()
                         << " hacia " << nombreDestino << endl;
                    return false;
                }
            }

            // las conexiones son bidireccionales
            // si A indica que B es peligroso, B tambien debe indicar
            // que A es peligroso en sus datos del archivo
            bool encontrada = false;

            for (int p = 0; p < (int)conexionesPeligrosas[destino].size(); p++)
            {
                if (conexionesPeligrosas[destino][p] ==
                    grafo.obtenerPlaneta(i).obtenerNombre())
                {
                    encontrada = true;
                }
            }

            if (!encontrada)
            {
                cout << "La conexion peligrosa no aparece "
                     << "en ambos sentidos" << endl;
                return false;
            }
        }
    }

    // despues de comprobar que todas las conexiones son validas
    // las registramos en la matriz de booleanos del grafo
    // marcarPeligrosa ya se encarga de hacerlo en ambos sentidos
    for (int i = 0; i < grafo.cantidadPlanetas(); i++)
    {
        for (int j = 0; j < (int)conexionesPeligrosas[i].size(); j++)
        {
            int destino = grafo.buscarPlaneta(conexionesPeligrosas[i][j]);
            grafo.marcarPeligrosa(i, destino);
        }
    }

    cout << "Conexiones peligrosas verificadas" << endl;

    return true;
}

void SistemaExploracionLazaro::calcularCombustible()
{
    // calculamos el combustible necesario para viajar entre cada par de planetas
    // solo recorremos la parte superior de la matriz porque las conexiones
    // son bidireccionales y Grafo ya guarda el mismo peso en ambos sentidos
    for (int i = 0; i < grafo.cantidadPlanetas(); i++)
    {
        for (int j = i + 1; j < grafo.cantidadPlanetas(); j++)
        {
            Planeta origen = grafo.obtenerPlaneta(i);
            Planeta destino = grafo.obtenerPlaneta(j);

            double diferenciaX = origen.obtenerX() - destino.obtenerX();
            double diferenciaY = origen.obtenerY() - destino.obtenerY();
            double diferenciaZ = origen.obtenerZ() - destino.obtenerZ();

            // usamos la distancia euclidiana entre las coordenadas
            // para conocer la separacion espacial de los dos planetas
            double distancia = sqrt(
                diferenciaX * diferenciaX +
                diferenciaY * diferenciaY +
                diferenciaZ * diferenciaZ);

            // el factor gravitacional ajusta el combustible teniendo en cuenta
            // los factores temporales de ambos planetas y el valor de lambda
            double factor = 1 + lambda *
                                    ((origen.obtenerFactorTemporal() - 1) +
                                     (destino.obtenerFactorTemporal() - 1)) /
                                    2;

            double combustible = k * distancia * factor;

            // guardamos el resultado como peso de la conexion
            // y Grafo se encarga de registrarlo en las dos direcciones
            grafo.establecerPeso(i, j, combustible);
        }
    }

    cout << "Combustible de las conexiones calculado" << endl;

    // mostramos la matriz para comprobar que se calcularon
    // los pesos de todas las conexiones entre planetas
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
             << grafo.obtenerPlaneta(i).obtenerNombre() << endl;
    }
}

bool SistemaExploracionLazaro::realizarExploracion()
{
    // la mision siempre debe comenzar en Tierra
    // buscamos su posicion para saber desde donde iniciar el recorrido
    int tierra = grafo.buscarPlaneta("Tierra");

    if (tierra == -1)
    {
        cout << "No se encontro la Tierra" << endl;
        return false;
    }

    int cantidad = grafo.cantidadPlanetas();
    vector<int> visitados(cantidad, 0);

    int actual = tierra;

    // limpiamos los resultados por si se vuelve a ejecutar
    // la exploracion sobre el mismo sistema
    recorrido.clear();
    combustibleTotal = 0;

    // empezamos en Tierra y la marcamos como visitada
    recorrido.push_back(grafo.obtenerPlaneta(tierra));
    visitados[tierra] = 1;

    cout << endl
         << "Recorrido de la nave" << endl;

    // visitamos los demas planetas sin contar Tierra
    // porque ya es nuestro punto de partida
    for (int paso = 1; paso < cantidad; paso++)
    {
        int elegido = -1;

        // primero intentamos encontrar una conexion segura
        // solo consideramos las peligrosas si no queda ninguna
        // conexion segura hacia un planeta sin visitar
        for (int tipo = 0; tipo < 2 && elegido == -1; tipo++)
        {
            for (int i = 0; i < cantidad; i++)
            {
                if (visitados[i] == 0 &&
                    grafo.esPeligrosa(actual, i) == tipo)
                {
                    // entre las conexiones del mismo tipo elegimos
                    // la que necesita menos combustible
                    if (elegido == -1 ||
                        grafo.obtenerPeso(actual, i) <
                            grafo.obtenerPeso(actual, elegido))
                    {
                        elegido = i;
                    }
                    else if (grafo.obtenerPeso(actual, i) ==
                                 grafo.obtenerPeso(actual, elegido) &&
                             grafo.obtenerPlaneta(i).obtenerNombre() <
                                 grafo.obtenerPlaneta(elegido).obtenerNombre())
                    {
                        // si hay empate en combustible usamos el nombre
                        // alfabeticamente menor para decidir el destino
                        elegido = i;
                    }
                }
            }
        }

        if (elegido == -1)
        {
            cout << "No se encontro otro planeta" << endl;
            return false;
        }

        double combustible = grafo.obtenerPeso(actual, elegido);
        bool peligrosa = grafo.esPeligrosa(actual, elegido);

        cout << grafo.obtenerPlaneta(actual).obtenerNombre()
             << " -> " << grafo.obtenerPlaneta(elegido).obtenerNombre()
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

        // guardamos el planeta elegido en el orden real de visita
        // este recorrido tambien nos servira despues para generar
        // los archivos de detalle y resumen de la mision
        recorrido.push_back(grafo.obtenerPlaneta(elegido));

        visitados[elegido] = 1;
        actual = elegido;
    }

    // al terminar las visitas regresamos directamente a Tierra
    // incluso si la conexion de regreso es peligrosa
    if (actual != tierra)
    {
        double combustibleRegreso = grafo.obtenerPeso(actual, tierra);
        bool peligrosa = grafo.esPeligrosa(actual, tierra);

        cout << grafo.obtenerPlaneta(actual).obtenerNombre()
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

        // agregamos Tierra al final para registrar el regreso
        // como un desplazamiento mas del recorrido
        recorrido.push_back(grafo.obtenerPlaneta(tierra));
    }

    return true;
}

bool SistemaExploracionLazaro::generarDetalle()
{
    // necesitamos haber realizado la exploracion para poder
    // generar el detalle de los desplazamientos de la nave
    if (recorrido.empty())
    {
        cout << "No hay un recorrido para generar el detalle" << endl;
        return false;
    }

    ofstream detalle("detalle_recorrido.txt");

    if (!detalle.is_open())
    {
        cout << "No se pudo crear el archivo de detalle" << endl;
        return false;
    }

    // conservamos dos decimales en las distancias y el combustible
    // para mantener el formato que usamos en las pruebas anteriores
    detalle.setf(ios::fixed);
    detalle.precision(2);

    detalle << "MISIÓN LÁZARO - DETALLE DEL RECORRIDO" << endl;

    double combustibleAcumulado = 0;

    // el primer planeta del recorrido es Tierra
    // por eso comenzamos en la posicion 1 y usamos el anterior
    // como origen de cada desplazamiento
    for (int i = 1; i < (int)recorrido.size(); i++)
    {
        Planeta origen = recorrido[i - 1];
        Planeta destino = recorrido[i];

        double diferenciaX = origen.obtenerX() - destino.obtenerX();
        double diferenciaY = origen.obtenerY() - destino.obtenerY();
        double diferenciaZ = origen.obtenerZ() - destino.obtenerZ();

        // calculamos nuevamente la distancia para incluirla en el detalle
        // el peso del grafo representa combustible, no distancia
        double distancia = sqrt(
            diferenciaX * diferenciaX +
            diferenciaY * diferenciaY +
            diferenciaZ * diferenciaZ);

        // usamos la misma formula aplicada al construir los pesos
        // asi podemos mostrar el factor gravitacional de cada viaje
        double factor = 1 + lambda *
                                ((origen.obtenerFactorTemporal() - 1) +
                                 (destino.obtenerFactorTemporal() - 1)) /
                                2;

        int indiceOrigen = grafo.buscarPlaneta(origen.obtenerNombre());
        int indiceDestino = grafo.buscarPlaneta(destino.obtenerNombre());

        // recuperamos el combustible que ya habiamos calculado
        // y verificamos si esta conexion se marco como peligrosa
        double combustible = grafo.obtenerPeso(indiceOrigen, indiceDestino);
        bool peligrosa = grafo.esPeligrosa(indiceOrigen, indiceDestino);

        combustibleAcumulado += combustible;

        // registramos cada desplazamiento en el mismo orden
        // en que la nave visito los planetas
        detalle << endl;
        detalle << "Desplazamiento " << i << endl;
        detalle << "Origen: " << origen.obtenerNombre() << endl;
        detalle << "Destino: " << destino.obtenerNombre() << endl;
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
                << combustibleAcumulado << endl;
    }

    // comprobamos que no haya ocurrido un error al escribir
    // antes de informar que el archivo se genero correctamente
    detalle.close();

    if (!detalle)
    {
        cout << "Error al escribir el archivo de detalle" << endl;
        return false;
    }

    cout << "Archivo detalle_recorrido.txt generado" << endl;

    return true;
}

bool SistemaExploracionLazaro::generarResumen()
{
    // necesitamos tener el recorrido completo antes de generar
    // el resumen porque de ahi salen las estadisticas de la mision
    if (recorrido.empty())
    {
        cout << "No hay un recorrido para generar el resumen" << endl;
        return false;
    }

    ofstream resumen("resumen.txt");

    if (!resumen.is_open())
    {
        cout << "No se pudo crear el archivo de resumen" << endl;
        return false;
    }

    int cantidad = grafo.cantidadPlanetas();
    int desplazamientos = recorrido.size() - 1;

    double distanciaTotal = 0;
    int conexionesSeguras = 0;
    int conexionesPeligrosasUsadas = 0;

    double mayorCombustible = 0;
    double menorCombustible = 0;

    string origenMayor;
    string destinoMayor;
    string origenMenor;
    string destinoMenor;

    // recorremos cada par de planetas consecutivos
    // para recuperar la distancia, el consumo y el tipo de conexion
    // tambien incluimos el regreso a Tierra como ultimo desplazamiento
    for (int i = 1; i < (int)recorrido.size(); i++)
    {
        Planeta origen = recorrido[i - 1];
        Planeta destino = recorrido[i];

        double diferenciaX = origen.obtenerX() - destino.obtenerX();
        double diferenciaY = origen.obtenerY() - destino.obtenerY();
        double diferenciaZ = origen.obtenerZ() - destino.obtenerZ();

        double distancia = sqrt(
            diferenciaX * diferenciaX +
            diferenciaY * diferenciaY +
            diferenciaZ * diferenciaZ);

        distanciaTotal += distancia;

        int indiceOrigen = grafo.buscarPlaneta(origen.obtenerNombre());
        int indiceDestino = grafo.buscarPlaneta(destino.obtenerNombre());

        double combustible = grafo.obtenerPeso(indiceOrigen, indiceDestino);
        bool peligrosa = grafo.esPeligrosa(indiceOrigen, indiceDestino);

        if (peligrosa)
        {
            conexionesPeligrosasUsadas++;
        }
        else
        {
            conexionesSeguras++;
        }

        // guardamos los extremos de mayor y menor consumo
        // en el primer desplazamiento inicializamos ambos valores
        // y despues los actualizamos solamente si encontramos otro extremo
        if (i == 1 || combustible > mayorCombustible)
        {
            mayorCombustible = combustible;
            origenMayor = origen.obtenerNombre();
            destinoMayor = destino.obtenerNombre();
        }

        if (i == 1 || combustible < menorCombustible)
        {
            menorCombustible = combustible;
            origenMenor = origen.obtenerNombre();
            destinoMenor = destino.obtenerNombre();
        }
    }

    // usamos dos decimales para mantener el formato
    // de las salidas que ya habiamos comprobado
    resumen.setf(ios::fixed);
    resumen.precision(2);

    resumen << "MISIÓN LÁZARO - RESUMEN" << endl;
    resumen << endl;

    resumen << "Planetas registrados: " << cantidad << endl;
    resumen << "Planetas explorados: " << cantidad - 1 << endl;

    resumen << endl;
    resumen << "Recorrido:" << endl;

    for (int i = 0; i < (int)recorrido.size(); i++)
    {
        resumen << recorrido[i].obtenerNombre();

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

    // el ultimo planeta del recorrido debe ser Tierra
    // porque la nave tiene que regresar al punto de partida
    if (recorrido[recorrido.size() - 1].obtenerNombre() == "Tierra")
    {
        resumen << "Regreso a la Tierra: SI" << endl;
    }
    else
    {
        resumen << "Regreso a Tierra: No" << endl;
    }

    resumen.close();

    if (!resumen)
    {
        cout << "Error al escribir el archivo de resumen" << endl;
        return false;
    }

    cout << "Combustible total: " << combustibleTotal << endl;
    cout << "Archivo resumen.txt generado" << endl;

    return true;
}
