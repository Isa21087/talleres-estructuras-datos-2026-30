
#include "Planeta.h"

Planeta::Planeta() {
    nombre = "";
    x = 0;
    y = 0;
    z = 0;
    factorTemporal = 1;
}

std::string Planeta::obtenerNombre() const {
    return nombre;
}

double Planeta::obtenerX() const {
    return x;
}

double Planeta::obtenerY() const {
    return y;
}

double Planeta::obtenerZ() const {
    return z;
}

double Planeta::obtenerFactorTemporal() const {
    return factorTemporal;
}

void Planeta::asignarNombre(const std::string& nuevoNombre) {
    nombre = nuevoNombre;
}

void Planeta::asignarCoordenadas(double nuevaX, double nuevaY, double nuevaZ) {
    x = nuevaX;
    y = nuevaY;
    z = nuevaZ;
}

void Planeta::asignarFactorTemporal(double nuevoFactorTemporal) {
    factorTemporal = nuevoFactorTemporal;
}
