
#include <iostream>
#include <vector>

int main () {

unsigned int input;
std::vector<unsigned int> vec;

std::cout << "Introduce un unsigned char: ";
std::cin >> input;

vec.push_back(input);

std::cout << "El vector contiene: ";
for (unsigned int& c : vec) {
    std::cout << c << " ";
}
std::cout << std::endl;
}