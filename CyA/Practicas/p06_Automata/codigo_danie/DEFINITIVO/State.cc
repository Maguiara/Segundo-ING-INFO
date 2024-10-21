// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 6: Diseño e implementación de un simulador de autómatas finitos
// Autor: Daniel Martínez Sopo
// Correo: alu0101675893@ull.edu.es
// Fecha: 19/10/2024
// Archivo State.cc: Contiene las implementaciones de métodos de la clase State.
// Historial de revisiones
// 19/10/2024 - Creación (primera versión) del código
#include "State.h"

/**
 * @brief Constructs a State object from a given input line.
 * 
 * @param line The input line containing state information.
 * @param alphabet The alphabet of the automaton.
 * @param staterange The total number of states in the automaton.
 * 
 * @details Parses the input line to initialize the state number, 
 *          acceptance status, number of transitions, and the transitions themselves.
 */
State::State(const std::string& line, const Alphabet& alphabet, const int& staterange){
  alphabet_ = alphabet;
  staterange_ = staterange;
  std::istringstream iss(line); 
  iss >> statenum_; 
  int aux;
  iss >> aux; 
  acceptance_ = (aux == 1); 
  iss >> transitionnum_; 
  for (int i{0}; i < transitionnum_; ++i) {
    char symbol;
    int next_state;
    iss >> symbol; 
    if(!alphabet_.find(symbol)){
      if(symbol != '&') invalid_transition(1); 
    }      
    iss >> next_state;  
    if(next_state < 0 || next_state >= staterange_) invalid_transition(2);
    transitions_.emplace(symbol, next_state);
  }
}

/**
 * @brief Overloads the less-than operator for State objects.
 * 
 * @param other The other State object to compare against.
 * 
 * @return true if the current state number is less than the other state's number; false otherwise.
 */
bool State::operator<(const State& other) const{
  return statenum_ < other.statenum_;
}


/**
 * @brief Checks for possible transitions from the current state for a given symbol.
 * 
 * @param symbol The input symbol to check for transitions.
 * 
 * @return A set of possible next states for the given symbol.
 */
std::set<int> State::check_transition(const char& symbol) {
  auto range = transitions_.equal_range(symbol); 
  std::set<int> posibilities;
  if(range.first == range.second) return posibilities;  
  for (auto it = range.first; it != range.second; ++it) {
    int next_state = it->second; 
    posibilities.emplace(next_state);
  }
  return posibilities; 
}


/**
 * @brief Handles invalid transitions for the state.
 * 
 * @param opcode The code indicating the type of error.
 * 
 * @details Prints an error message and exits the program if the state attempts
 *          to transition with an invalid symbol or to a non-existent state.
 */
void State::invalid_transition(const int& opcode){
  if(opcode == 1){
    std::cout << "The state " << statenum_ << " tries to do a transition with a symbol non existent in your automaton's alphabet." << std::endl;
    exit(-1);  
  }
  if(opcode == 2){
    std::cout << "The state " << statenum_ << " tries to do a transition to a non existent state in your automaton." << std::endl;
    exit(-1);
  }
}