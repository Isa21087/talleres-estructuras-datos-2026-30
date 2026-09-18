#include <cstdlib>  // Para std::atoi
#include <iostream> // Para entrada/salida estándar
#include <chrono>   // Para medición de tiempo

#include "suma_functions.h" // Declaraciones de las funciones suma_recursive, suma_iterative, suma_constant

// -------------------------------------------------------------------------
// Función principal del programa
// Este programa compara tres versiones del algoritmo para sumar múltiplos de k hasta n:
// - versión recursiva
// - versión iterativa
// - versión con fórmula (tiempo constante)
// Además de calcular los resultados, mide cuánto tiempo tarda cada versión.

// test_suma.cxx prueba las tres versiones del algoritmo que calcula la suma de los múltiplos de k menores o iguales a n.
//  -------------------------------------------------------------------------
int main(int argc, char *argv[]) /*Esto significa que el programa recibe datos desde la terminal.

argc indica cuántos elementos se escribieron en el comando.
argv guarda esos elementos como textos.
argv[0] es el nombre del ejecutable.
argv[1] es el primer dato escrito.
argv[2] es el segundo dato escrito.*/
{
  // Validación de argumentos de línea de comandos.
  // Se espera que el usuario ingrese dos números: n (límite superior) y k (múltiplo base)
  if (argc < 3) // ¿El número de elementos (argc) es menor a 3? si es 3 se salta el if porque es falso decir que 3 es menor a 3y se ejecuta el programa, si es menor a 3 se ejecuta el if y se muestra el mensaje de error.
  {
    std::cerr
        << "Uso: " << argv[0]
        << " <n> <k>" << std::endl;
    return -1;
  }

  // Conversión de argumentos de tipo texto (char*) a tipo numérico (unsigned short)
  // Se utiliza este tipo para forzar el análisis de límites y posibles errores por desbordamiento
  // Aquí n es el límite superior y k es el número cuyos múltiplos se van a sumar. El programa exige recibir ambos valores y comprueba que sean mayores que cero. POSITIVOS
  unsigned int n = static_cast<unsigned int>(std::atoi(argv[1]));
  unsigned int k = static_cast<unsigned int>(std::atoi(argv[2]));

  // Validación semántica: n y k deben ser mayores que cero si es igual a cero se muestra un mensaje de error y el programa termina con código -1.
  if (n == 0 || k == 0)
  {
    std::cerr << "Error: n y k deben ser mayores que cero." << std::endl;
    return -1;
  }

  // ---------------------------------------------------------------
  // Cálculo usando la versión RECURSIVA del algoritmo
  // Se mide el tiempo de ejecución usando std::chrono y system_clock
  // Nota: en algunos sistemas operativos (especialmente Windows),
  // los resultados pueden ser cero si la resolución del reloj no es suficiente
  // ---------------------------------------------------------------
  long start_recursive =
      std::chrono::duration_cast<std::chrono::nanoseconds>(
          std::chrono::system_clock::now().time_since_epoch())
          .count();

  double result_recursive = suma_recursive(n, k); // utiliza recursion

  long end_recursive =
      std::chrono::duration_cast<std::chrono::nanoseconds>(
          std::chrono::system_clock::now().time_since_epoch())
          .count();

  long time_recursive = end_recursive - start_recursive;

  // ---------------------------------------------------------------
  // Cálculo usando la versión ITERATIVA del algoritmo
  // ---------------------------------------------------------------
  long start_iterative =
      std::chrono::duration_cast<std::chrono::nanoseconds>(
          std::chrono::system_clock::now().time_since_epoch())
          .count();

  double result_iterative = suma_iterative(n, k); // utiliza iteracion o sea unciclo

  long end_iterative =
      std::chrono::duration_cast<std::chrono::nanoseconds>(
          std::chrono::system_clock::now().time_since_epoch())
          .count();

  long time_iterative = end_iterative - start_iterative;

  // ---------------------------------------------------------------
  // Cálculo usando la versión en TIEMPO CONSTANTE (fórmula matemática)
  // ---------------------------------------------------------------
  long start_constant =
      std::chrono::duration_cast<std::chrono::nanoseconds>(
          std::chrono::system_clock::now().time_since_epoch())
          .count();

  double result_constant = suma_constant(n, k); // utiliza una formula matematica para calcular la suma de los múltiplos de k menores o iguales a n.

  long end_constant =
      std::chrono::duration_cast<std::chrono::nanoseconds>(
          std::chrono::system_clock::now().time_since_epoch())
          .count();

  long time_constant = end_constant - start_constant;

  // ---------------------------------------------------------------
  // Mostrar resultados en formato CSV para facilitar su análisis posterior
  // Formato:
  // n;k;resultado_recursivo;resultado_iterativo;resultado_formula;
  //     tiempo_recursivo;tiempo_iterativo;tiempo_formula;
  // Este formato permite copiar los resultados fácilmente a Excel o herramientas de graficación
  // ---------------------------------------------------------------
  std::cout
      << n << ";" << k << ";"
      << result_recursive << ";" << result_iterative << ";" << result_constant << ";"
      << time_recursive << ";" << time_iterative << ";" << time_constant << ";"
      << std::endl;

  return 0;
}

// eof - test_main.cxx
