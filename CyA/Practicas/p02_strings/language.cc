


#include "tools.h"
#include "language.h"


void Language::Prefix(MyString& user_string) {
  std::string aux = user_string.my_string(); //Para poder aplicar los metodos de la libreria string de C++
  std::string current_prefix;
  my_language_.push_back("&"); //Añadimos la cadena vacia al inicio
  for (int i{0}; i < aux.length(); ++i) {
    current_prefix  += aux[i];
    my_language_.push_back(current_prefix);
  }
}

void Language::Sufix(MyString& user_string) {
  std::string aux = user_string.my_string(); //Para poder aplicar los metodos de la libreria string de C++
  std::string current_sufix;
  my_language_.push_back("&"); //Añadimos la cadena vacia al inicio
  for (int i = aux.length() - 1; i >= 0; --i) {
    current_sufix = aux[i] + current_sufix;
    my_language_.push_back(current_sufix);
  }
}


std::ostream& operator<<(std::ostream& out, const Language& user_language) {
  out << "{";
  bool first = true;
  for (const auto cad: user_language.my_language_) {
    if(!first) {
      out << ", ";
    }
    out << cad;
    first = false; 
  }
  out << "}";
  return out;
}