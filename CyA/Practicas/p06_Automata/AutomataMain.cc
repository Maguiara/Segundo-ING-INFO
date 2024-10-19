

#include "tools.h"
#include "Automata.h"
#include "Estados.h"
#include "alphabet.h"

int main (int argc, char* argv[]) {
  usage(argc, argv);
  Automata user_automata;
  user_automata.AnalizeAutomaton(argv[1], argv[2]);
} 