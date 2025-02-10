#include "BigInteger.h"


// Constructores


BigInteger::BigInteger(int n) {
  unsigned n_abs = abs(n);
  if (n < 0) signo_ = true;
  else signo_ = false;
  numero_ = BigUnsigned(n_abs);
}

BigInteger::BigInteger(const unsigned char* n) {
  if (n[0] == '-') signo_ = true;
  else signo_ = false;

  // Quitamos el caracter '-' si lo hubiera
  if (signo_) n++;
  numero_ = BigUnsigned(n);
  
}

BigInteger::BigInteger(const BigInteger& other) {
  numero_ = other.numero_;
  signo_ = other.signo_;
}

BigInteger::BigInteger(const BigUnsigned& other) {
  numero_ = other;
  signo_ = false;
}

// Operadores de asignacion

BigInteger BigInteger::operator=(const BigInteger& other) {
  if (this != &other) {
    numero_ = other.numero_;
    signo_ = other.signo_;
  }
  return *this;
}

// Inserccion y extraccion de flujo

std::ostream& operator<<(std::ostream& os, const BigInteger& bi) {
  if (bi.signo_) os << '-';
  os << bi.numero_;
  return os;
}

std::istream& operator>>(std::istream& is, BigInteger& bi) {
  std::string str;
  is >> str;
  if (str[0] == '-') {
    bi.signo_ = true;
    str = str.substr(1); // Quitamos el signo
  } else {
    bi.signo_ = false;
  }
  bi.numero_ = BigUnsigned(reinterpret_cast<const unsigned char*>(str.c_str()));
  return is;
}

// Operadores de incremento y decremento

BigInteger& BigInteger::operator++() {
  BigUnsigned zero;
  if (signo_) {
    if (numero_ == zero) signo_ = false;
    else numero_ = numero_ - 1;
  } else {
    numero_ = numero_ + 1;
  }
  return *this;
}

BigInteger BigInteger::operator++(int) {
  BigInteger temp(*this);
  ++(*this);
  return temp;
}

BigInteger& BigInteger::operator--() {
  BigUnsigned zero;
  if (signo_) {
    numero_ = numero_ + 1;
  } else {
    if (numero_ == zero) signo_ = true;
    else numero_ = numero_ - 1;
  }
  return *this;
}

BigInteger BigInteger::operator--(int) {
  BigInteger temp(*this);
  --(*this);
  return temp;
}

// Operadores aritméticos

BigInteger operator+(const BigInteger& bi1, const BigInteger& bi2) {
  BigInteger res;
  BigUnsigned zero;
  // Caso 1: Los dos números tienen el mismo signo
  if (bi1.signo_ == bi2.signo_) {
    res.numero_ = bi1.numero_ + bi2.numero_;
    res.signo_ = bi1.signo_;
  } else {
    if (bi1.numero_ == bi2.numero_) {
      res.numero_ = zero;
      res.signo_ = false;
    } else if 
    
  }
  return res;
}