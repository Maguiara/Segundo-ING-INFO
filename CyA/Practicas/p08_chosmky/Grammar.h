/**
 * @file Grammar.h
 * @brief Implementación de la clase Grammar para transformar gramáticas a la Forma Normal de Chomsky (CNF).
 * 
 * Este archivo contiene la implementación de la clase Grammar, que proporciona métodos para cargar información
 * de la gramática desde un archivo, transformar la gramática a la Forma Normal de Chomsky (CNF) y escribir la
 * gramática transformada en un archivo de salida.
 * 
 * La clase Grammar utiliza varias variables miembro privadas para almacenar los terminales, no terminales
 * y producciones de la gramática.
 * 
 * @note La implementación asume que el archivo de la gramática de entrada está correctamente formateado.
 * @note La implementación no maneja producciones unitarias ni producciones vacías.
 * 
 * @see Grammar.h
 * @see tools.h
 */


#include "tools.h"
#include "myAlphabet.h"

class Grammar {
  public:
  //Construcctor
  void LoadInformation(const std::string& input_file);
  //Metodos de la clase
  void Transform2CFN(const std::string& input_file, const std::string& output_file);
  char GenerateNonTerminal(const char c);
  bool ComprobarProduccion(const std::string& production);
  

  

 private:
 //Metodos que no han de ser accesibles
  void PrimeraParte();
  void SegundaParte();
  void Write(const std::string& output_file);
  bool CompararSalida(const std::string&, const std::string&);
  void ErrorExit(const int error_code);

  //Atributos privados de la clase
  int num_of_terminals_;
  std::set<char> terminals_;
  int num_of_non_terminals_;
  std::set<char> non_terminals_;
  int num_of_productions_;
  std::multimap<char, std::string> productions_;
  Alphabet valid_alphabet_;
};