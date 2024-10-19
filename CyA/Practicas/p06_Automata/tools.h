/**
 * @file tools.h
 * @brief Declaración de funciones para herramientas de análisis de código.
 * Contiene la declaración de funciones para manejar argumentos y archivos.
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

#ifndef TOOLS_H
#define TOOLS_H

#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

void usage (int argc, char* argv[]);
void argumentFail(char* argv[]);
void checkHelp(char* argv[]);
void checkFiles(char* argv[]);

#endif 