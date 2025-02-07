#include "BigUnsigned.h"


// Constructores de la clase


BigUnsigned::BigUnsigned(unsigned n) {
  while (n > 0) {
    digitos_.push_back((n % 10) + '0'); // Almaenarlo como char en vez de int
    n /= 10;
  }
}

// Hay que arreglar este constructor
BigUnsigned::BigUnsigned(const unsigned char* str) {
  for (int i = 0; str[i] != '\0'; i++) {
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

// revisar esta funcion por que usar string es raro rarete
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
  if (bu1.digitos_.size() < bu2.digitos_.size()) {
    return true;
  }
  if (bu1.digitos_.size() > bu2.digitos_.size()) {
    return false;
  }
  for (int i = bu1.digitos_.size() - 1; i >= 0; i--) {
    if (bu1.digitos_[i] > bu2.digitos_[i]) {
      return false;
    }
  }
  return true;
}

// Operadores de incremento y decremento

