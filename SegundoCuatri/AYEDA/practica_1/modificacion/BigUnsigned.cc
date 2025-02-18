#include "BigUnsigned.h"
#include <cstring> 


// Constructores de la clase

int globalContador = 0;

BigUnsigned::BigUnsigned(unsigned n) {
  while (n > 10) {
    digitos_.push_back((n % 10) + '0'); // Almaenarlo como char en vez de int
    n /= 10;
  }
  digitos_.push_back(n + '0');
}


BigUnsigned::BigUnsigned(const unsigned char* str) {
  int len = strlen(reinterpret_cast<const char*>(str));
  for (int i = len - 1; i >= 0; i--) {
    if (!isdigit(str[i])) {
      std::cerr << "Error: el string no es un número" << std::endl;
      return;
    }
    digitos_.push_back(str[i]);
  }
}

BigUnsigned::BigUnsigned(const BigUnsigned& other) : digitos_(other.digitos_) {}


// Operador de asignación

BigUnsigned BigUnsigned::operator=(const BigUnsigned& other) {
  if (this != &other) {
    digitos_ = other.digitos_;
  }
  return *this;
}

// Operadores de inserción y extracción de flujo

std::ostream& operator<<(std::ostream& os, const BigUnsigned& bu) {
  for (int i = bu.digitos_.size() - 1; i >= 0; i--) {
    os << bu.digitos_[i] - '0';
  }
  return os;
}


std::istream& operator>>(std::istream& is, BigUnsigned& bu) {
  std::string str;
  is >> str;
  bu.digitos_.clear();
  for (int i = str.size() - 1; i >= 0; i--) {
    bu.digitos_.push_back(str[i]);
  }
  return is;
}

// Operadores de comparación

bool BigUnsigned::operator==(const BigUnsigned& other) const {
 return digitos_ == other.digitos_;
}

bool operator<(const BigUnsigned& bu1, const BigUnsigned& bu2) {
  if (bu1.digitos_.size() != bu2.digitos_.size()) return bu1.digitos_.size() < bu2.digitos_.size();
  for (int i = bu1.digitos_.size() - 1; i >= 0; i--) {
    if (bu1.digitos_[i] != bu2.digitos_[i]) return bu1.digitos_[i] < bu2.digitos_[i];
  }
  return false;
}

// Operadores de incremento y decremento

// Pre-incremento
BigUnsigned& BigUnsigned::operator++() {
  *this = *this + 1;
  return *this;
}

// Post-incremento
BigUnsigned BigUnsigned::operator++(int) {
  BigUnsigned temp(*this);
  ++(*this);
  return temp;
}

// Pre-decremento
BigUnsigned& BigUnsigned::operator--() {
  *this = *this - 1;
  return *this;
}

// Post-decremento
BigUnsigned BigUnsigned::operator--(int) {
  BigUnsigned temp(*this);
  --(*this);
  return temp;
}


// Operadores aritméticos

// Operador de la suma
BigUnsigned operator+(const BigUnsigned& bu1, const BigUnsigned& bu2) {
  BigUnsigned totalSum;
  totalSum.digitos_.clear();
  int carry = 0;
  int i = 0;
  while (i < bu1.digitos_.size() || i < bu2.digitos_.size() || carry > 0) {
    int suma = carry;
    if (i < bu1.digitos_.size()) suma += bu1.digitos_[i] - '0';
    if (i < bu2.digitos_.size()) suma += bu2.digitos_[i] - '0';
    totalSum.digitos_.push_back((suma % 10) + '0');
    carry = suma / 10;
    i++;
  }
  return totalSum;
}

// Operador de la resta
BigUnsigned BigUnsigned::operator-(const BigUnsigned& other) const {
  BigUnsigned res;
  if (*this < other) return res;
  res.digitos_.clear();
  int carry = 0;
  int i = 0;
  while (i < digitos_.size() || i < other.digitos_.size() || carry != 0) {
    int resta = carry;
    if (i < digitos_.size()) resta += digitos_[i] - '0';
    if (i < other.digitos_.size()) resta -= other.digitos_[i] - '0';
    if (resta < 0) {
      resta += 10;
      carry = -1;
    } else {
      carry = 0;
    }
    res.digitos_.push_back(resta + '0');
    i++;
  } 
  while (res.digitos_.size() > 1 && res.digitos_.back() == '0') {
    res.digitos_.pop_back();
  }
  return res;
}


// Operador de la multiplicación
BigUnsigned BigUnsigned::operator*(const BigUnsigned& other) const {
  BigUnsigned zero;
  if (*this == zero|| other == zero) return zero; // Caso de que alguno de los dos sea 0

  BigUnsigned smaller = *this < other ? *this : other;
  BigUnsigned larger = *this < other ? other : *this;
  BigUnsigned res, iterador; // Empieza en 0, 
  while (!(iterador == smaller)) { // Por lo que esto hara las iteraciones necesarias por que llegaria smaller - 1
    res = res + larger;
    ++iterador;
  }
  return res;
}

// Operador de la división
BigUnsigned operator/(const BigUnsigned& bu1, const BigUnsigned& bu2) {
  BigUnsigned zero;

  if (bu2 == zero) return zero; // Caso de que el divisor sea 0
  if (bu1 < bu2) return zero; // Caso de que el dividendo sea menor que el divisor

  BigUnsigned temp = bu1;
  BigUnsigned res;
  while (bu2 < temp || bu2 == temp) {
    temp = (temp - bu2);
    res++;
  }
  return res;
}

// Operador del módulo
BigUnsigned BigUnsigned::operator%(const BigUnsigned& other) const {
  BigUnsigned zero;
  if (other == zero) return zero; // Caso de que el divisor sea 0 
  BigUnsigned temp = *this;
  int contador = 0;
  while (other < temp || other == temp) {
    temp = (temp - other);
    contador++;
  }
  contadorAcumulado_ += contador;
  return temp;
}
