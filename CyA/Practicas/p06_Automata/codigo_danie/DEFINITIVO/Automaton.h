// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 6: Diseño e implementación de un simulador de autómatas finitos
// Autor: Daniel Martínez Sopo
// Correo: alu0101675893@ull.edu.es
// Fecha: 19/10/2024
// Archivo Automaton.h: Contiene la clase Automaton utilizada en el proyecto, esta cumple el rol
//                      de autómata en el contexto de los autómatas finitos.
// Historial de revisiones
// 19/10/2024 - Creación (primera versión) del código
#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <iostream>
#include "AlphabetDani.h"
#include "State.h"
#include <set>
#include <fstream>
#include <vector>

class Automaton {
 public:
  //constructor
  Automaton(const std::string& input);
  //métodos
  void check_string(const std::string& input);
  State search_state(const int& state);
  void invalid_automaton(int opcode);
 private:
  Alphabet alphabet_;
  int statenum_;
  State initial_;
  std::set<State> states_;
};

#endif

