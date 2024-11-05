
/**
 * @file tools.h
 * @author Marco Aguiar Álvarez
 * @brief Archivo que contiene la declaracion de las funciones que velan por el buen uso del programa
 * @e alu0101620961@ull.edu.es
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef TOOLS_H
#define TOOLS_H

#include <utility>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <fstream>
#include <vector>
#include <string> 

void usage (int argc, char* argv[]);
void argumentFail(char* argv[]);
void checkHelp(char* argv[]);
void checkFiles(char* argv[]);

#endif 