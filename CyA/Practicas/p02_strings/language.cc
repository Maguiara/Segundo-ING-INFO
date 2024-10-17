/**
 * @file language.cc
 * @brief Implementación de la clase Language y sus métodos.
 * Contiene la implementación de la clase Language, sus constructores, getters,
 * métodos y sobrecargas de operadores.
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
#include "language.h"


/**
 * @brief Genera todos los prefijos de una cadena dada y los inserta en el lenguaje.
 *
 * Esta función toma una cadena de entrada proporcionada por el usuario y genera todos sus prefijos posibles.
 * Cada prefijo generado se inserta en el conjunto de `my_language_`. Además, se inserta una cadena vacía representada
 * por el carácter '&'.
 *
 * @param user_string Objeto de tipo MyString que contiene la cadena de entrada del usuario.
 */
void Language::Prefix(MyString& user_string) {
  std::string current_prefix;
  for (int i{0}; i < user_string.getSize(); ++i) { 
    current_prefix  += user_string.my_string()[i];
    my_language_.insert(current_prefix);
  }
  MyString empty_string("&");
  my_language_.insert(empty_string);
}

/**
 * @brief Genera todos los sufijos posibles de una cadena y los inserta en el lenguaje.
 *
 * Esta función toma una cadena proporcionada por el usuario y genera todos los sufijos posibles
 * de dicha cadena. Cada sufijo generado se inserta en el conjunto de lenguaje de la clase.
 * Además, se inserta una cadena vacía representada por el carácter '&'.
 *
 * @param user_string Objeto de tipo MyString que contiene la cadena de la cual se generarán los sufijos.
 */
void Language::Sufix(MyString& user_string) {
  std::string current_sufix;
  for (int i = user_string.getSize() - 1; i >= 0; --i) { 
    current_sufix = user_string.my_string()[i] + current_sufix;
    my_language_.insert(current_sufix);
  }
  MyString empty_string("&");
  my_language_.insert(empty_string);
}


/**
 * @brief Sobrecarga del operador de inserción para la clase Language.
 *
 * Esta función permite imprimir un objeto de la clase Language en un flujo de salida.
 * El formato de salida es una lista de cadenas separadas por comas y encerradas entre llaves.
 *
 * @param out Flujo de salida donde se imprimirá el objeto Language.
 * @param user_language Objeto de la clase Language que se va a imprimir.
 * @return Referencia al flujo de salida modificado.
 */
std::ostream& operator<<(std::ostream& out, const Language& user_language) {
  out << "{";
  bool first = true;
  for (const auto& symbol: user_language.my_language_) {
    if(!first) {
      out << ", ";
    }
    out << symbol;
    first = false; 
  }
  out << "}";
  return out;
}