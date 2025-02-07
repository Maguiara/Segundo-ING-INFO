#ifndef BIGUNSIGNEG_H
#define BIGUNSIGNED_H


#include "tools.h"
class BigUnsigned {
 public:
  //Constructores
  BigUnsigned(unsigned n = 0);
  BigUnsigned(const unsigned char* );
  BigUnsigned(const BigUnsigned&); // Constructor de copia

  //Asignacion
  BigUnsigned operator=(const BigUnsigned&);
  
  // Inserccion y extraccion de flujo
  friend std::ostream& operator<<(std::ostream&, const BigUnsigned&);
  friend std::istream& operator>>(std::istream&, BigUnsigned&);

  //Comparacion
  bool operator==(const BigUnsigned&) const;
  friend bool operator<(const BigUnsigned&, const BigUnsigned&);

  //Incremento/decremento
  BigUnsigned& operator++(); // Pre-incremento
  BigUnsigned operator++(int); // Post-incremento
  BigUnsigned& operator--(); // Pre-decremento
  BigUnsigned operator--(int); // Post-decremento
  
  //Operadores aritméticos
  friend BigUnsigned operator+(const BigUnsigned&, const BigUnsigned&);
  BigUnsigned operator-(const BigUnsigned&) const;
  BigUnsigned operator*(const BigUnsigned&) const;
  friend BigUnsigned operator/(const BigUnsigned&, const BigUnsigned&);
  BigUnsigned operator%(const BigUnsigned&) const;

 private: 
  std::vector<unsigned char> digitos_;
}; 


#endif