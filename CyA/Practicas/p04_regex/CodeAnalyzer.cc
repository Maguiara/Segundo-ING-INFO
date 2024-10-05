#include "CodeAnalyzer.h"



void CodeAnalyzer::Analyze(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream input(inputFile);
    std::ofstream output(outputFile);

    output << "PROGRAM: " << inputFile << std::endl;

    std::string line;
    int lineNumber = 0;
    
    while (std::getline(input, line)) {
        lineNumber++;
        AnalyzeVariables(line, lineNumber);
        AnalyzeLoops(line, lineNumber);
        DetectMain(line, lineNumber);
        AnalyzeComments(line, lineNumber);
    }


    output << "MAIN:\n" << (get_hasMain() ? "True" : "False") << "\n";
    
    input.close();
    output.close();
}

void CodeAnalyzer::AnalyzeVariables(const std::string& line, int lineNumber) {
    std::regex intRegex(R"(int\s+(\w+)\s*(=\s*[^\;]*)?\;)");
    std::regex doubleRegex(R"(double\s+(\w+)\s*(=\s*[^\;]*)?\;)");
    std::smatch match;

    if (std::regex_search(line, match, intRegex)) {
       variables_.push_back("[LINE " + std::to_string(lineNumber) + " ]");
    }
    
    if (std::regex_search(line, match, doubleRegex)) {
        std::cout << "[Line " << lineNumber << "] DOUBLE: " << match[1] << "\n";
    }
}

void CodeAnalyzer::AnalyzeLoops(const std::string& line, int lineNumber) {
    std::regex forRegex(R"(for\s*\(.*\))");
    std::regex whileRegex(R"(while\s*\(.*\))");

    if (std::regex_search(line, forRegex)) {
        std::cout << "[Line " << lineNumber << "] LOOP: for\n";
    }
    
    if (std::regex_search(line, whileRegex)) {
        std::cout << "[Line " << lineNumber << "] LOOP: while\n";
    }
}

void CodeAnalyzer::DetectMain(const std::string& line, int lineNumber) {
    std::regex mainRegex(R"(int\s+main\s*\()");
    if (std::regex_search(line, mainRegex)) {
        has_main_ = true;
    }
}

void CodeAnalyzer::AnalyzeComments(const std::string& line, int lineNumber) {
    std::regex singleLineComment(R"(//.*)");
    std::regex multiLineComment(R"(\/\*[\s\S]*?\*\/)");
    if (std::regex_search(line, singleLineComment)) {
        std::cout << "[Line " << lineNumber << "] Comment: " << line << "\n";
    }
    
    if (std::regex_search(line, multiLineComment)) {
        std::cout << "[Line " << lineNumber << "] Multi-line comment detected\n";
    }
}

