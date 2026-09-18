#include <algorithm>           // Para make_heap y sort_heap
#include "sort_functions.h"    // Declaraciones de las funciones

//todos ordenan de menor a mayor 
// -------------------------------------------------------------------------
// Implementación del algoritmo Bubblesort.
// Recorre el arreglo varias veces comparando pares adyacentes.
// Si los elementos están fuera de orden, los intercambia.
// -------------------------------------------------------------------------
void bubblesort(long* a, long n) 
{
  for (unsigned long j = 0; j < n; ++j)
  {
    for (unsigned long i = 0; i < n - 1; ++i)
    {
      if (a[i] > a[i + 1])
      {
        long tmp = a[i];
        a[i] = a[i + 1];
        a[i + 1] = tmp;
      } // fi
    } // rof
  } // rof
}

// -------------------------------------------------------------------------
// Función auxiliar para particionar el arreglo en Quicksort.
// Elige el último elemento como pivote y reorganiza los elementos de modo
// que los menores o iguales al pivote queden a su izquierda, y los mayores a la derecha.
// Retorna la posición final del pivote.
// -------------------------------------------------------------------------
long quicksort_partition(long* a, long p, long r)
{
  long x = a[r];     // Pivote //toma como pivote el último elemento del arreglo
  long j = p - 1;    // Índice del último elemento menor o igual al pivote

  for (long i = p; i < r; i++)
  {
    if (x >= a[i])
    {
      j = j + 1;

      // Intercambiar a[i] con a[j]
      long temp = a[j];
      a[j] = a[i];
      a[i] = temp;
    } // fi
  } // rof

  // Colocar el pivote en su posición final
  a[r] = a[j + 1];
  a[j + 1] = x;

  return (j + 1);
}

// -------------------------------------------------------------------------
// Función recursiva auxiliar para quicksort.
// Aplica recursivamente el algoritmo en los subarreglos izquierdo y derecho
// delimitados por el índice de partición.
// -------------------------------------------------------------------------
void quicksort_dummy(long* a, long p, long r)
{
  if (p < r)
  {
    long q = quicksort_partition(a, p, r);     // Partición
    quicksort_dummy(a, p, q - 1);              // Subarreglo izquierdo
    quicksort_dummy(a, q + 1, r);              // Subarreglo derecho
  } // fi
}

// -------------------------------------------------------------------------
// Función principal que invoca quicksort.
// Solo sirve como envoltorio para simplificar el llamado desde main.
// -------------------------------------------------------------------------
void quicksort(long* a, long n)
{
  quicksort_dummy(a, 0, n - 1);
}

// -------------------------------------------------------------------------
// Implementación de Heapsort utilizando funciones de la STL.
// make_heap construye un heap (montículo máximo).
// sort_heap ordena el arreglo a partir del heap generado.
// -------------------------------------------------------------------------
void heapsort(long* a, long n)
{
  std::make_heap(a, a + n);    // Construye el heap
  std::sort_heap(a, a + n);    // Ordena el arreglo a partir del heap
}

// eof - sort_functions.cxx
