/** 
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Computabilidad y Algoritmia
 * 
 * @brief Este programa calcula la suma de los primeros n números naturales.
 * @version 1.0
 * 
 * @see https://github.com/ULL-2024-2025/Code-Examples
 */

#include <iostream>

// Función que calcula la suma de los primeros n números naturales
int SumaNaturales(int n) {
    int suma = 0;
    double hola;
    for (int i = 1; i <= n; ++i) {
        suma += i;
    }
    return suma;
}

int main() {
    int numero;
    double adios = 3.2;
    std::cout << "Introduce un número: ";
    std::cin >> numero;

    /**comentario multilina para 
     * probar lo de la descripcion
     */

    // Calcula y muestra la suma de los primeros 'numero' naturales
    std::cout << "La suma de los primeros " << numero << " números naturales es: "
              << SumaNaturales(numero) << std::endl;

    return 0;
}
