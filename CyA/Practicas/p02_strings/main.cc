/**
 * @file main.cc
 * @brief Función principal del programa.
 * Contiene la función principal que procesa los argumentos de línea de comandos,
 * abre los archivos de entrada y salida, y ejecuta las operaciones correspondientes
 * según el código de operación proporcionado.
 * 
 * @details
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Computabilidad y Algoritmia
 * Curso: 2º
 * Práctica 2: Cadenas y lenguajes
 * 
 * @author Marco Aguiar Álvarez
 * @date 19/09/2024
 * @note Correo: alu0101620961@ull.edu.es
 */

#include "tools.h"


/**
 * @brief Función principal del programa.
 *
 * Esta función se encarga de procesar los argumentos de línea de comandos,
 * abrir los archivos de entrada y salida, y ejecutar las operaciones
 * correspondientes según el código de operación proporcionado.
 *
 * @param argc Número de argumentos de línea de comandos.
 * @param argv Array que contiene los argumentos de línea de comandos.
 *             - argv[1]: Ruta del archivo de entrada.
 *             - argv[2]: Ruta del archivo de salida.
 *             - argv[3]: Código de operación a realizar (convertido a entero).
 */
int main (int argc, char* argv[]) {
  usage(argc, argv);
  std::ifstream input_file{argv[1]}; 
  std::ofstream output_file{argv[2]};
  int opcode{std::stoi(argv[3])};
  operations(input_file, output_file, opcode);
  return 0;
} 