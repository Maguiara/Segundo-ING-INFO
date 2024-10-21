// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 6: Diseño e implementación de un simulador de autómatas finitos
// Autor: Daniel Martínez Sopo
// Correo: alu0101675893@ull.edu.es
// Fecha: 19/10/2024
// Archivo tools.cc: Contiene definiciones de funciones utilizadas en el programa.
// Historial de revisiones
// 19/10/2024 - Creación (primera versión) del código
#include "tools.h"

/**
 * @brief Validates command line arguments.
 * 
 * @param argc Number of command line arguments.
 * @param argv Array of pointers to character strings containing command line arguments.
 */
void Usage(int argc, char* argv[]){
  if (argc != 3) {
    (argc == 2) ? CheckHelp(argv) : ArgFail(argv);
  }  
  else CheckFiles(argv);
} 

/**
 * @brief Handles incorrect argument counts.
 * 
 * @param argv Array of pointers to character strings containing command line arguments.
 */
void ArgFail(char* argv[]) {
  std::cout << "Wrong argument, to get more information: " << argv[0] << " --help." << std::endl;
  exit(-1);
}

/**
 * @brief Checks for the help flag in command line arguments.
 * 
 * @param argv Array of pointers to character strings containing command line arguments.
 */
void CheckHelp(char* argv[]){
  std::string aux = argv[1];
  if (aux == "--help") Help();
  ArgFail(argv);
}

/**
 * @brief Checks if input and output files can be opened.
 * 
 * @param argv Array of pointers to character strings containing command line arguments.
 */
void CheckFiles(char* argv[]){
  std::ifstream input(argv[1]);
  std::ifstream output(argv[2]);
  if (!input || !output){
    std::cout << "Invalid text files, could not be opened." << std::endl;
    exit(-1);
  }
  input.close(); output.close();
}


/**
 * @brief Displays usage information for the program.
 */
void Help(){
  std::cout << "To ensure the effective execution of this program, the correct usage of the command line is as follows:\n" << 
  "Usage: [execution command] [automaton text file] [strings text file]\n" << 
  "The program will simulate an automatan wether NFA or DFA, it must be correctly defined in the .fa text file so the execution finds no problem" <<
  ". \nTo avoid trouble we suggest you check your text files before executing this simulator.\n \n" << 
  "Here is an example of how your .fa should look:\n\n" <<
  "0 1\n4\n0\n0 0 2 0 2 1 1\n1 1 2 0 1 1 1\n2 0 2 0 1 1 3\n3 0 2 0 2 1 3\n\n" <<
  "Also be sure to use one line only for each string you wanna check in your .txt !!!" << std::endl;
  exit(-1);
}