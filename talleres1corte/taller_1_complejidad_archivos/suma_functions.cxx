#include "suma_functions.h"
#include <iostream>     // Para entrada/salida estándar


// -------------------------------------------------------------------------
// Versión iterativa del algoritmo
// Recorre todos los enteros entre 1 y n
// Si un número es divisible entre k, se suma al total acumulado
// -------------------------------------------------------------------------
//double suma_iterative(unsigned short n, unsigned short k) {
double suma_iterative(unsigned int n, unsigned int k) {
    //ANTES int suma = 0;
    unsigned long long suma = 0;                   // 1

    for (unsigned int i = 1; i <= n; i++)          // 1 + (n+1) + n
    {
        if (i % k == 0)                            // 2*n
        {
            suma += i;                             // 2*n
        }
    }

    return suma;                                   // 1
}
//T(n) = 1 + [1 + (n+1) + n] + 2n + 2n + 1


// -------------------------------------------------------------------------
// Versión recursiva del algoritmo
// Caso base: si n == 0, retorna 0
// Paso recursivo: si n es múltiplo de k, se suma n + suma(n-1, k)
// Si no, se descarta n y se analiza el anterior
// -------------------------------------------------------------------------
// ANTES double suma_recursive(unsigned short n, unsigned short k) {
double suma_recursive(unsigned int n, unsigned int k) {

    if (n == 0) {                                  // 1
        return 0;                                  // 1
    }

    if (n % k == 0) {                              // 2
        return n + suma_recursive(n - 1, k);       // 2 + T(n-1)
    }
    else {
        return suma_recursive(n - 1, k);           // 1 + T(n-1)
    }
}
//T(n) = 1 + 2 + 2 + T(n-1)
//T(n) = 5 + T(n-1)

// -------------------------------------------------------------------------
// Versión en tiempo constante (fórmula matemática)
// Esta función debe ser implementada por el estudiante.
// Se espera que utilice una fórmula cerrada basada en progresiones aritméticas
// para calcular directamente la suma de los múltiplos de k hasta n.
// No utilice bucles ni recursión.
// -------------------------------------------------------------------------
//ANTES double suma_constant(unsigned short n, unsigned short k) {
double suma_constant(unsigned int n, unsigned int k) {
    // TODO #01: Implementar esta función utilizando una fórmula matemática
    // para calcular directamente la suma de los múltiplos de k menores o iguales a n.
    unsigned long long m = n / k;                  // 2

    return k * m * (m + 1) / 2;                    // 5
}
//T(n) = 2 + 5
//T(n) = 7
//T(n) = O(1)
// eof - suma_functions.cxx
