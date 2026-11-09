#include <iostream>
#include "../Grafo.h"

using namespace std;

int main()
{
    Grafo grafo;

    Planeta tierra = {"Tierra", 0, 0, 0, 1};
    Planeta miller = {"Miller", 2, 0, 0, 1};
    Planeta mann = {"Mann", 5, 0, 0, 1};
    Planeta edmunds = {"Edmunds", 9, 0, 0, 1};

    // agregamos los planetas de la primera prueba
    grafo.agregarPlaneta(tierra);
    grafo.agregarPlaneta(miller);
    grafo.agregarPlaneta(mann);
    grafo.agregarPlaneta(edmunds);

    cout << "Cantidad de planetas: "
         << grafo.cantidadPlanetas() << endl;

    cout << "Posicion de Mann: "
         << grafo.buscarPlaneta("Mann") << endl;

    // registramos el combustible entre tierra y miller
    // y verificamos que se guarde en ambos sentidos
    grafo.establecerPeso(0, 1, 2);

    cout << "Tierra a Miller: "
         << grafo.obtenerPeso(0, 1) << endl;

    cout << "Miller a Tierra: "
         << grafo.obtenerPeso(1, 0) << endl;

    // marcamos una conexion peligrosa para comprobar
    // que tambien quede registrada en ambos sentidos
    grafo.marcarPeligrosa(1, 2);

    cout << "Miller a Mann es peligrosa: "
         << grafo.esPeligrosa(1, 2) << endl;

    cout << "Mann a Miller es peligrosa: "
         << grafo.esPeligrosa(2, 1) << endl;

    cout << "Tierra a Edmunds es peligrosa: "
         << grafo.esPeligrosa(0, 3) << endl;

    // comprobamos que no se puedan agregar planetas
    // con nombres repetidos o factores temporales invalidos
    Planeta repetido = {"Mann", 8, 0, 0, 1};
    Planeta factorInvalido = {"Nuevo", 10, 0, 0, 0};

    cout << "Agregar planeta repetido: "
         << grafo.agregarPlaneta(repetido) << endl;

    cout << "Agregar factor temporal invalido: "
         << grafo.agregarPlaneta(factorInvalido) << endl;

    cout << "Cantidad final de planetas: "
         << grafo.cantidadPlanetas() << endl;
    return 0;
}