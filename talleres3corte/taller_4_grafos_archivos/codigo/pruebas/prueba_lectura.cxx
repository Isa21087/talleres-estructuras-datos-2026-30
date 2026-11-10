#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ifstream archivo("pruebas/prueba_03_peligros.txt");

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo" << endl;
        return 1;
    }

    double k, lambda;
    int cantidadPlanetas;

    archivo >> k >> lambda;
    archivo >> cantidadPlanetas;

    cout << "k: " << k << endl;
    cout << "lambda: " << lambda << endl;
    cout << "Cantidad de planetas: " << cantidadPlanetas << endl;

    for (int i = 0; i < cantidadPlanetas; i++) {
        string nombre;
        double x, y, z, factorTemporal;
        int cantidadPeligrosas;

        archivo >> nombre >> x >> y >> z;
        archivo >> factorTemporal >> cantidadPeligrosas;

        cout << endl << "Planeta: " << nombre << endl;
        cout << "Coordenadas: " << x << " " << y << " " << z << endl;
        cout << "Factor temporal: " << factorTemporal << endl;

        // leemos los nombres de las conexiones peligrosas
        // segun la cantidad que indica el archivo
        for (int j = 0; j < cantidadPeligrosas; j++) {
            string destino;
            archivo >> destino;

            cout << "Conexion peligrosa con: " << destino << endl;
        }
    }

    archivo.close();

    return 0;
}