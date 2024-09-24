/**
 * @file tools.h
 * @brief Programa de herramientas.
 * Contiene la declaración de las funciones herramienta contenidas en el programa
 * para indicar al usuario el correcto funcionamiento del código.
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




#ifndef TOOLS_H
#define TOOLS_H

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <cstdlib>

 void usage(int argc, char* argv[]);
 void errorMessage(char* argv[]);
 void checkFiles(char* argv[]);
 void checkHelp( char* argv[]);
 void checkOpcode(char* argv[]);
 void operations(std::ifstream& input_file, std::ofstream& output_file, const int opcode);

#endif