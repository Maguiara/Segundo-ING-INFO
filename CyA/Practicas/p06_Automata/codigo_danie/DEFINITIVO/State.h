// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 6: Diseño e implementación de un simulador de autómatas finitos
// Autor: Daniel Martínez Sopo
// Correo: alu0101675893@ull.edu.es
// Fecha: 19/10/2024
// Archivo State.h: Contiene la clase State utilizada en el proyecto, esta cumple el rol
//                  de estado en el contexto de los autómatas finitos.
// Historial de revisiones
// 19/10/2024 - Creación (primera versión) del código
#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <map>
#include "AlphabetDani.h"
#include <sstream>
#include <utility>
#include <vector>
 
class State {
 public:
  //constructores
  State(){}
  State(const std::string& line, const Alphabet& alphabet, const int& staterange);
  //getter y setter
  int get_state_num()const {return statenum_;}
  void set_state_num(const int& num) {statenum_ = num;}
  //métodos
  bool acceptance(){return acceptance_;}
  std::set<int> check_transition(const char& symbol);
  void invalid_transition(const int& opcode);
  //sobrecarga del operador
  bool operator<(const State& other) const;
 private:
  int statenum_;
  int staterange_;
  bool acceptance_;
  int transitionnum_;
  Alphabet alphabet_;
  std::multimap<char, int> transitions_;
};

#endif