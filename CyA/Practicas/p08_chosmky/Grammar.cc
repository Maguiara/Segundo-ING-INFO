

/**
 * @file Grammar.cc
 * @brief Implementación de la clase Grammar para transformar gramáticas a la Forma Normal de Chomsky (CNF).
 * 
 * Este archivo contiene la implementación de la clase Grammar, que proporciona métodos para cargar información
 * de la gramática desde un archivo, transformar la gramática a la Forma Normal de Chomsky (CNF) y escribir la
 * gramática transformada en un archivo de salida.
 * 
 * Los métodos principales en este archivo incluyen:
 * - Transform2CFN: Transforma la gramática de entrada a CNF y la escribe en un archivo de salida.
 * - LoadInformation: Carga la información de la gramática desde un archivo de entrada.
 * - GenerateNonTerminal: Genera un nuevo símbolo no terminal.
 * - PrimeraParte: Primera parte del algoritmo para transformar la gramática a CNF.
 * - SegundaParte: Segunda parte del algoritmo para transformar la gramática a CNF.
 * - Write: Escribe la gramática transformada en un archivo de salida.
 * 
 * @note La implementación asume que el archivo de la gramática de entrada está correctamente formateado.
 * @note La implementación no maneja producciones unitarias ni producciones vacías.
 * 
 * @see Grammar.h
 * @see tools.h
 */


#include "Grammar.h"
#include "tools.h"


/**
 * @brief transforma la gramatica de la entrada en una gramatica en FN de chomsky
 * 
 * @param input_file 
 * @param output_file 
 */
void Grammar::Transform2CFN(const std::string& input_file, const std::string& output_file) {
  LoadInformation(input_file);
  PrimeraParte();
  SegundaParte();
  Write(output_file);
  if (CompararSalida(input_file, output_file)) std::cout << "La gramatica ya estaba en forma normal de Chomsky" << std::endl;
  else std::cout << "El archivo no estaba en forma normal de Chomsky" << std::endl;
}


/**
 * @brief Lee toda la informacion del archivo que contiene la gramtica, 
 *        cargandola en los parametros de la clase
 * 
 * @param input_file 
 */
void Grammar::LoadInformation(const std::string& input_file) {
  //Abrir el archivo de entrada
  std::ifstream input_gramar(input_file);
  if (!input_gramar.is_open()) ErrorExit(0);
  std::string especification_line;
  std::getline(input_gramar, especification_line);
  // Leemos el numero de terminales para la gramatica
  num_of_terminals_ = std::stoi(especification_line);
  std::string grammar_alphabet;
  for (int i{0}; i < num_of_terminals_; i++) {
    std::getline(input_gramar, especification_line);
    grammar_alphabet += especification_line[0];
    terminals_.emplace(especification_line[0]);
  }
  valid_alphabet_ = grammar_alphabet;
  if (valid_alphabet_.find('&')) ErrorExit(1);
  // Leemos el numero de no terminales para la gramatica
  std::getline(input_gramar, especification_line);
  num_of_non_terminals_ = std::stoi(especification_line);
  for (int i{0}; i < num_of_non_terminals_; i++) {
    std::getline(input_gramar, especification_line);
    if (islower(especification_line[0])) ErrorExit(3);
    if (especification_line[0] == '&') ErrorExit(5);
    non_terminals_.emplace(especification_line[0]);
  }
  // Leemos el numero de producciones para la gramatica
  std::getline(input_gramar, especification_line);
  num_of_productions_ = std::stoi(especification_line);
  for (int i{0}; i < num_of_productions_; i++) {
    std::getline(input_gramar, especification_line);
    std::istringstream aux(especification_line);
    char non_terminal;
    std::string production;
    aux >> non_terminal >> production;
    // Comprobaciones sobre las producciones
    if (non_terminals_.find(non_terminal) == non_terminals_.end()) {
      std::cout << "Error en la produccion: " << non_terminal << " -> " << production << std::endl;
      ErrorExit(2);
    }
    if (islower(non_terminal)) {
      std::cout << "Error en la produccion: " << non_terminal << " -> " << production << std::endl;
      ErrorExit(3);
    }
    if (production == "&") {
      std::cout << "Error en la produccion: " << non_terminal << " -> " << production << std::endl;
      ErrorExit(4);
    }
    if (production.size() == 1 && isupper(production[0])) {
      std::cout << "Error en la produccion: " << non_terminal << " -> " << production << std::endl;
      ErrorExit(6);
    } 
    productions_.emplace(non_terminal, production);
  }
}


/**
 * @brief Genera un nuevo no terminal a partir de un terminal o un no terminal
 * 
 * @param c Terminal o no terminal a partir del cual se generara el nuevo no terminal
 */
char Grammar::GenerateNonTerminal(const char c) {
  char aux = toupper(c);
  while(non_terminals_.find(aux) != non_terminals_.end()) {
    aux++;
    if (aux == 'Z') aux = 'A';
  }
  non_terminals_.emplace(aux);
  num_of_non_terminals_++;
  return aux;
}


/**
 * @brief Primera parte del algoritmo de transformacion a FN de chomsky
 * 
 */
void Grammar::PrimeraParte() {
  // Mapa para almacenar la correspondencia entre terminales y no terminales
  std::map<char, char> terminal_to_non_terminal;

  for (auto it = productions_.begin(); it != productions_.end(); ++it) {
    std::string production = it->second;
    std::string new_production;
    if (production.size() > 1) {
      for (char& c : production) {
        if (islower(c)) {
          if (terminal_to_non_terminal.find(c) == terminal_to_non_terminal.end()) {
            // Generar un nuevo no terminal para el terminal c
            char new_non_terminal = GenerateNonTerminal(c);
            terminal_to_non_terminal[c] = new_non_terminal;
            // Añadir la nueva producción al conjunto de producciones
            std::string comprobacion = std::string(1, c);
            
            productions_.emplace(new_non_terminal, std::string(1, c));
            num_of_productions_++;
          }
          // Remplazar el terminal c por el no terminal correspondiente
          new_production += terminal_to_non_terminal[c];
        } else {
          new_production += c;
        }
      }
  
      // Actualizar la producción original con los no terminales
      it->second = new_production;
    }
  }
}


/**
 * @brief Segunda parte del algoritmo de transformacion a FN de chomsky 
 * 
 */
void Grammar::SegundaParte() {
  std::map<char, std::string> new_productions;
  // Iterar sobre las producciones y dividirlas en producciones de dos no terminales
  for (auto it = productions_.begin(); it != productions_.end(); ++it) {
    std::string production = it->second;
    if (production.size() >= 3) {
      char non_terminal = it->first;
      std::vector<char> new_non_terminals;
      // Creamos los no terminales necesarios ( m - 2 )
      for (long unsigned int i{0}; i < production.size() - 2; i++) {
        non_terminal = GenerateNonTerminal('A');
        new_non_terminals.push_back(non_terminal);
      }
      // Añadir las nuevas producciones al mapa
      non_terminal = it->first;
      for (long unsigned int i{0}; i < production.size() - 2; i++) {
        new_productions[non_terminal] = std::string(1, production[i]) + new_non_terminals[i];
        non_terminal = new_non_terminals[i];
      }
      // Añadir la última producción
      new_productions[new_non_terminals[new_non_terminals.size()- 1]] = std::string(1, production[production.size() - 2]) + std::string(1, production[production.size() - 1]);
      // Actualizar la producción original con los no terminales
        it->second = std::string(1, production[0]) + new_non_terminals[0];
    }
  }
  // Add the new productions to the grammar
  for (const auto& prod : new_productions) {
    productions_.emplace(prod.first, prod.second);
    num_of_productions_++;
  }
  
}



/**
 * @brief Escribe la gramatica en el archivo de salida
 * 
 * @param output_file 
 */
void Grammar::Write(const std::string& output_file) {
  std::ofstream output_grammar(output_file);
  if (!output_grammar.is_open()) ErrorExit(7);
  output_grammar << num_of_terminals_  << std::endl;
  for (auto it = terminals_.begin(); it != terminals_.end(); it++) output_grammar << *it << std::endl;
  output_grammar << num_of_non_terminals_ << std::endl;
  for (auto it = non_terminals_.begin(); it != non_terminals_.end(); it++) output_grammar << *it << std::endl;
  output_grammar << num_of_productions_ << std::endl;
  for (auto it = productions_.begin(); it != productions_.end(); it++) output_grammar << it->first << " " << it->second << std::endl;

}


/**
 * @brief Compara si el archivo especificado por el usuario ya estaba en FNC
 * 
 * @param input_file 
 * @param output_file 
 * @return true 
 * @return false 
 */
bool Grammar::CompararSalida(const std::string& input_file, const std::string& output_file) {
  std::ifstream input(input_file);
  std::ifstream output(output_file);
  std::string input_line, output_line;

  while (std::getline(input, input_line) && std::getline(output, output_line)) {
    if (input_line != output_line) return false;
  }
  return true;
}



/**
 * @brief Funcion que recibe un codigo de error y muestra un mensaje de error
 * 
 * @param error_code 
 */
void Grammar::ErrorExit(const int error_code) {
  switch (error_code) {
    case 0:
      std::cerr << "Error: No se puede abrir el archivo de entrada." << std::endl;
      break;
    case 1:
      std::cerr << "Error: La cadena vacía '&' no está permitida en el alfabeto de la gramática." << std::endl;
      break;
    case 2:
      std::cerr << "Error: Símbolo no terminal no encontrado en el conjunto de no terminales." << std::endl;
      break;
    case 3:
      std::cerr << "Error: El símbolo terminal está en minúsculas." << std::endl;
      break;
    case 4:
      std::cerr << "Error: La producción vacía no está permitida." << std::endl;
      break;
    case 5:
      std::cerr << "Error: El símbolo '&' no puede ser un símbolo no terminal." << std::endl;
      break;
    case 6:
      std::cerr << "Error: Producción unitaria no permitida." << std::endl;
      break;
    case 7:
      std::cerr << "Error: No se puede abrir el archivo de salida." << std::endl;
      break;
    default:
      std::cerr << "Error: Error desconocido." << std::endl;
      break;
  }
  exit(-1);
}

/**
 * @brief Comprueba si una producción ya existe en el conjunto de producciones.
 * 
 * @param production La producción a comprobar.
 * @return true si la producción ya existe, false en caso contrario.
 */
bool Grammar::ComprobarProduccion(const std::string& production) {
  for (const auto& prod : productions_) {
    if (prod.second == production) 
      return true;
  }
  return false;
}

// ############################//
//  PRUEBAS QUE NO FUNCIONARON //
// ############################//


  /** Investigar si se puede hacer esto y luego getlines 
  char simbol_of_alphabet;
  std::string alphabet;
  input_gramar >> num_of_terminals_;
  for (int i{0}; i < num_of_terminals_; i++) {
    input_gramar >> simbol_of_alphabet;
    alphabet += simbol_of_alphabet; 
  }
  **/ 


 // Primer prototipo de la funcion PrimeraParte
 //void Grammar::PrimeraParte() {
//  //Leemos todas las producciones y las modificamos en caso de encontrar una prod. > 1 que no sea una cadena de no terminales
//  for (auto it = productions_.begin(); it != productions_.end(); it++) {
//    std::string production = it->second;
//    if (production.size() > 1) { // S -> aXbX -> S -> AXBX
//    //este primer bucle solo cambia los terminales por no terminales
//    std::set<char> find_terminals;
//    std::cout << "Produccion: " << production << std::endl;
//      for (char& c : production) {
//        if(islower(c)) {
//          std::cout << "Terminal: " << c << std::endl;
//          find_terminals.emplace(c);
//        }
//      }
//
//      
//    std::cout << "Produccion despues de los cambios: " << production << std::endl;
//    }
//  } 
//}