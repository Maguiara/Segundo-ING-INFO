 // Universidad de La Laguna
 // Escuela Superior de Ingeniería y Tecnología
 // Grado en Ingeniería Informática
 // Asignatura: Computabilidad y Algoritmia
 // Curso: 2º
 // Práctica 2: Cadenas y lenguajes
 // Autor: Marco Aguiar Álvarez
 // Correo: alu0101620961@ull.edu.es
 // Fecha: 19/09/2024
 // Archivo Mystring.h: Archivo que contiene la declaracion de la clase "cadena".
 // Contiene la definicion de las funciones herramienta contenidas en el programa
 // para indicar al usuario el correcto funcionamiento del codigo
 // Historial de revisiones
 // 19/09/2024- Creación (primera versión) del código
 // 20/09/2024- Creacion de las clases "cadena", "lenguaje", y "alfabeto" con la definicion de sus metodos privados

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
  int size() const { return size_; }
  //Metodos y sobrecargas
  void Invert();
  friend std::istream& operator>>(std::istream& in, MyString& user_string);
  friend std::ostream& operator<<(std::ostream& out, const MyString& user_string);
 private:
	std::string my_string_{""};
  int size_{0};
};


#endif