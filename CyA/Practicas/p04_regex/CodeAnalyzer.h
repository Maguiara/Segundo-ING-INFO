/**
 * @file CodeAnalyzer.h
 * @brief Declaración de la clase CodeAnalyzer para el análisis de código.
 * Contiene la definición de la clase y sus métodos para analizar archivos de código.
 * 
 * @details
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Computabilidad y Algoritmia
 * Curso: 2º
 * Práctica 4: Análisis de código con expresiones regulares
 * 
 * @date 19/09/2024
 * @note Correo: alu0101620961@ull.edu.es
 */

#include "tools.h"
#include "variableHandler.h"
#include "loopsHandler.h"
#include "commentHandler.h"
class CodeAnalyzer {
public:

    //Getters
    bool get_hasMain() const {return has_main_;}
    std::string get_description() const {return description_; }
    //Funciones para analizar el codigo e imprimir la salida
    void ReadDescription (const std::string& inputfile);
    void Analyze(const std::string& inputFile, const std::string& outputFile);
    void WriteOutput(const std::string& inputFile, const std::string& outputFile, variableHandler& variables, loopsHandler& loops, commentHandler& comments);

private:
    //Metodos que no son parte de la interfaz publica de la clase
    void AnalyzeVariables(const std::string& line, int lineNumber, variableHandler& variables);
    void AnalyzeLoops(const std::string& line, int& lineNumber,  std::ifstream& input, loopsHandler& loops);
    void DetectMain(const std::string& line);
    void AnalyzeComments(const std::string& line, int& lineNumber, std::ifstream& input, commentHandler& comments);
    bool has_main_ = false;
    std::string description_;
};



