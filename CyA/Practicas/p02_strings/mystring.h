/**
 * @file mystring.h
 * @brief Declaración de la clase MyString y sus métodos.
 * Contiene la definición de la clase MyString, sus constructores, getters,
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

#ifndef MYSTRING_H
#define MYSTRING_H
class MyString {
 public:
  //Constructores 
  MyString() = default;
  MyString(const std::string& user_string);
  //Getters
  std::string my_string() const { return my_string_; }
  int getSize() const; 
  //Metodos y sobrecargas
  void Invert();
  bool operator<(const MyString& other) const;
  friend std::istream& operator>>(std::istream& in, MyString& user_string);
  friend std::ostream& operator<<(std::ostream& out, const MyString& user_string);
 private:
	std::string my_string_{"&"};
  int size_{0};
};


#endif