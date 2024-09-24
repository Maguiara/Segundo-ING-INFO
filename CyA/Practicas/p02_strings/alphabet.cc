/**
 * @file alphabet.cc
 * @brief Implementación de la clase Alphabet y sus métodos.
 * Contiene la implementación de la clase Alphabet, sus constructores,
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
 * @date 19/09/2024
 * @note Correo: alu0101620961@ull.edu.es
 */

#include "tools.h" 
#include "alphabet.h"


/**
 * @brief Constructor de la clase Alphabet.
 *
 * Este constructor inicializa un objeto Alphabet utilizando un alfabeto proporcionado por el usuario.
 * Cada carácter del alfabeto del usuario se inserta en el conjunto `my_alphabet_`.
 *
 * @param user_alphabet Una cadena de simbolos que representa el alfabeto proporcionado por el usuario.
 */
Alphabet::Alphabet(const std::string& user_alphabet) {
  for (char c : user_alphabet) {
    my_alphabet_.insert(c);
  }
} 

/**
 * @brief Sobrecarga del operador de inserción para la clase Alphabet.
 *
 * Esta función permite imprimir un objeto de la clase Alphabet en un flujo de salida.
 * El alfabeto se imprime en formato de conjunto, es decir, los elementos están 
 * delimitados por llaves y separados por comas.
 *
 * @param out Flujo de salida donde se imprimirá el alfabeto.
 * @param user_alphabet Objeto de la clase Alphabet que se desea imprimir.
 * @return Referencia al flujo de salida modificado.
 */
std::ostream& operator<<(std::ostream& out, const Alphabet& user_alphabet) {
  out << "{"; 
  for (auto it = user_alphabet.my_alphabet_.begin(); it != user_alphabet.my_alphabet_.end(); ++it) {
    out << *it;
    if (std::next(it) != user_alphabet.my_alphabet_.end()) {
      out << ", ";  // Para añadir la coma entre los elementos
    }
  }
  out << "}";
  return out;
}

/**
 * @brief Sobrecarga del operador de extracción >> para la clase Alphabet.
 *
 * Esta función permite leer un alfabeto desde un flujo de entrada (std::istream).
 * El alfabeto se lee como una cadena de caracteres y se almacena en un conjunto (std::set)
 * dentro del objeto Alphabet proporcionado.
 *
 * @param in Flujo de entrada desde el cual se leerá el alfabeto.
 * @param user_alphabet Objeto de la clase Alphabet donde se almacenará el alfabeto leído.
 * @return Referencia al flujo de entrada modificado.
 */
std::istream& operator>>(std::istream& in, Alphabet& user_alphabet) {
  std::string user_input;
  in >> user_input; // Leemos el alfabeto como una string 
  user_alphabet.my_alphabet_.clear(); // Nos aseguramos de que el SET esta vacio
   for (char c : user_input) {
    user_alphabet.my_alphabet_.insert(c);
  }
  return in;
}