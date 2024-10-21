
#include "tools.h"
#include "Estados.h"
#include "Alphabet.h"

//Constructor parametrizado
State::State(const std::string& state_information, const Alphabet& valid_alphabet) {
  alphabet_ = valid_alphabet;
  std::istringstream issStateInfo(state_information);
  issStateInfo >> state_id_ ;
  int aceptance_state;
  issStateInfo >> aceptance_state;
  aceptation_ = (aceptance_state == 1);
  issStateInfo >> num_transitions_;
  for (int i{0}; i < num_transitions_; i++) {
    char transition_symbol;
    issStateInfo >> transition_symbol;
    if(!alphabet_.find(transition_symbol) && transition_symbol != '&') {
      std::cout << "El simbolo con el que se intenta transitar ( " << transition_symbol  <<" ) no existe en el alfabeto" << std::endl;
      exit(-1);
    }
    int transition_state_id;
    issStateInfo >> transition_state_id;
    if( transition_state_id < 0 ) {
      std::cout << "El estado al que se intenta transitar ( " << transition_state_id << " ) con el simbolo " << transition_symbol <<  " no es valido" << std::endl;
      exit(-1);
    }
    transitions_.emplace(transition_symbol, transition_state_id);
  } 


}


bool State::operator<(const State& other) const {
  return state_id_ < other.state_id_;
}


std::set<int> State::getTransitions(char symbol) {
  auto range = transitions_.equal_range(symbol);
  std::set<int> result;  
  for (auto it = range.first; it != range.second; ++it) {
    int transition_state = it->second;
    result.emplace(transition_state);
  }
  return result;
}

/**std::ostream& operator<<(std::ofstream& out, const State& estado) {
  out << "alfabeto: " << estado.alphabet_ << std::endl;
  out << "Id del estado: " << estado.state_id_ <<  std::endl;
  (estado.aceptation_) ? out << "Es de aceptacion" << std::endl : out << " No es de aceptacion" << std::endl;
  out << "numero de transiciones: " << estado.num_transitions_ << std::endl;
  return out; 
}

*/