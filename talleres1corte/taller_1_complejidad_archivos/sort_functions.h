#ifndef __SORT_FUNCTIONS__H__
#define __SORT_FUNCTIONS__H__

// -------------------------------------------------------------------------
// Ordena el arreglo 'a' de tamaño 'n' utilizando el algoritmo Bubblesort.
// Este algoritmo compara elementos adyacentes y los intercambia si están
// en orden incorrecto, repitiendo este proceso varias veces.
// -------------------------------------------------------------------------
void bubblesort(long* a, long n);

// -------------------------------------------------------------------------
// Ordena el arreglo 'a' de tamaño 'n' utilizando el algoritmo Quicksort.
// Quicksort selecciona un pivote y divide el arreglo en dos partes para
// aplicar recursivamente el mismo proceso.
// -------------------------------------------------------------------------
void quicksort(long* a, long n);

// -------------------------------------------------------------------------
// Ordena el arreglo 'a' de tamaño 'n' utilizando el algoritmo Heapsort.
// Heapsort convierte el arreglo en un heap (montículo) y luego extrae
// los elementos en orden para producir el arreglo ordenado.
// -------------------------------------------------------------------------
void heapsort(long* a, long n);

// -------------------------------------------------------------------------
// Verifica si el rango de elementos [first, last] está ordenado de forma creciente.
// Esta función es genérica y puede utilizarse con arreglos o estructuras iterables.
// Retorna true si el rango está ordenado, false en caso contrario.
// -------------------------------------------------------------------------
template<class I>
bool is_sorted(I first, I last);

#include "sort_functions.hxx"

#endif // __SORT_FUNCTIONS__H__

// eof - sort_functions.h
