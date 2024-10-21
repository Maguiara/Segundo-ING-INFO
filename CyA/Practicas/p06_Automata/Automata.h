
#ifndef AUTOMATA_H
#define AUTOMATA_H

#include "Alphabet.h"
#include "Estados.h"

class Automata {
 public:
  Automata() = default;
  //metodos
  void AnalizeAutomaton(const std::string& automaton_especifications, const std::string& inputs);
  void LoadInfo(const std::string& especifications);
  void SimulateStrings(const std::string& inputs);

 private:
  //metodos
  State SearchState(const int state_id);
  //Atributos
  Alphabet alphabet_;
  int total_states_;
  int initial_state_id_;
  std::set<State> states_;
};


#endif