/*Universidad de La Laguna
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática
* Asignatura: Computabilidad y Algoritmia
* Curso: 2º
* Práctica 6: Diseño e implementación de un simulador de autómatas finitos
* Autor: Marco Aguiar Álvarez
* Correo: alu0101620961@ull.edu.es
* Fecha: 19/10/2024
* Archivo Alphabet.cc: Contiene las implementaciones de métodos de la clase Alphabet.
**/


#ifndef AUTOMATA_H
#define AUTOMATA_H

#include "Alphabet.h"
#include "Estados.h"

class Automata {
 public:
  Automata() = default;
  //metodos
  void AnalizeAutomaton(const std::string& automaton_especifications, const std::string& inputs);

 private:
  //metodos
  void LoadInfo(const std::string& especifications);
  void SimulateStrings(const std::string& inputs);
  State SearchState(const int state_id);
  //Atributos
  Alphabet alphabet_;
  int total_states_;
  int initial_state_id_;
  std::set<State> states_;
};


#endif