/*Universidad de La Laguna
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática
* Asignatura: Computabilidad y Algoritmia
* Curso: 2º
* Práctica 6: Diseño e implementación de un simulador de autómatas finitos
* Autor: Marco Aguiar Álvarez
* Correo: alu0101675893@ull.edu.es
* Fecha: 19/10/2024
* Archivo Alphabet.cc: Contiene las implementaciones de métodos de la clase Alphabet.
**/


#include "tools.h"
#include "Automata.h"
#include "Estados.h"
#include "Alphabet.h"

/**
 * @brief Analiza un autómata con especificaciones e inputs.
 * 
 * Carga la información del autómata y simula las cadenas proporcionadas.
 *
 * @param automaton_especifications Especificaciones del autómata.
 * @param inputs Cadenas de entrada para simular.
 */
void Automata::AnalizeAutomaton(const std::string& automaton_especifications, const std::string& inputs) {
  LoadInfo(automaton_especifications);
  SimulateStrings(inputs);
}


/**
 * @brief Carga la información del autómata desde un archivo de especificaciones.
 * 
 * Lee el alfabeto, el número total de estados, el estado inicial y las características
 * de cada estado. Valida que no haya más líneas de las esperadas en el archivo.
 *
 * @param automaton_especifications Ruta al archivo con las especificaciones del autómata.
 */
void Automata::LoadInfo(const std::string& automaton_especifications) {
  // Creamos el archivo de especificaciones
  std::ifstream especifications(automaton_especifications);
  std::string especification_line;
  //Leemos el alfabeto
  std::getline(especifications, especification_line);
  for (char c : especification_line) {
    if (c == '&') {
      std::cout << "El alfabeto introducido no es valido " << std::endl;
      exit(-1);
    }
  }
  alphabet_ = Alphabet(especification_line);
  //Leemos el numero total de estados
  std::getline(especifications, especification_line);
  total_states_ = std::stoi(especification_line);
  //Leemos el estado inicial
  std::getline(especifications, especification_line);
  initial_state_id_ = std::stoi(especification_line);

  //Leemos todas las lineas de caracteristicas de los estados
  for (int i{0}; i < total_states_; i++) {
    std::getline(especifications, especification_line);
    std::istringstream issStatesinfo(especification_line);
    State read_state(especification_line, alphabet_, total_states_);
    states_.emplace(read_state);
  }
  //Excepcion en caso de que haya mas lineas que estados totales especificados
  if(std::getline(especifications, especification_line)) {
    std::cout << "Se han especificado mas lineas de informacion de estados que estados totales especificados\n Por favor revise que su archivo: " << automaton_especifications << " esta correctamente escrito" << std::endl;
  }
} 

/**
 * @brief Simula la aceptación de cadenas de entrada en el autómata.
 * 
 * Lee cadenas desde un archivo, verifica si cada cadena es aceptada
 * o rechazada según las transiciones del autómata. Considera las 
 * transiciones epsilon y valida los símbolos contra el alfabeto.
 *
 * @param inputs Ruta al archivo que contiene las cadenas de entrada.
 */
void Automata::SimulateStrings(const std::string& inputs) {
  //Creamos el archivo de cadenas del usuario
  std::ifstream user_inputs_strings(inputs);
  std::string user_string_to_read;
  //Creamos el set que contendra los estados que se vayan leyendo

  while (std::getline(user_inputs_strings, user_string_to_read)) {
    //user_string_to_read.erase(user_string_to_read.find_last_not_of(" \n\r\t") + 1); 

    std::set<int> current_states_id;
    current_states_id.emplace(initial_state_id_);
    bool rejected = false;
    //Comprobamos que desde el estado inicial existan epsilon transiciones
    State initial_state = SearchState(initial_state_id_);
    std::set<int> epsilon_transitions = initial_state.getTransitions('&');
    if (!epsilon_transitions.empty()) current_states_id.insert(epsilon_transitions.begin(), epsilon_transitions.end());
    //Leemos cada simbolo de la cadena
    for (char symbol : user_string_to_read) {
      if(!alphabet_.find(symbol)) {
        std::cout << user_string_to_read << " --- Rejected" << std::endl;
        rejected = true;
        break;
      }
      //Analizamos todas las transiciones posibles de los estados actuales con el symbolo leido
      std::set<int> next_states;
      for(int state_id : current_states_id) {
        State analyze_state = SearchState(state_id);
        std::set<int> state_transitions = analyze_state.getTransitions(symbol);
        next_states.insert(state_transitions.begin(), state_transitions.end());
      }

      //Comprobamos que los nuevos estados alcanzados tengan epsilon transiciones
      std::set<int> epsilon_transitions_next_states;
      for (int next_state_id : next_states) {
        State analyze_next_state = SearchState(next_state_id);
        std::set<int> next_states_transitions = analyze_next_state.getTransitions('&');
        epsilon_transitions_next_states.insert(next_states_transitions.begin(), next_states_transitions.end());
      }

      next_states.insert(epsilon_transitions_next_states.begin(), epsilon_transitions_next_states.end());
      current_states_id = next_states;

      if(current_states_id.empty()) {
        std::cout << user_string_to_read << " --- Rejected" << std::endl;
        rejected = true;
        break;
      }
    }
     if (!rejected) {
      bool accepted = false;
      for (int state_id : current_states_id) {
        State valid_state = SearchState(state_id);
        if (valid_state.IsAceptation()) {
          accepted = true;
          break;
        }
      }

      if (accepted) {
        std::cout << user_string_to_read << " --- Accepted" << std::endl;
      } else {
        std::cout << user_string_to_read << " --- Rejected" << std::endl;
      }
    }

  }
  user_inputs_strings.close();
}

/**
 * @brief Busca un estado por su ID en el conjunto de estados.
 * 
 * Crea un objeto State con el ID proporcionado y lo busca en el conjunto.
 * Retorna el estado correspondiente.
 *
 * @param state_id ID del estado a buscar.
 * @return State El estado correspondiente al ID buscado.
 */

State Automata::SearchState(const int state_id) {
  State next_state;
  next_state.setID(state_id);
  auto it = states_.find(next_state);
  next_state = *it;  // Actualizar al siguiente estado
  return next_state;
}




/**
 * std::set<int> current_states = {initial_state_};
  for (char symbol : user_string) {
    std::set<int> following_states;
    for (int current_state_id : current_states) {
      for (auto state : states_ )
        if (state.getID() == current_state_id) {
          std::set<int> transitions = state.getTransitions(symbol);
          following_states.insert(transitions.begin(), transitions.end());
        }
    }
    current_states = following_states;
  }
  
}
 */


/**
 * Para mirar mañana: 
 * Rehacer el codigo desde 0 haciendo lo siguiente:
 *  -Al leer un alfabeto comprobar que este no contenga el simbolo &
 * 
 *  -Una clase automata que tenga un estado inicial (comprobar que en la linea que se lee el estado inicial no haya
 *   mas de un estado inicial), un alfabeto (mirar bien la clase alfabeto) un set de estados y si tal los estados totales
 * 
 *  -Una clase estado la cual tenga por atributos id del estado, si el estado es de aceptacion o no, el rango de la transicion,
 *   el numero de transiciones que tiene el estado, un alfabeto y un multimap con las trancisiones
 * 
 *  -Un construcctor de la clase estate la cual le llega una linea que leida del archivo de especificaciones, 
 *   y un alfabeto para comprobar si el simbolo pertenece y construte las transiciones dentro del constructor
 * 
 *  -Mejorar o rehacer el metodo simulatestring y el metodo Analyze automata con el que me dio dani (tener en cuenta todas las 
 *  cosas que pueden hacer que una cadena sea rechazada)
 * 
 * 
 * A las muy malas cambiar todo el codigo de dani
 */