#include "CodeAnalyzer.h"
#include "tools.h"

int main(int argc, char* argv[]) {
    usage(argc, argv);
    CodeAnalyzer analyzer;
    analyzer.Analyze(argv[1], argv[2]);

}



/**
 * Hacer la clase variableHandler y las clases con igual nombre para los comentarios y para los bucles ç
 * Ademas de hacer la implementacion del metodo .store() en cada clase y hacer un metodo print para meterlo todo en 
 * el archivo de salida. Por otro lado cambiar la funcion Analyze con un if else para cada caso y asi ahorrar hacer 
 * todas las comprobaciones todo el rato. (Revisar chat gpt para acordarme de todo)
 */