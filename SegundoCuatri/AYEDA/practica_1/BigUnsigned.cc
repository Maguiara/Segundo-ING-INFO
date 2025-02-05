#include "BigUnsigned.h"

BigUnsigned::BigUnsigned(unsigned n = 0) {
  while (n > 0) {
    digitios_.push_back(n % 10);
    n /= 10;
  }
}

BigUnsigned::BigUsigned(const unsigned char* str) {
 
}

BigUnsigned::BigUnsigned(const BigUnsigned& other) : digitos_(other.digitos_) {}