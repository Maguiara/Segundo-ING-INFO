/**
 * @file CodeAnalyzer_main.cc
 * @brief Implementación del archivo principal para el analizador de código.
 * Contiene la función principal que utiliza la clase CodeAnalyzer para analizar
 * archivos de código.
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

#include "CodeAnalyzer.h"

void CodeAnalyzer::ReadDescription(const std::string& inputfile) {
  std::ifstream input(inputfile);
  std::getline(input, description_);
  std::regex endCommentRegex(R"(\*\/)");
    // Seguir leyendo hasta encontrar el final del comentario
    while (!std::regex_search(description_, endCommentRegex)) {
        std::string nextLine;
        if (std::getline(input, nextLine)) {
            description_ += "\n" + nextLine;
        } else {
            break; // Fin del archivo
        }
    }
} 

/**
 * @brief Analiza un archivo de código fuente y genera un informe.
 *
 * @param inputfile Ruta del archivo de entrada.
 * @param outputfile Ruta del archivo de salida.
 */
void CodeAnalyzer::Analyze(const std::string& inputfile, const std::string& outputfile) {
  std::ifstream input(inputfile);

  //Lee la descripcion del archivo
  ReadDescription(inputfile);
  // Variables necesarias para el analisis del archivo
  std::string line;
  int lineNumber = 0;
  // Expresiones regulares para el analisis
  std::regex variableRegex(R"((int|double)\s+(\w+)\s*(?:=\s*([\w\d\.]+))?\s*\;)"); // Detecta tanto variables int como doubles inicializadas o no
  std::regex loopRegex(R"((for|while)\s*\(.*\)\s*\{)"); // Detecta los bucles
  std::regex mainRegex(R"(int\s+main\s*\()"); // Detecta el main
  std::regex singleLineCommentRegex(R"(\/\/.*)"); // Detecta los comentarios de una linea
  std::regex multiLineCommentRegex(R"(\/\*.*)"); // Detecta los inicios de comentarios multilinea
  std::smatch match;
  // Variables donde se guardara la informacion
  variableHandler variables;
  loopsHandler loops;
  commentHandler comments;

  // Leer el archivo línea por línea
  while (std::getline(input, line)) {
    lineNumber++;
    if (std::regex_search(line, loopRegex)) {
      AnalyzeLoops(line, lineNumber, input, loops);
    } else if (std::regex_search(line, variableRegex)) {
      AnalyzeVariables(line, lineNumber, variables);
    } else if (std::regex_search(line, singleLineCommentRegex) or std::regex_search(line, multiLineCommentRegex)) {
      AnalyzeComments(line, lineNumber, input, comments);
    } else if (std::regex_search(line, mainRegex)) {
      DetectMain(line); 
    }
  }

  WriteOutput(inputfile, outputfile, variables, loops, comments);
  input.close();
}


/**
 * @brief Escribe los resultados del análisis en un archivo de salida.
 *
 * Esta función toma el nombre de un archivo de entrada y un archivo de salida, y escribe
 * los resultados del análisis del archivo de entrada en el archivo de salida. Los resultados incluyen
 * el nombre del programa, variables, declaraciones, presencia de una función main y comentarios.
 *
 * @param inputFile El nombre del archivo de entrada que se está analizando.
 * @param outputFile El nombre del archivo donde se escribirán los resultados del análisis.
 */
void CodeAnalyzer::WriteOutput(const std::string& inputFile, const std::string& outputFile, variableHandler& variables, loopsHandler& loops, commentHandler& comments) {
  std::ofstream output(outputFile);
  output << "PROGRAM: " << inputFile << std::endl;

  output << "\n DESCRIPTION\n " << description_ << std::endl;

  output << "\n VARIABLES: \n";
  variables.PrintVariables(output); 

  output << "\n STATEMENTS: \n";
  loops.PrintLoops(output); 

  output << "\n MAIN: \n" << (has_main_ ? "True" : "False") << std::endl;

  output << "\n COMMENTS: \n"; 
  comments.PrintComments(output); 

}

/**
 * @brief Analiza una línea para encontrar declaraciones de variables.
 *
 * Busca variables de tipo entero y doble en la línea dada y las almacena en `variables_`.
 *
 * @param line La línea de código a analizar.
 * @param lineNumber El número de línea en el archivo.
 */
void CodeAnalyzer::AnalyzeVariables(const std::string& line, int lineNumber, variableHandler& variables) {
  std::regex int_variable(R"(int\s+(\w+)\s*(=\s*([\w\d\.]+))?\s*\;)");
  std::regex double_variable(R"(double\s+(\w+)\s*(=\s*([\w\d\.]+))?\s*\;)");
  std::smatch match;

  if (std::regex_search(line, match, int_variable)) {
    variables.StoreIntVariable(lineNumber, match);
  } else if (std::regex_search(line, match, double_variable)){
    variables.StoreDoubleVariable(lineNumber, match);
  }
}

/**
 * @brief Detecta bucles y rastrea su alcance.
 *
 * Verifica si una línea contiene 'for' o 'while', registra el tipo de bucle y su número de línea.
 * Rastrea el alcance del bucle contando llaves de apertura y cierre.
 *
 * @param line Línea de código actual.
 * @param lineNumber Número de línea actual.
 * @param input Flujo de archivo de entrada.
 */
void CodeAnalyzer::AnalyzeLoops(const std::string& line, int& lineNumber, std::ifstream& input, loopsHandler& loops) {
  std::regex for_regex (R"(for\s*\(.*\))");
  if (std::regex_search(line, for_regex)) {
    loops.StoreForLoops(lineNumber);
  } else {
    loops.StoreWhileLoops(lineNumber);
  }
  
  // Contador de llaves
  int openBraces = 0;
  int closeBraces = 0;
  // Verificar si la primera línea del bucle contiene una llave de apertura
  if (line.find('{') != std::string::npos) {
    openBraces++;
  }
  // Leer el resto del bloque del bucle
  std::string for_line;
  while (std::getline(input, for_line)) {
    lineNumber++;  
    // Contar las llaves de apertura y cierre
    if (for_line.find('{') != std::string::npos) {
      openBraces++;
    }
    if (for_line.find('}') != std::string::npos) {
      closeBraces++;
    }
    // Si hemos cerrado todas las llaves de apertura, salimos de la función
    if (openBraces > 0 && openBraces == closeBraces) return;
  }
}

/**
 * @brief Detecta la función main en una línea de código.
 *
 * @param line La línea de código a analizar.
 */
void CodeAnalyzer::DetectMain(const std::string& line) {
    std::regex mainRegex(R"(int\s+main\s*\()");
    if (std::regex_search(line, mainRegex)) {
        has_main_ = true;
    }
}

/**
 * @brief Detecta y registra comentarios en una línea de código.
 *
 * @param line Línea de código actual.
 * @param lineNumber Número de línea actual.
 * @param input Flujo de archivo de entrada.
 */
void CodeAnalyzer::AnalyzeComments(const std::string& line, int& lineNumber, std::ifstream& input, commentHandler& comments) {
  std::regex single_line_comment(R"(//.*)");
  if (std::regex_search(line, single_line_comment)) {
    comments.StoreSingleLineComments(line, lineNumber);
  } else {
    std::regex end_multiline_comment(R"(\*\/)");
    int first_comment_line = lineNumber;
    std::string comment_line;

    while (std::getline(input, comment_line) && !(std::regex_search(comment_line, end_multiline_comment))) {
      ++lineNumber;
    }
    ++lineNumber;
    comments.StoreMultiLineComments(first_comment_line, lineNumber);
  }
}