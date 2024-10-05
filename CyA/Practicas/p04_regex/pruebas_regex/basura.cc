#include <iostream>
#include <regex>
#include <string>
#include <fstream>

int main() {
    std::string line = "int factorial = 1;";
    std::regex variableRegex(R"((int|double)\s+(\w+)\s*=\s*([\w\d\.]+)\s*;)");
    std::smatch match;

    if (std::regex_search(line, match, variableRegex)) {
        std::string varType = match[1].str();    // Captura el tipo (int o double)
        std::string varName = match[2].str();    // Captura el nombre de la variable
        std::string varValue = match[3].str();   // Captura el valor de la variable

        std::cout << "Tipo: " << varType << "\n";
        std::cout << "Nombre: " << varName << "\n";
        std::cout << "Valor: " << varValue << "\n";
    }

    return 0;
}
