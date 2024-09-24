/**
 * @file mystring.cc
 * @brief Implementación de la clase MyString y sus métodos.
 * Contiene la implementación de la clase MyString, sus constructores, getters,
 * métodos y sobrecargas de operadores.
 * 
 * @details
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Computabilidad y Algoritmia
 * Curso: 2º
 * Práctica 2: Cadenas y lenguajes
 * 
 * @author Marco Aguiar Álvarez
 * @date 19/09/2024
 * @note Correo: alu0101620961@ull.edu.es
 */ 

 #include "mystring.h"
 #include "tools.h" 


/**
 * @brief Constructor de la clase MyString.
 *
 * Este constructor inicializa un objeto MyString con una cadena proporcionada por el usuario.
 * Si la cadena proporcionada es "&", el tamaño se establece en 0. De lo contrario, el tamaño
 * se establece en la longitud de la cadena proporcionada.
 *
 * @param user_string La cadena de caracteres proporcionada por el usuario para inicializar el objeto MyString.
 */
 MyString::MyString(const std::string& user_string) {
  my_string_ = user_string;
  (user_string == "&") ? size_ = 0 : size_ = user_string.length(); 
 }


/**
 * @brief Devuelve el tamaño de la cadena almacenada en el objeto MyString.
 *
 * Esta función retorna el tamaño de la cadena `my_string_`. Si la cadena es "&",
 * se considera que su tamaño es 0.
 *
 * @return El tamaño de la cadena `my_string_` como un entero.
 */
int MyString::getSize() const {
  return (my_string_ == "&") ? 0 :my_string_.length();
}

/**
 * @brief Invierte la cadena almacenada en el objeto MyString.
 *
 * Intercambia los caracteres desde ambos extremos hacia el centro.
 */
void MyString::Invert() {
  int aux_length = my_string_.length(); //evitamos que salte la FLAG -Wall al comparar un int (i) con un long unsigned int (my_string_.length()) directamente
  for (int i{0}; i < aux_length / 2; i++) {
    std::swap(my_string_[i], my_string_[my_string_.length() - 1 - i]);
  }
}


/**
 * @brief Sobrecarga del operador < para comparar dos objetos MyString.
 *
 * Esta función compara dos objetos MyString. Si las longitudes de las cadenas
 * son iguales, se comparan alfanumericamente. Si las longitudes son diferentes,
 * se compara en base a la longitud de las cadenas.
 *
 * @param other El objeto MyString con el que se va a comparar.
 * @return true si el objeto actual es menor que el objeto other.
 * @return false en caso contrario.
 */
bool MyString::operator<(const MyString& other) const {
  return (my_string_.length() == other.my_string_.length()) ? my_string_ < other.my_string_ : my_string_.length() < other.my_string_.length();
}


/**
 * @brief Sobrecarga del operador de extracción >> para la clase MyString.
 *
 * Esta función permite leer una cadena de caracteres desde un flujo de entrada
 * y almacenarla en un objeto de la clase MyString.
 *
 * @param in Flujo de entrada desde el cual se leerá la cadena de caracteres.
 * @param user_string Objeto de la clase MyString donde se almacenará la cadena leída.
 * @return Referencia al flujo de entrada, permitiendo el encadenamiento de operaciones.
 */
std::istream& operator>>(std::istream& in, MyString& user_string) {
  in >> user_string.my_string_;
  return in;
}


/**
 * @brief Sobrecarga del operador de inserción << para la clase MyString.
 *
 * Esta función permite imprimir el contenido de un objeto MyString en un flujo de salida.
 *
 * @param out Referencia al flujo de salida (std::ostream) donde se imprimirá el contenido.
 * @param user_string Referencia constante al objeto MyString cuyo contenido se va a imprimir.
 * @return Referencia al flujo de salida (std::ostream) después de insertar el contenido del objeto MyString.
 */
std::ostream& operator<<(std::ostream& out, const MyString& user_string) {
  out << user_string.my_string_;
  return out;
} 