 // Universidad de La Laguna
 // Escuela Superior de Ingeniería y Tecnología
 // Grado en Ingeniería Informática
 // Asignatura: Computabilidad y Algoritmia
 // Curso: 2º
 // Práctica 2: Cadenas y lenguajes
 // Autor: Marco Aguiar Álvarez
 // Correo: alu0101620961@ull.edu.es
 // Fecha: 19/09/2024
 // Archivo Mystring.cc : Archivo que contiene las definiciones de la clase "cadena".
 // Contiene la definion de la clase cadena junto con las definiciones de los metodos de la misma 
 // Historial de revisiones
 // 19/09/2024- Creación (primera versión) del código
 // 20/09/2024- Creacion de las clases "cadena", "lenguaje", y "alfabeto" con la definicion de sus metodos privados

 #include "tools.h" 

void MyString::Invert() {
  for (int i{0}; i <= size()/2; i++) {
    std::swap(my_string_[i], my_string_[(my_string_.length() - 1) - i]);
  }
}



std::istream& operator>>(std::istream& in, MyString& user_string) {
  in >> user_string.my_string_;
  return in;
}


std::ostream& operator<<(std::ostream& out, const MyString& user_string) {
  out << user_string.my_string_;
  return out;
} 