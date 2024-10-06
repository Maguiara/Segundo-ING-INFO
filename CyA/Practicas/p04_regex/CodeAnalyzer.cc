#include "CodeAnalyzer.h"



void CodeAnalyzer::Analyze(const std::string& inputfile, const std::string& outputfile) {
    std::ifstream input(inputfile);

    // Variables necesarias para el analisis del archivo
    std::string line;
    int lineNumber = 0;
    //Expresiones regulares para el analisis
    std::regex variableRegex(R"((int|double)\s+(\w+)\s*(=\s*[^\;]*)?\;)"); //Detecta las variables tipo int
    std::regex loopRegex(R"((for|while)\s*\(.*\)\s*\{)"); //Detecta los bucles
    std::regex mainRegex(R"(int\s+main\s*\()"); //Detecta el main
    std::regex singleLineCommentRegex(R"(\/\/.*)"); //Detecta los comentarios de una linea
    std::regex multiLineCommentRegex(R"(\/\*)"); //Detecta los inicios de comentarios multilinea
    
    
   // Leer el archivo línea por línea
    while (std::getline(input, line)) {
      lineNumber++;
        if (std::regex_search(line, variableRegex)) {
            AnalyzeVariables(line, lineNumber);
        } else if (std::regex_search(line, loopRegex)) {
            AnalyzeLoops(line, lineNumber, input);
        } else if (std::regex_search(line, singleLineCommentRegex) or std::regex_search(line, multiLineCommentRegex)) {
            AnalyzeComments(line, lineNumber, input);
        }
    } 
    WriteOutput(inputfile, outputfile);
    input.close();
}

void CodeAnalyzer::WriteOutput(const std::string& inputFile, const std::string& outputFile) {
  std::ofstream output(outputFile);
  output << "PROGRAM: " << inputFile << std::endl;
  //Falta hacer la parte de la descripcion
  output << "VARIABLES: \n";
  for (const auto& variable : variables_ ) {
    output << variable << std::endl;
  }

  output << "\n STATMENTS: \n";
  for (const auto& statment : loops_) {
    output << statment << std::endl;
  }

  output << "\n MAIN: \n" << (has_main_ ? "True" : "False");

  output << "\n COMMENTS: \n"; 
  for (const auto& comments : comments_) {
    output << comments << std::endl;
  }

}

void CodeAnalyzer::AnalyzeVariables(const std::string& line, int lineNumber) {
    std::regex intRegex(R"(int\s+(\w+)\s*(?:=\s*([\w\d\.]+))?\s*;)");
    std::regex doubleRegex(R"(double\s+(\w+)\s*(?:=\s*([\w\d\.]+))?\s*;)");
    std::smatch match;

    if (std::regex_search(line, match, intRegex)) {
      if (match[2].matched) {
       variables_.push_back("[LINE " + std::to_string(lineNumber) + " ] INT: " + match[1].str() + " = " + match[2].str());
      } else {
      variables_.push_back("[LINE " + std::to_string(lineNumber) + " ] INT: " + match[1].str());
      }
    }
    
    if (std::regex_search(line, match, doubleRegex)) {
      if (match[2].matched) { 
        variables_.push_back("[Line " + std::to_string(lineNumber) + "] DOUBLE: " + match[1].str() + " = " + match[2].str());
      } else {
        variables_.push_back("[Line " + std::to_string(lineNumber) + "] DOUBLE: " + match[1].str());
      }
    }
}

void CodeAnalyzer::AnalyzeLoops(const std::string& line, int& lineNumber, std::ifstream& input) {
  std::regex forRegex(R"(for\s*\(.*\))");
  std::regex whileRegex(R"(while\s*\(.*\))");

  if (std::regex_search(line, forRegex)) {
    loops_.push_back("[Line " + std::to_string(lineNumber) + "] LOOP: for");
  }
    
  if (std::regex_search(line, whileRegex)) {
    loops_.push_back("[Line " + std::to_string(lineNumber) + "] LOOP: while");
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
    lineNumber++;  // Incrementar el número de línea

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

void CodeAnalyzer::DetectMain(const std::string& line, int lineNumber) {
    std::regex mainRegex(R"(int\s+main\s*\()");
    if (std::regex_search(line, mainRegex)) {
        has_main_ = true;
    }
}

void CodeAnalyzer::AnalyzeComments(const std::string& line, int& lineNumber, std::ifstream& input) {
    std::regex singleLineComment(R"(//.*)");
    std::regex multiLineComment(R"(\/\*[\s\S])");
    if (std::regex_search(line, singleLineComment)) {
        comments_.push_back("[Line " + std::to_string(lineNumber) + "] Comment: " + line + ";");
    }
    
    if (std::regex_search(line, multiLineComment)) {
      std::regex end_multiline_comment(R"(\*\/)");
      int first_comment_line = lineNumber;
      std::string comment_line;

      while (std::getline(input, comment_line) && !(std::regex_search(comment_line, end_multiline_comment))) {
        lineNumber++;
      }
      comments_.push_back("[Lines " + std::to_string(first_comment_line) + " - " + std::to_string(lineNumber + 1) + " ] Multiline commemt detected");
    }
}