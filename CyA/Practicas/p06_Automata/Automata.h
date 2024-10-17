
#ifndef AUTOMATA_H
#define AUTOMATA_H

#include <iostream>
#include <set>
#include <vector>
#include <map>
#include "alphabet.h"
#include "Estados.h"

class Automata {



 private:
  Alphabet alphabet_;
  std::set<State> states_;
  State initial_state_;
  int total_states_;
};


#endif