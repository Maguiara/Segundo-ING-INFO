
#include <iostream>
#include <vector>

int main () {

  int numero = 1234;
  std::vector<int> digitos;
  while (numero > 0) {
    digitos.push_back(numero % 10);
    numero /= 10;
  }

  for (int i : digitos) {
    std::cout << i << " ";
  }
}