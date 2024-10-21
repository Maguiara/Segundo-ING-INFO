// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 6: Diseño e implementación de un simulador de autómatas finitos
// Autor: Daniel Martínez Sopo
// Correo: alu0101675893@ull.edu.es
// Fecha: 19/10/2024
// Archivo p06_automata_simulator.cc: 
// Contiene la función main del proyecto que usa un objeto Automaton que emplea dos archivos de entrada 
// dados por el usuario para simular un NFA o un DFA y pasar por pantalla su veredicto para ciertas cadenas.
// Historial de revisiones
// 19/10/2024 - Creación (primera versión) del código
#include <iostream>
#include "Automaton.h"
#include "tools.h"

/**
 * @brief Main function of the program, calls the Usage function and the client function.
 * @param argc Number of command line arguments.
 * @param argv Array of pointers to strings that contains
 *             the command line arguments.
 */
int main(int argc, char* argv[]){
  Usage(argc, argv);
  Automaton example(argv[1]);
  example.check_string(argv[2]);
}