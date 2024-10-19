
#include "tools.h"
#include "Estados.h"



void State::AddTransition(char state_symbol, int transition_state_id) {
  transicions_.emplace(state_symbol, transition_state_id);
  
}



bool State::operator<(const State& other) const {
  return state_id_ < other.state_id_;
}


std::set<int> State::getTransitions(char symbol) {
  std::set<int> result;  // Usamos un set para almacenar los estados de destino únicos

    // We use equal_range to get all transitions with the same symbol
    auto range = transicions_.equal_range(symbol);
    for (auto it = range.first; it != range.second; ++it) {
        result.insert(it->second);  // Insertamos cada estado de destino en el set
    }
    //Exactamente lo mismo pero comprobando con las epsilon transiciones
     auto range2 = transicions_.equal_range('&');
    for (auto it2 = range.first; it2 != range.second; ++it2) {
        result.insert(it2->second);  // Insertamos cada estado de destino en el set
    }

    return result;
}