#include <iostream>
#include <fstream>
#include <regex>
#include <string>

class CodeAnalyzer {
public:
    void analyze(const std::string& inputFile, const std::string& outputFile);
private:
    void analyze_variables(const std::string& line, int lineNumber);
    void analyze_loops(const std::string& line, int lineNumber);
    void detect_main(const std::string& line, int lineNumber);
    void analyze_comments(const std::string& line, int lineNumber);
    
    bool hasMain = false;
};

