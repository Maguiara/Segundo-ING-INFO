#include "CodeAnalyzer.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Uso: ./p04_code_analyzer <input_file> <output_file>\n";
        return 1;
    }

    CodeAnalyzer analyzer;
    analyzer.analyze(argv[1], argv[2]);

    return 0;
}

