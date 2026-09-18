/*
  ---------------------------------------------------------------------------
  Nombre del archivo: test_sorted.cxx

  Descripción:
  Este programa compara el desempeño de tres algoritmos de ordenamiento
  (Bubblesort, Quicksort y Heapsort) sobre un arreglo que ya está
  previamente ordenado de forma creciente. Para cada algoritmo:
    - Se mide el tiempo de ejecución (en milisegundos).
    - Se verifica que el arreglo resultante esté correctamente ordenado.
    - Se imprimen los resultados en formato CSV.

  Uso desde consola:
    ./test_sorted <count>

  Donde:
    <count> es el tamaño del arreglo a ordenar.

  Salida:
    count; is_sorted_bubble; is_sorted_quick; is_sorted_heap; time_bubble; time_quick; time_heap

  ---------------------------------------------------------------------------
*/

#include <cstdlib>
#include <iostream>
#include <chrono>

#include "sort_functions.h"

// -------------------------------------------------------------------------
int main(int argc, char* argv[])
{
  // Obtener argumento desde la línea de comandos
  if (argc < 2)
  {
    std::cerr
      << "Usage: " << argv[0]
      << " count" << std::endl;
    return (-1);
  } // fi

  long count = std::atoi(argv[1]);

  // Reservar memoria para tres copias del arreglo
  long* a_bubble = new long[count];
  long* a_quick = new long[count];
  long* a_heap = new long[count];

  // Llenar los arreglos con valores ya ordenados crecientemente comenzando desde cero. mientras c sea menor que count. Si count = 5, las posiciones válidas son: 0, 1, 2, 3 y 4
  for (long c = 0; c < count; ++c)
  {
    a_bubble[c] = c;
    a_quick[c] = c;
    a_heap[c] = c;
  } // rof

  // --- Medición de Bubblesort
  long start_bubble =
    std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::system_clock::now().time_since_epoch()
    ).count();
  bubblesort(a_bubble, count);
  long end_bubble =
    std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::system_clock::now().time_since_epoch()
    ).count();
  long time_bubble = end_bubble - start_bubble;

  // --- Medición de Quicksort
  long start_quick =
    std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::system_clock::now().time_since_epoch()
    ).count();
  quicksort(a_quick, count);
  long end_quick =
    std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::system_clock::now().time_since_epoch()
    ).count();
  long time_quick = end_quick - start_quick;

  // --- Medición de Heapsort
  long start_heap =
    std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::system_clock::now().time_since_epoch()
    ).count();
  heapsort(a_heap, count);
  long end_heap =
    std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::system_clock::now().time_since_epoch()
    ).count();
  long time_heap = end_heap - start_heap;

  // Imprimir resultados en formato CSV:
  // count; is_sorted_bubble; is_sorted_quick; is_sorted_heap; time_bubble; time_quick; time_heap
  std::cout
    << count << ";"
    << is_sorted(a_bubble, a_bubble + count) << ";"
    << is_sorted(a_quick, a_quick + count) << ";"
    << is_sorted(a_heap, a_heap + count) << ";"
    << time_bubble << ";"
    << time_quick << ";"
    << time_heap << std::endl;

  // Liberar memoria
  delete[] a_bubble;
  delete[] a_quick;
  delete[] a_heap;

  return (0);
}

// eof - test_sorted.cxx
