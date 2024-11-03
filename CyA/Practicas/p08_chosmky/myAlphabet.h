/** 
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Computabilidad y Algoritmia
 * Curso: 2º
 * Práctica 6: Diseño e implementación de un simulador de autómatas finitos
 * @file Alphabet.h
 * @brief Defines the Alphabet class for managing a set of symbols.
 * 
 * @details Provides methods to construct, clear, and find symbols in the alphabet.
 * 
 * @version 
 * @date 19/10/2024
 * 
 * @author Marco Aguiar Álvarez
 */


#ifndef ALPHABET_H
#define ALPHABET_H

#include <iostream>
#include <set>
#include <string>
#include <fstream>

class Alphabet{
 public:
  //constructores y destructor 
  Alphabet() : size_{0} {}
  ~Alphabet(){}
  Alphabet(const std::string&);
  //getter
  int get_size();
  //métodos
  void clear();
  bool find(char);
  //sobrecargas
  friend std::ostream& operator<<(std::ostream& os, const Alphabet& alphabet);
  friend std::istream& operator>>(std::istream& is, Alphabet& alphabet);
 private:
  //atributos
  std::set<char> symbols_;
  int size_;
};

#endif