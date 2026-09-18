#ifndef __SUMA_FUNCTIONS__H__
#define __SUMA_FUNCTIONS__H__

// -------------------------------------------------------------------------
// Calcula la suma de todos los números menores o iguales a 'n' que son múltiplos de 'k',
// utilizando un enfoque recursivo.
// Parámetros:
//   - n: límite superior de la secuencia (positivo)
//   - k: base de los múltiplos a sumar (positivo)
// Retorna:
//   - La suma total de los múltiplos de k entre 1 y n (inclusive)
// -------------------------------------------------------------------------
// ANTES double suma_recursive(unsigned short n, unsigned short k);
double suma_recursive(unsigned int n, unsigned int k);

// -------------------------------------------------------------------------
// Calcula la suma de los múltiplos de 'k' entre 1 y 'n',
// utilizando un enfoque iterativo mediante un ciclo.
// Parámetros:
//   - n: límite superior de la secuencia
//   - k: múltiplo base
// Retorna:
//   - La suma total acumulada de los múltiplos de k entre 1 y n
// -------------------------------------------------------------------------
//ANTES double suma_iterative(unsigned short n, unsigned short k);
double suma_iterative(unsigned int n, unsigned int k);
// -------------------------------------------------------------------------
// Calcula la suma de los múltiplos de 'k' entre 1 y 'n' utilizando una fórmula matemática.
// Esta función debe ser implementada por el estudiante sin utilizar bucles ni recursión.
// Parámetros:
//   - n: límite superior
//   - k: múltiplo base
// Retorna:
//   - Resultado del cálculo directo de la suma, si está correctamente implementado
// -------------------------------------------------------------------------
//ANTES double suma_constant(unsigned short n, unsigned short k);
double suma_constant(unsigned int n, unsigned int k);

#endif // __SUMA_FUNCTIONS__H__

// eof - suma_functions.h
