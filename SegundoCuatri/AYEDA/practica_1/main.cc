

#include "BigInteger.h"


int main () {
  // Pruebas de la clase BigUnsigned
  unsigned char numero [] = "80";
  // ------------------------------------
  
  // ------------------------------------
  BigUnsigned bu(numero);
  BigUnsigned bu2 = bu;
  BigUnsigned bu3;
  std::cout << "Introduce un numero (sin signo): ";
  std::cin >> bu3;
  unsigned char str[] = "123456789";
  BigUnsigned bu4(str);


  std::cout << "El numero es: " << bu << std::endl;
  std::cout << "El numero copiado es: " << bu2 << std::endl;
  std::cout << "El numero introducido es: " << bu3 << std::endl;
  std::cout << "El numero inicializado como cadena de caracteres es: " << bu4 << std::endl;
  std::cout << "Los numeros " << bu << " y " << bu3 << " ";
  if (bu == bu3) std::cout << "son iguales" << std::endl;
  else std::cout << "no son iguales" << std::endl;

  if (bu < bu3) std::cout << "El numero " << bu << " es menor que " << bu3 << std::endl;
  else std::cout << "El numero " << bu << " es mayor que " << bu3 << std::endl;

  ++bu;
  std::cout << "Incrementado (pre): " << bu << std::endl;
  bu++;
  std::cout << "Incrementado (post): " << bu << std::endl;

  --bu2;
  std::cout << "Decrementado (pre): " << bu2 << std::endl;
  bu2--;
  std::cout << "Decrementado (post): " << bu2 << std::endl;

  BigUnsigned suma = bu + bu3;
  std::cout << "La suma de " << bu << " y " << bu3 << " es: " << suma << std::endl;
  BigUnsigned resta = bu - bu3;
  std::cout << "La resta de " << bu << " y " << bu3 << " es: " << resta << std::endl;
  BigUnsigned mult = bu * bu3;
  std::cout << "La multiplicacion de " << bu << " y " << bu3 << " es: " << mult << std::endl;
  BigUnsigned div = bu / bu3;
  std::cout << "La division de " << bu << " y " << bu3 << " es: " << div << std::endl;
  BigUnsigned mod = bu % bu3;
  std::cout << "El modulo de " << bu << " y " << bu3 << " es: " << mod << std::endl;

  // Pruebas de la clase BigInteger
  int numero2 = 10;
  BigInteger bi(numero2);
  BigInteger bi2 = bi;
  BigInteger bi3;
  std::cout << "Introduce un numero (con signo): ";
  std::cin >> bi3;
  std::cout << "El numero es: " << bi << std::endl;
  std::cout << "El numero copiado es: " << bi2 << std::endl;
  std::cout << "El numero introducido es: " << bi3 << std::endl;

  //std::cout << "Los numeros " << bi << " y " << bi3 << " ";
  //if (bi == bi3) std::cout << "son iguales" << std::endl;
  //else std::cout << "no son iguales" << std::endl;
  //if (bi < bi3) std::cout << "El numero " << bi << " es menor que " << bi3 << std::endl;
  //else std::cout << "El numero " << bi << " es mayor que " << bi3 << std::endl;

  ++bi;
  std::cout << "Incrementado (pre): " << bi << std::endl;
  bi++;
  std::cout << "Incrementado (post): " << bi << std::endl;

  --bi2;
  std::cout << "Decrementado (pre): " << bi2 << std::endl;
  bi2--;
  std::cout << "Decrementado (post): " << bi2 << std::endl;

  BigInteger suma2 = bi + bi3;
  std::cout << "La suma de " << bi << " y " << bi3 << " es: " << suma2 << std::endl;
  /** BigInteger resta2 = bi - bi3;
  std::cout << "La resta de " << bi << " y " << bi3 << " es: " << resta2 << std::endl;
  BigInteger mult2 = bi * bi3;
  std::cout << "La multiplicacion de " << bi << " y " << bi3 << " es: " << mult2 << std::endl;
  BigInteger div2 = bi / bi3;
  std::cout << "La division de " << bi << " y " << bi3 << " es: " << div2 << std::endl;
  BigInteger mod2 = bi % bi3;
  std::cout << "El modulo de " << bi << " y " << bi3 << " es: " << mod2 << std::endl;
  */
}