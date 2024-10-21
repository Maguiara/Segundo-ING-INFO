
#ifndef ESTADOS_H
#define ESTADOS_H

#include "tools.h"
#include "Alphabet.h"

class State {
 
 public:
  //Constructores
  State() = default;
  State(const std::string& state_information, const Alphabet& valid_alphabet);

  //Getters
  Alphabet getAlphabet() {return alphabet_;}
  int getID(){ return state_id_; }
  void setID(const int& num) {state_id_= num; }
  bool IsAceptation(){ return aceptation_;}
  int getNumTransitions() {return num_transitions_; }
  std::set<int> getTransitions(char symbol);
  
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