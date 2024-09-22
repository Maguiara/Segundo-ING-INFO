 // Universidad de La Laguna
 // Escuela Superior de Ingeniería y Tecnología
 // Grado en Ingeniería Informática
 // Asignatura: Computabilidad y Algoritmia
 // Curso: 2º
 // Práctica 2: Cadenas y lenguajes
 // Autor: Marco Aguiar Álvarez
 // Correo: alu0101620961@ull.edu.es
 // Fecha: 19/09/2024
 // Archivo tools.cc: programa de herramientas.
 // Contiene la definicion de las funciones herramienta contenidas en el programa
 // para indicar al usuario el correcto funcionamiento del codigo
 // Historial de revisiones
 // 17/09/2024- Creación (primera versión) del código
#include "tools.h"


int main (int argc, char* argv[]) {
  Usage(argc, argv);
  std::ifstream input_file{argv[1]}; 
  std::ofstream output_file{argv[2]};
  int opcode{std::stoi(argv[3])};
  Operations(input_file, output_file, opcode);
  
} 