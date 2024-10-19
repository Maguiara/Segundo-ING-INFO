
#ifndef AUTOMATA_H
#define AUTOMATA_H

#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include "alphabet.h"
#include "Estados.h"

class Automata {

 public:
  void AnalizeAutomaton(const std::string& automaton_especifications, const std::string& inputs);


 private:
  void LoadInfo(const std::string& especifications);
  bool SimulateStrings(const std::string& inputs);
  Alphabet alphabet_;
  std::set<State> states_;
  std::set<State> aceptance_states_;
  int initial_state_;
  int total_states_;
};


#endif