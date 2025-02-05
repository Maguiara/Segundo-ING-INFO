#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include "tools.h"
#include "BigUnsigned.h"

class BigInteger {
 public:
  
  //Constructores
  BigInteger(int n = 0);
  BigInteger(const unsigned char* );
  BigInteger(const BigInteger&); // Constructor de copia
  BigInteger(const BigUnsigned&); //Constructor de cambio de tipo


  //Asignacion
  BigInteger operator=(const BigInteger&);
  
  // Inserccion y extraccion de flujo
  friend std::ostream& operator<<(std::ostream&, const BigInteger&);
  friend std::istream& operator>>(std::istream&, BigInteger&);

  //Comparacion
  bool operator==(const BigInteger&) const;
  friend bool operator<(const BigInteger&, const BigInteger&);

  //Incremento/decremento
  BigInteger& operator++(); // Pre-incremento
  BigInteger operator++(int); // Post-incremento
  BigInteger& operator--(); // Pre-decremento
  BigInteger operator--(int); // Post-decremento
  
  //Operadores aritméticos
  friend BigInteger operator+(const BigInteger&, const BigInteger&);
  BigInteger operator-(const BigInteger&) const;
  BigInteger operator*(const BigInteger&) const;
  friend BigInteger operator/(const BigInteger&, const BigInteger&);
  BigInteger operator%(const BigInteger&) const;

 private: 
  std::vector<unsigned char> digitios_;
}; 

#endif