#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <vector>

class CodeAnalyzer {
public:

    bool get_hasMain() {return has_main_;}

    void Analyze(const std::string& inputFile, const std::string& outputFile);
    void WriteOutput(const std::string& inputFile, const std::string& outputFile);

private:
    //Metodos que no son parte de la interfaz publica de la clase
    void AnalyzeVariables(const std::string& line, int lineNumber);
    void AnalyzeLoops(const std::string& line, int& lineNumber,  std::ifstream& input);
    void DetectMain(const std::string& line, int lineNumber);
    void AnalyzeComments(const std::string& line, int& lineNumber, std::ifstream& input);
    //Vectores que contienen los matches detectados
    std::vector<std::string> variables_;
    std::vector<std::string> loops_;
    std::vector<std::string> comments_;
    bool has_main_ = false;
};



