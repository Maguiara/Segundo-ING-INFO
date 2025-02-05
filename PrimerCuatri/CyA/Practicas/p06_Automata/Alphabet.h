// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 6: Diseño e implementación de un simulador de autómatas finitos
// Autor: Daniel Martínez Sopo
// Correo: alu0101675893@ull.edu.es
// Fecha: 19/10/2024
// Archivo Alphabet.h: Contiene la clase Alphabet utilizada en el proyecto, esta cumple el rol
//                     de alfabeto en el contexto de la computabilidad.
// Historial de revisiones
// 19/10/2024 - Creación (primera versión) del código
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