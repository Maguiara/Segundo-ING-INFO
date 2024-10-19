
#include "tools.h"

class State {
 
 public:
  //Constructores
  State() = default;
  State(int state_id, bool aceptation) : state_id_(state_id), aceptation_(aceptation) {}

  //Metodos 
  void AddTransition(char state_symbol, int transition_state_id);

  //Getters
  bool IsAceptation(){ return aceptation_;}
  int getID(){ return state_id_; }
  std::set<int> getTransitions(char symbol);

  //sobrecargas
  bool operator<(const State& other);
  friend std::istream operator>>(std::ifstream& in, State& estado);
 private:
  int state_id_;
  bool aceptation_;
  int num_transitions_;
  std::multimap<char, int> transicions_;
};