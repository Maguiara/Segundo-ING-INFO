// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 6: Diseño e implementación de un simulador de autómatas finitos
// Autor: Daniel Martínez Sopo
// Correo: alu0101675893@ull.edu.es
// Fecha: 19/10/2024
// Archivo Alphabet.cc: Contiene las implementaciones de métodos de la clase Alphabet.
// Historial de revisiones
// 19/10/2024 - Creación (primera versión) del código

#include "AlphabetDani.h"


/**
 * @brief Constructor que inicializa un objeto Alphabet con una cadena de símbolos.
 * 
 * Este constructor toma una cadena como entrada y agrega cada carácter de
 * la cadena a un set de símbolos, asegurando que cada símbolo sea único.
 * También actualiza el tamaño del alfabeto.
 *
 * @param alphabet Cadena que representa los símbolos del alfabeto.
 */
Alphabet::Alphabet(const std::string& alphabet){  
  for (char c : alphabet){
    if (c != ' ') // Ignorar espacios
      symbols_.insert(c);
  }
  size_ = symbols_.size();
}


/**
 * @brief Devuelve el tamaño del alfabeto.
 * 
 * @return El número de símbolos únicos en el alfabeto.
 */
int Alphabet::get_size(){
  return size_;
}


/**
 * @brief Limpia el alfabeto, eliminando todos los símbolos.
 * 
 * Esta función vacía el conjunto de símbolos y restablece el tamaño
 * a cero.
 */
void Alphabet::clear(){
  symbols_.clear();
  size_ = 0;
}

/**
 * @brief Verifica si un símbolo está presente en el alfabeto.
 * @param c El símbolo que se quiere buscar en el alfabeto.
 * @return true si el símbolo está presente en el alfabeto.
 * @return false si el símbolo no está presente en el alfabeto.
 */
bool Alphabet::find(char c){
  return symbols_.find(c) != symbols_.end();
}

/**
 * @brief Sobrecarga del operador de salida para imprimir el alfabeto.
 * 
 * Esta función permite imprimir un objeto de tipo Alphabet en un flujo
 * de salida de manera legible. Los símbolos se separan por comas
 * y se encierran entre llaves. En caso de ser un alfabeto creado por 
 * el constructor por defecto que no fue cargado con ningún símbolo,
 * no imprimirá nada, pues no puede existir un alfabeto vacío.
 * 
 * @param os Flujo de salida donde se imprimirá el alfabeto.
 * @param alphabet Objeto Alphabet que se va a imprimir.
 * @return Referencia al flujo de salida.
 */
std::ostream& operator<<(std::ostream& os, const Alphabet& alphabet) {
  if(alphabet.size_ == 0) os << "";
  else {
    os << "{";
    bool first = true;  
    for (char c : alphabet.symbols_) {
      if (!first) {
        os << ", ";  
      }
      os << c;
      first = false;  
    }
    os << "}";
  }  
  return os;
}


/**
 * @brief Sobrecarga del operador de entrada para leer un alfabeto desde un flujo.
 * 
 * Esta función permite leer una cadena de símbolos desde un flujo de entrada
 * y almacenarla en un objeto Alphabet. Cada carácter leído se agrega al conjunto
 * de símbolos.
 * 
 * @param is Flujo de entrada desde el que se leerá el alfabeto.
 * @param alphabet Objeto Alphabet que se va a rellenar.
 * @return Referencia al flujo de entrada.
 */
std::istream& operator>>(std::istream& is, Alphabet& alphabet) {
  std::string aux;
  is >> aux;
  for (char c : aux){
    alphabet.symbols_.insert(c);
  }
  alphabet.size_ = alphabet.symbols_.size();
  return is;
}


