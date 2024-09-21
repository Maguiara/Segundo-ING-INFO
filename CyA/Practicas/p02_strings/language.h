 // Universidad de La Laguna
 // Escuela Superior de Ingeniería y Tecnología
 // Grado en Ingeniería Informática
 // Asignatura: Computabilidad y Algoritmia
 // Curso: 2º
 // Práctica 2: Cadenas y lenguajes
 // Autor: Marco Aguiar Álvarez
 // Correo: alu0101620961@ull.edu.es
 // Fecha: 19/09/2024
 // Archivo language.h: Archivo que contiene la declaracion de la clase "Lenguaje"
 // Contiene la definicion de las funciones herramienta contenidas en el programa
 // para indicar al usuario el correcto funcionamiento del codigo
 // Historial de revisiones
 // 17/09/2024- Creación (primera versión) del código
#include "tools.h"

class Language {
 public:
	void Prefix(MyString user_string);
	void Sufix(MyString user_string);
	friend std::istream operator>>(std::istream in, Language& user_language);
	friend std::ostream operator<<(std::ostream out, const Language& user_language);
 private:
  std::set <MyString> my_language_;
};