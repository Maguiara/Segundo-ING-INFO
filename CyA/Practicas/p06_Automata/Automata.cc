

#include "Automata.h"
#include "Estados.h"


void Automata::AnalizeAutomaton(const std::string& automaton_especifications, const std::string& inputs) {
  LoadInfo(automaton_especifications);
  std::ifstream user_inputs(inputs);
  std::string user_string;
  while (std::getline(user_inputs, user_string)) {
    if (SimulateStrings(user_string)) std::cout << user_string << " --- Accepted";
    else std::cout << user_string << " --- Rejected";
  }
}




void Automata::LoadInfo(const std::string& automaton_especifications) {
  // Read the first line (alphabet of the automaton)
  std::ifstream especifications(automaton_especifications);
  std::string line;
  std::getline(especifications, line);
  std::istringstream iss(line);
  char symbol;
  while (iss >> symbol) {
    alphabet_.Emplace(symbol);
  }
  // Read the second line num of states
  std::getline(especifications, line);
  total_states_ = std::stoi(line);

  // Read the third line
  std::getline(especifications, line);
  initial_state_ = std::stoi(line); 

  // Read the information of the states and its transitions
  for(int i{0}; i < total_states_; i++) {
    std::getline(especifications, line);
    std::istringstream issStates(line);
    int state_id, num_transitions; 
    bool aceptation;
    issStates >> state_id >> aceptation >> num_transitions;
    State estado(state_id, aceptation);
    //check that it is an acceptance state
    if(estado.IsAceptation()) aceptance_states_.insert(estado);
    //read and save the transitions of each state
    for (int j{0}; j < num_transitions; j++){
      char state_symbol; 
      int transition_state_id;
      issStates >> state_symbol >> transition_state_id; 
      estado.AddTransition(state_symbol, transition_state_id);
    }
    states_.insert(estado);
  }

} 


bool Automata::SimulateStrings(const std::string& user_string) {
  std::set<int> current_states = {initial_state_};
  for (char symbol : user_string) {
    std::set<int> following_states;
    for (int current_state_id : current_states) {
      //
      for (auto state : states_ )
        if (state.getID() == current_state_id) {
          std::set<int> transitions = state.getTransitions(symbol);
          following_states.insert(transitions.begin(), transitions.end());
        }
    }
    current_states = following_states;
  }
  
}