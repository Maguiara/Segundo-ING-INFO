

#include "tools.h"
#include "BigUnsigned.h"


int main () {
  unsigned numero = 1234;
  BigUnsigned bu(numero);
  BigUnsigned bu2 = bu;
  BigUnsigned bu3;
  std::cin >> bu3;

  std::cout << "El numero es: " << bu << std::endl;
  std::cout << "El numero copiado es: " << bu2 << std::endl;
  std::cout << "El numero introducido es: " << bu3 << std::endl;
  if (bu == bu3) std::cout << "Son iguales" << std::endl;
  else std::cout << "No son iguales" << std::endl;

  if (bu < bu3) std::cout << "El numero " << bu << " es menor que " << bu3 << std::endl;
  else std::cout << "El numero " << bu << " es mayor que " << bu3 << std::endl; 
}