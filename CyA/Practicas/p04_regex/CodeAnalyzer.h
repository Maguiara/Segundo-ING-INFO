#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <vector>

class CodeAnalyzer {
public:

    bool get_hasMain() {return has_main_;}

    void Analyze(const std::string& inputFile, const std::string& outputFile);
    void AnalyzeVariables(const std::string& line, int lineNumber);
    void AnalyzeLoops(const std::string& line, int lineNumber);
    void DetectMain(const std::string& line, int lineNumber);
    void AnalyzeComments(const std::string& line, int lineNumber);

private:
    std::vector<std::string> variables_;
    std::vector<std::string> loops_;
    std::vector<std::string> comments_;
    bool has_main_ = false;
};



