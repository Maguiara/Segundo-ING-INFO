 // Universidad de La Laguna
 // Escuela Superior de Ingeniería y Tecnología
 // Grado en Ingeniería Informática
 // Asignatura: Computabilidad y Algoritmia
 // Curso: 2º
 // Práctica 2: Cadenas y lenguajes
 // Autor: Marco Aguiar Álvarez
 // Correo: alu0101620961@ull.edu.es
 // Fecha: 19/09/2024
 // Archivo tools.cc: programa de herramientas.
 // Contiene la definicion de las funciones herramienta contenidas en el programa
 // para indicar al usuario el correcto funcionamiento del codigo
 // Historial de revisiones
 // 17/09/2024- Creación (primera versión) del código

#include "tools.h"

class Alphabet {
 public:
  Alphabet() = default;
  Alphabet(const std::string& user_alphabet) {}
  friend std::istream& operator>>(std::istream in, Alphabet& user_alphabet);
  friend std::ostream& operator<<(std::ostream out, const Alphabet& user_alphabet);
 private:
	std::set<char> my_alphabet_;
};