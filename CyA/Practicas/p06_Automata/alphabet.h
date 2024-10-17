/**
 * @file alphabet.h
 * @brief Declaración de la clase Alphabet y sus métodos.
 * Contiene la declaración de la clase Alphabet, sus constructores, getters,
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

#ifndef ALPHABET_H
#define ALPHABET_H
class Alphabet {
 public:
  //Constructor por defecto y parametrizado
  Alphabet() = default;
  Alphabet(const std::string& user_alphabet);
  //Getters
  std::set<char> my_alphabet() { return my_alphabet_; }
  bool CheckAlphabet();
  //Sobrecargas
  friend std::istream& operator>>(std::istream& in, Alphabet& user_alphabet);
  friend std::ostream& operator<<(std::ostream& out, const Alphabet& user_alphabet);
 private:
	std::set<char> my_alphabet_;
};

#endif

