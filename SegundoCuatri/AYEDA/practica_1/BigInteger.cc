#include "BigInteger.h"


// Constructores


BigInteger::BigInteger(int n) {
  if (n < 0) {
    signo_ = true;
    n = -n;
  } else {
    signo_ = false;
  }
  numero_ = BigUnsigned(n);
}

BigInteger::BigInteger(const unsigned char* n) {
  numero_ = BigUnsigned(n);
  signo_ = false;
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
    str = str.substr(1);
  } else {
    bi.signo_ = false;
  }
  bi.numero_ = BigUnsigned(reinterpret_cast<const unsigned char*>(str.c_str()));
  return is;
}