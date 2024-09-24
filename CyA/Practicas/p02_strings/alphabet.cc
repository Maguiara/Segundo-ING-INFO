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
 * @param user_alphabet Cadena de símbolos del alfabeto.
 */
Alphabet::Alphabet(const std::string& user_alphabet) {
  for (char c : user_alphabet) {
    my_alphabet_.insert(c);
  }
} 

/**
 * @brief Sobrecarga del operador de inserción para la clase Alphabet.
 * @param out Flujo de salida.
 * @param user_alphabet Objeto Alphabet.
 * @return Referencia al flujo de salida.
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
 * @param in Flujo de entrada.
 * @param user_alphabet Objeto Alphabet.
 * @return Referencia al flujo de entrada.
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