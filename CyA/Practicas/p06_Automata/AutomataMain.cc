

#include "tools.h"
#include "Automata.h"
#include "Estados.h"
#include "Alphabet.h"

int main (int argc, char* argv[]) {
  usage(argc, argv);
  Automata user_automata;
  std::string input = argv[2];
  user_automata.AnalizeAutomaton(argv[1], input);

} 