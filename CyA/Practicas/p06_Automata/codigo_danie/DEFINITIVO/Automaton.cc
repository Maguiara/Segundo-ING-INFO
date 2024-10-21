// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 6: Diseño e implementación de un simulador de autómatas finitos
// Autor: Daniel Martínez Sopo
// Correo: alu0101675893@ull.edu.es
// Fecha: 19/10/2024
// Archivo Automaton.cc: Contiene las implementaciones de métodos de la clase Automaton.
// Historial de revisiones
// 19/10/2024 - Creación (primera versión) del código
#include "Automaton.h"


/**
 * @brief Constructs an Automaton object from a given input file.
 * 
 * @param input Path to the input file containing automaton definitions.
 * 
 * @details Reads the automaton's alphabet, state count, initial state,
 *          and transitions from the input file. Validates the configuration
 *          and stores the states in a set.
 */
Automaton::Automaton(const std::string& input){
  std::ifstream filein(input);
  std::string line;
  std::getline(filein, line);
  for (char c : line) {
    if (c == '&') invalid_automaton(1);
  }
  alphabet_ = Alphabet(line);
  line.clear();
  std::getline(filein, line);
  statenum_ = std::stoi(line);
  line.clear();
  std::getline(filein, line);
  int counter = 0;
  for (char c : line){
    if (c != ' ') counter++;
  }
  if (counter != 1) invalid_automaton(2);
  int first = std::stoi(line);
  line.clear();
  counter = 0;
  while(std::getline(filein, line)){
    int state_num = line[0] - '0';
    if (state_num == first){
      initial_ = State(line, alphabet_, statenum_);
      states_.emplace(initial_);
    }
    else{
      states_.emplace(State(line, alphabet_, statenum_));
    }
    counter++;
  }
  if(counter != statenum_) invalid_automaton(3);
}

/**
 * @brief Checks a set of strings against the automaton.
 * 
 * @param input Path to the file containing strings to be checked.
 * 
 * @details Reads each string from the input file and simulates the automaton
 *          to determine whether each string is accepted or rejected.
 */
void Automaton::check_string(const std::string& input){
  std::ifstream filein(input);
  std::string line;
  while (std::getline(filein, line)) {
    int current_state_num = initial_.get_state_num();  // Estado inicial
    State current_state = initial_;                    // Comenzar desde el estado inicial
    bool rejected = false;
    std::set<int> actual_states;
    actual_states.emplace(current_state_num);
    std::set<int> epsilon = current_state.check_transition('&');
    if (!epsilon.empty()) actual_states.insert(epsilon.begin(), epsilon.end());
    // ahora en actual states tenemos todas las posibilidades por las que podriamos avanzar para seguir leyendo el automata
    for (char c : line) {
      if (c == '&') break;
      if (!alphabet_.find(c)) {
        std::cout << line << " --- Rejected" << std::endl;
        rejected = true;
        break;
      }
      else{
        std::set<int> next_states;  // Conjunto de estados para el siguiente símbolo
        for(int current : actual_states){
          State workingstate = search_state(current); 
          std::set<int> next = workingstate.check_transition(c);  // Transiciones con 'c'
          next_states.insert(next.begin(), next.end());  // Agregar los nuevos estados 
        }

        std::set<int> epsilon_next;
        for (int current : next_states) {
            State workingstate = search_state(current);
            std::set<int> epsilon = workingstate.check_transition('&');
            epsilon_next.insert(epsilon.begin(), epsilon.end());
        }

        // Actualizar el conjunto actual de estados
        next_states.insert(epsilon_next.begin(), epsilon_next.end());
        actual_states = next_states;


        if (actual_states.empty()) {
            rejected = true;
            std::cout << line << " --- Rejected" << std::endl;
            break;
        }
      }
    }  
    if (!rejected) {
      bool accepted = false;
      for (int state : actual_states) {
        State current = search_state(state);
        if (current.acceptance()) {
          accepted = true;
          break;
        }
      }

      if (accepted) {
        std::cout << line << " --- Accepted" << std::endl;
      } else std::cout << line << " --- Rejected" << std::endl;
    }           
  }
}  


/**
 * @brief Searches for a state by its number.
 * 
 * @param state The number of the state to search for.
 * 
 * @return The State object corresponding to the given state number.
 */
State Automaton::search_state(const int& state){
  State next_state;
  next_state.set_state_num(state);
  auto it = states_.find(next_state);
  next_state = *it;  // Actualizar al siguiente estado
  return next_state;
}




/**
 * @brief Handles invalid automaton configurations.
 * 
 * @param opcode The code indicating the type of error.
 * 
 * @details Prints an error message and exits the program if the automaton
 *          configuration is invalid, such as having an invalid alphabet,
 *          multiple initial states, or mismatched state definitions.
 */
void Automaton::invalid_automaton(int opcode) {
  if(opcode == 1){
    std::cout << "It appears you have choosen as one of the symbols of your alphabet the reserved character to designate the empty string: &\n " <<
    "Please change that symbol or the simulator will NOT accept your automatan text file." << std::endl;
    exit(-1);
  }
  if(opcode == 2){
    std::cout << "Looks like your automaton has more than one intial state. The simulator will NOT accept your automaton text file " <<
    "if it has more than one initial state." <<  std::endl;
    exit(-1);
  }  
  if(opcode == 3){
    std::cout << "The number of sentences describing states and the number of states of your automatan do not match. Your automatan " <<
    "must have a decription for each state even if it does not have any transition, in which case you should just say that it has 0 transitions" <<
    std::endl;
    exit(-1);
  }
}