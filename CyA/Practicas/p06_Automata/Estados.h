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


#ifndef ESTADOS_H
#define ESTADOS_H

#include "tools.h"
#include "Alphabet.h"

class State {
 
 public:
  //Constructores
  State() = default;
  State(const std::string& state_information, const Alphabet& valid_alphabet, const int valid_states);

  //Getters
  Alphabet getAlphabet() {return alphabet_;}
  int getID(){ return state_id_; }
  void setID(const int& num) {state_id_= num; }
  bool IsAceptation(){ return aceptation_;}
  int getNumTransitions() {return num_transitions_; }
  std::set<int> getTransitions(char symbol);

  //Metodos
  std::set<int> EpsilonClausure();
  
  //sobrecargas
  bool operator<(const State& other) const;

 private:
  Alphabet alphabet_;
  int state_id_;
  bool aceptation_;
  int num_transitions_;
  std::multimap<char, int> transitions_;
};

#endif