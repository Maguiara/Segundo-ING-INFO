
#include "tools.h"

class State {


 private:

  int state_id_;
  int num_transitions_;
  bool aceptacion_;
  std::multimap<State, std::pair<char, int>> transicions_;
};