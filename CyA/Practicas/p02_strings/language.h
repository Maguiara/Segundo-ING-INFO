/**
 * @file language.h
 * @brief Declaración de la clase Language y sus métodos.
 * Contiene la declaración de la clase Language, sus métodos y sobrecargas de operadores.
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
#include "mystring.h"

#ifndef LANGUAGE_H
#define LANGUAGE_H
class Language {
 public:
 	//Metodos
	void Prefix(MyString& user_string);
	void Sufix(MyString& user_string);
	void clear() { my_language_.clear(); }
	//Getter 
	const std::set<MyString> getLanguage() const { return my_language_; }
	//Sobrecargas
	friend std::istream& operator>>(std::istream& in, Language& user_language);
	friend std::ostream& operator<<(std::ostream& out, const Language& user_language);

 private:
  std::set<MyString> my_language_;
};

#endif