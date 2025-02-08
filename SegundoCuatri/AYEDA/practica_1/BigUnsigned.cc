#include "BigUnsigned.h"


// Constructores de la clase


BigUnsigned::BigUnsigned(unsigned n) {
  while (n > 10) {
    digitos_.push_back((n % 10) + '0'); // Almaenarlo como char en vez de int
    n /= 10;
  }
  digitos_.push_back(n + '0');
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
  if (bu1.digitos_ == bu2.digitos_) {
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
  std::string totalSum;
  int carry = 0;
  int i = 0;
  while (i < bu1.digitos_.size() || i < bu2.digitos_.size() || carry > 0) {
    int suma = carry;
    if (i < bu1.digitos_.size()) {
      suma += bu1.digitos_[i] - '0';
    }
    if (i < bu2.digitos_.size()) {
      suma += bu2.digitos_[i] - '0';
    }
    totalSum.push_back(suma % 10 + '0');
    carry = suma / 10;
    i++;
  }
  return BigUnsigned((unsigned char*)totalSum.c_str());
}

// Operador de la resta
BigUnsigned BigUnsigned::operator-(const BigUnsigned& other) const {
  BigUnsigned res;
  if (*this < other) return res;
  res.digitos_.clear();
  int carry = 0;
  for (int i = 0; i < digitos_.size(); i++) {
    int diff = (digitos_[i] - '0') - (i < other.digitos_.size() ? (other.digitos_[i] - '0') : 0) + carry;
    if (diff < 0) {
      diff += 10;
      carry = -1;
    } else {
      carry = 0;
    }
    //std::cout << "diff: " << diff << std::endl; Debugear codigo
    res.digitos_.push_back(diff + '0');
  }
  while (res.digitos_.size() > 1 && res.digitos_.back() == '0') {
    res.digitos_.pop_back();
  }
  return res;
}


// Operador de la multiplicación

BigUnsigned BigUnsigned::operator*(const BigUnsigned& other) const {
  BigUnsigned res;
  BigUnsigned smaller = *this < other ? *this : other;
  BigUnsigned larger = *this < other ? other : *this;
  for (BigUnsigned i; i < smaller; ++i) {
    res = res + larger;
  }
  return res;
}

// Operador de la división

BigUnsigned operator/(const BigUnsigned& bu1, const BigUnsigned& bu2) {
  BigUnsigned res;
  BigUnsigned temp = bu1;
  while (bu2 < temp || bu2 == temp) {
    temp = temp - bu2;
    res = res + 1;
  }
  return res;
}

// Operador del módulo

BigUnsigned BigUnsigned::operator%(const BigUnsigned& other) const {
  BigUnsigned res;
  BigUnsigned temp = *this;
  while (other < temp || other == temp) {
    temp = temp - other;
  }
  return temp;
}