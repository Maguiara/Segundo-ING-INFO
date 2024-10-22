/*Universidad de La Laguna
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática
* Asignatura: Computabilidad y Algoritmia
* Curso: 2º
* Práctica 6: Diseño e implementación de un simulador de autómatas finitos
* Autor: Marco Aguiar Álvarez
* Correo: alu0101620961@ull.edu.es
* Fecha: 19/10/2024
* Archivo Alphabet.cc: Contiene las implementaciones de métodos de la clase Alphabet.
**/



#include "tools.h"
#include "Estados.h"
#include "Alphabet.h"

/**
* @brief Constructor parametrizado que inicializa un objeto State a partir de información de estado.
* 
* Este constructor recibe una cadena que contiene la información del estado,
* un objeto Alphabet que representa los símbolos válidos y un entero que
* indica la cantidad de estados válidos. Procesa la cadena para extraer
* el ID del estado, si es un estado de aceptación, y las transiciones
* asociadas. Valida que los símbolos de transición estén en el alfabeto
* y que los IDs de estado de transición sean válidos.
*
* @param state_information Cadena que contiene el ID del estado, la aceptación y las transiciones.
* @param valid_alphabet Objeto Alphabet que representa los símbolos válidos para las transiciones.
* @param valid_state Cantidad total de estados válidos en el autómata.
**/
State::State(const std::string& state_information, const Alphabet& valid_alphabet, const int valid_state) {
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
    if( (transition_state_id < 0)| (transition_state_id >= valid_state)) {
      std::cout << "El estado al que se intenta transitar ( " << transition_state_id << " ) con el simbolo " << transition_symbol <<  " no es valido" << std::endl;
      exit(-1);
    }
    transitions_.emplace(transition_symbol, transition_state_id);
  } 
}

/**
 * @brief Compara dos estados por su ID.
 * 
 * Devuelve true si el ID del estado actual es menor que el de `other`.
 *
 * @param other Otro objeto State a comparar.
 * @return true Si el ID actual es menor.
 * @return false En caso contrario.
 */
bool State::operator<(const State& other) const {
  return state_id_ < other.state_id_;
}

/**
 * @brief Obtiene los estados de transición para un símbolo dado.
 * 
 * Devuelve un conjunto de IDs de estados a los que se puede transitar
 * usando el símbolo especificado.
 *
 * @param symbol Símbolo utilizado para buscar las transiciones.
 * @return std::set<int> Conjunto de IDs de estados de transición.
 */
std::set<int> State::getTransitions(char symbol) {
  auto range = transitions_.equal_range(symbol);
  std::set<int> result;  
  for (auto it = range.first; it != range.second; ++it) {
    int transition_state = it->second;
    result.emplace(transition_state);
  }
  return result;
}



// Prubeas varias
/*
std::set<int> State::EpsilonClausure() {
  std::set<int> epsilon_transitions;

}
*/
// Pruebas varias para la depuracion del codigo
/**std::ostream& operator<<(std::ofstream& out, const State& estado) {
  out << "alfabeto: " << estado.alphabet_ << std::endl;
  out << "Id del estado: " << estado.state_id_ <<  std::endl;
  (estado.aceptation_) ? out << "Es de aceptacion" << std::endl : out << " No es de aceptacion" << std::endl;
  out << "numero de transiciones: " << estado.num_transitions_ << std::endl;
  return out; 
}

*/