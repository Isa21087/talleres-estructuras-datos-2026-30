/*
  es un programa creado para probar otras funciones.  
---------------------------------------------------------------------------
  Nombre del archivo: test_inverse.cxx

  Descripción:
  Este programa compara el desempeño de tres algoritmos de ordenamiento
  (Bubblesort, Quicksort y Heapsort) sobre un arreglo de números enteros
  ordenado de forma inversa. Para cada algoritmo:
    - Se mide el tiempo de ejecución (en milisegundos).
    - Se verifica que el arreglo resultante esté correctamente ordenado.
    - Se imprimen los resultados en formato CSV.

  Uso desde consola:
    ./test_inverse <count>

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
  long* a_bubble = new long[count]; //a_bubble contiene los datos que Bubblesort debe ordenar, mientras que count indica cuántos datos hay en ese arreglo.
  long* a_quick = new long[count];
  long* a_heap = new long[count];

  // La idea de count - c es ir produciendo números cada vez más pequeños.Llenar los tres arreglos con los mismos valores en orden inverso
  for (long c = 0; c < count; ++c)
  {
    a_bubble[c] = count - c; //queda [5, 4, 3, 2, 1] si count = 5.
    a_quick[c] = count - c;
    a_heap[c] = count - c;
  } // rof

  //El nombre inverse se refiere a cómo llega inicialmente el arreglo, no a cómo debe quedar al final. 

  // --- Medición de Bubblesort
  long start_bubble =
    std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::system_clock::now().time_since_epoch() //obtiene la hora actual del sistema.calcula cuánto tiempo ha pasado desde el punto inicial usado por el reloj del sistema.
    ).count();// extrae únicamente el valor numérico.count() es una función de chrono, no es la variable anterior. Esa función extrae el valor numérico del tiempo medido. y todo eso se guarda en start_bubble.
  bubblesort(a_bubble, count); //a_bubble es el arreglo que se quiere ordenar.Bubblesort modifica directamente a_bubble y deja sus elementos ordenados.
  
  //Esta parte hace exactamente lo mismo que la primera, pero ahora guarda el instante después de que Bubblesort terminó:
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
  quicksort(a_quick, count);// quicsksort ordena el arreglo a_quick y lo deja ordenado.
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
  heapsort(a_heap, count); // heapsort ordena el arreglo a_heap y lo deja ordenado.
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

// eof - test_inverse.cxx
