#include "CodeAnalyzer.h"
#include "tools.h"

int main(int argc, char* argv[]) {
    usage(argc, argv);
    CodeAnalyzer analyzer;
    analyzer.analyze(argv[1], argv[2]);

}

