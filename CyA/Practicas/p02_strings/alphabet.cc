 
 
 
 
#include "tools.h" 
#include "alphabet.h"


//Constructor parametrizado de la clase alphabet
Alphabet::Alphabet(const std::string& user_alphabet) {
  for (char c : user_alphabet) {
    my_alphabet_.insert(c);
  }
} 

//Sobrecarga del operador de flujo de salida
std::ostream& operator<<(std::ostream& out, const Alphabet& user_alphabet) {
  out << "{"; 
  for (auto it = user_alphabet.my_alphabet_.begin(); it != user_alphabet.my_alphabet_.end(); ++it) {
    out << *it;
    if (std::next(it) != user_alphabet.my_alphabet_.end()) {
      out << ", ";  // Para añadir la coma entre los elementos
    }
  }
  out << "}";
  return out;
}

std::istream& operator>>(std::istream& in, Alphabet& user_alphabet) {
  std::string user_input;
  in >> user_input; // Leemos el alfabeto como una string 
  user_alphabet.my_alphabet_.clear(); // Nos aseguramos de que el SET esta vacio
   for (char c : user_input) {
    user_alphabet.my_alphabet_.insert(c);
  }
  return in;
}

