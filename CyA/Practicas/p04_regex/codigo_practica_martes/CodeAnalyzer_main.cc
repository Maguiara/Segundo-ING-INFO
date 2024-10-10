/**
 * @file CodeAnalyzer_main.cc
 * @brief Implementación del archivo principal para el analizador de código.
 * Contiene la función principal que utiliza la clase CodeAnalyzer para analizar
 * archivos de código.
 * 
 * @details
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Computabilidad y Algoritmia
 * Curso: 2º
 * Práctica 4: Análisis de código con expresiones regulares
 * 
 * @date 19/09/2024
 * @note Correo: alu0101620961@ull.edu.es
 */


#include "CodeAnalyzer_practica.h"
#include "tools.h"

/**
 * @brief Punto de entrada del analizador de código.
 *
 * Inicializa CodeAnalyzer y analiza los archivos de entrada proporcionados.
 *
 * @param argc Número de argumentos de la línea de comandos.
 * @param argv Array de argumentos de la línea de comandos. El primer argumento debe ser la ruta del archivo de entrada,
 *             y el segundo argumento debe ser la ruta del archivo de salida.
 */

int main(int argc, char* argv[]) {
    usage(argc, argv);
    CodeAnalyzer analyzer;
    analyzer.Analyze(argv[1], argv[2]);
}

