

/**
 * @file Grammar.cc
 * @brief Implementation of the Grammar class for transforming grammars into Chomsky Normal Form (CNF).
 * 
 * This file contains the implementation of the Grammar class, which provides methods to load grammar
 * information from a file, transform the grammar into Chomsky Normal Form (CNF), and write the transformed
 * grammar to an output file.
 * 
 * The main methods in this file include:
 * - Transform2CFN: Transforms the input grammar into CNF and writes it to an output file.
 * - LoadInformation: Loads grammar information from an input file.
 * - GenerateNonTerminal: Generates a new non-terminal symbol.
 * - PrimeraParte: First part of the algorithm for transforming the grammar into CNF.
 * - SegundaParte: Second part of the algorithm for transforming the grammar into CNF.
 * - Write: Writes the transformed grammar to an output file.
 * 
 * The Grammar class uses several private member variables to store the grammar's terminals, non-terminals,
 * and productions.
 * 
 * @note The implementation assumes that the input grammar file is correctly formatted.
 * @note The implementation does not handle unit productions or empty productions.
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
}


/**
 * @brief Lee toda la informacion del archivo que contiene la gramtica, 
 *        cargandola en los parametros de la clase
 * 
 * @param input_file 
 */
void Grammar::LoadInformation(const std::string& input_file) {
  std::ifstream input_gramar(input_file);
  std::string especification_line;
  std::getline(input_gramar, especification_line);
  num_of_terminals_ = std::stoi(especification_line);
  std::string grammar_alphabet;
  for (int i{0}; i < num_of_terminals_; i++) {
    std::getline(input_gramar, especification_line);
    grammar_alphabet += especification_line[0];
    terminals_.emplace(especification_line[0]);
  }
  valid_alphabet_ = grammar_alphabet;
  if (valid_alphabet_.find('&')) {
    std::cout << "El simbolo '&' no puede pertenecer al alfabeto" << std::endl;
    exit(-1);
  }
  std::getline(input_gramar, especification_line);
   num_of_non_terminals_ = std::stoi(especification_line);
  for (int i{0}; i < num_of_non_terminals_; i++) {
    std::getline(input_gramar, especification_line);
    non_terminals_.emplace(especification_line[0]);
  }
  std::getline(input_gramar, especification_line);
  num_of_productions_ = std::stoi(especification_line);
  for (int i{0}; i < num_of_productions_; i++) {
    std::getline(input_gramar, especification_line);
    std::istringstream aux(especification_line);
    char non_terminal;
    std::string production;
    aux >> non_terminal >> production;
    if (non_terminals_.find(non_terminal) == non_terminals_.end()) {
      std::cout << "El terminal: " << non_terminal << " no ha sido especificado" << std::endl;
      exit(-1);
    }
    if (islower(non_terminal)) {
      std::cout << "Un terminal no puede tener producciones." << std::endl;
      exit(-1);
    }
    if (production == "&") {
      std::cout << "No puede existir producciones unitarias o vacias" << std::endl;
      exit(-1);
    }
    productions_.emplace(non_terminal, production);
  }
}


/**
 * @brief Generates a new non-terminal character that is not already in the set of non-terminals.
 * 
 * This function takes a character as input and generates a new non-terminal character by 
 * incrementing the input character and ensuring that the new character is not already present 
 * in the set of non-terminals. The new non-terminal character is then added to the set.
 * 
 * @param c The input character from which to generate a new non-terminal.
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

void Grammar::PrimeraParte() {
  // Map to store terminal to non-terminal mappings
  std::map<char, char> terminal_to_non_terminal;

  for (auto it = productions_.begin(); it != productions_.end(); ++it) {
    std::string production = it->second;
    std::string new_production;
    if (production.size() > 1) {
      for (char& c : production) {
        if (islower(c)) {
          if (terminal_to_non_terminal.find(c) == terminal_to_non_terminal.end()) {
            // Generate a new non-terminal for this terminal
            char new_non_terminal = GenerateNonTerminal(c);
            terminal_to_non_terminal[c] = new_non_terminal;
            // Add the new production to the set
            if (productions_.find(new_non_terminal) == productions_.end()) {
              productions_.emplace(new_non_terminal, std::string(1, c));
              num_of_productions_++;
            }
          }
          // Replace terminal with its corresponding non-terminal
          new_production += terminal_to_non_terminal[c];
        } else {
          new_production += c;
        }
      }
  
      // Update the production with the new production string
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

  for (auto it = productions_.begin(); it != productions_.end(); ++it) {
    std::string production = it->second;
    if (production.size() >= 3) {
      char A = it->first;
      std::vector<char> new_non_terminals;

      // Generate m - 2 new non-terminal symbols S -> AXBX
      for (long unsigned int i = 0; i < production.size() - 2; ++i) {
        new_non_terminals.push_back(GenerateNonTerminal(A));
      }

      // Replace the production A → B1B2 . . . Bm with the new productions
      new_productions[A] = std::string(1, production[0]) + new_non_terminals[0];
      for (long unsigned int i = 0; i < new_non_terminals.size() - 1; ++i) {
        new_productions[new_non_terminals[i]] = std::string(1, production[i + 1]) + new_non_terminals[i + 1];
      }
      new_productions[new_non_terminals.back()] = std::string(1, production[production.size() - 2]) + std::string(1, production.back());

      // Remove the original production
      it = productions_.erase(it);
      --it;
    }
  }

  // Add the new productions to the grammar
  for (const auto& prod : new_productions) {
    productions_.emplace(prod.first, prod.second);
    num_of_productions_++;
  }
}


void Grammar::Write(const std::string& output_file) {
  std::ofstream output_grammar(output_file);
  output_grammar << num_of_terminals_  << std::endl;
  for (auto it = terminals_.begin(); it != terminals_.end(); it++) output_grammar << *it << std::endl;
  output_grammar << num_of_non_terminals_ << std::endl;
  for (auto it = non_terminals_.begin(); it != non_terminals_.end(); it++) output_grammar << *it << std::endl;
  output_grammar << num_of_productions_ << std::endl;
  for (auto it = productions_.begin(); it != productions_.end(); it++) output_grammar << it->first << " -> " << it->second << std::endl;
}

  /** Investigar si se puede hacer esto y luego getlines 
  char simbol_of_alphabet;
  std::string alphabet;
  input_gramar >> num_of_terminals_;
  for (int i{0}; i < num_of_terminals_; i++) {
    input_gramar >> simbol_of_alphabet;
    alphabet += simbol_of_alphabet; 
  }
  **/ 