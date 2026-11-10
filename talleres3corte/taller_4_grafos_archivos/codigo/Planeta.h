#ifndef PLANETA_H
#define PLANETA_H

#include <string>

class Planeta
{
private:
    std::string nombre;
    double x;
    double y;
    double z;
    double factorTemporal;

public:
    Planeta();

    std::string obtenerNombre() const;
    double obtenerX() const;
    double obtenerY() const;
    double obtenerZ() const;
    double obtenerFactorTemporal() const;

    void asignarNombre(const std::string& nuevoNombre);
    void asignarCoordenadas(double nuevaX, double nuevaY, double nuevaZ);
    void asignarFactorTemporal(double nuevoFactorTemporal);
};

#endif
