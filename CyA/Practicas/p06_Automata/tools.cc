#include "tools.h"

void usage(int argc, char* argv[]) {
  if ((argc < 2) | (argc > 3)) argumentFail(argv);
  (argc == 3 ) ? checkFiles(argv) : checkHelp(argv);
}

void argumentFail(char* argv[]) {
  std::cout << "Numero incorrecto de argumentos, para mas informacion: " << argv[0] << " --help." << std::endl;
  exit(-1);
}

void checkFiles(char* argv[]) {
  std::ifstream user_input_file (argv[1]);
  std::ofstream user_output_file (argv[2]);
  if ( !user_input_file.is_open() | !user_output_file.is_open()) {
    std::cout << "No se pudo abrir los archivos. Comprueben que estos existan y/o esten en un estado usable" << std::endl;
    exit(-1);
  }
  return;
}


void checkHelp (char* argv[]) {
  std::string user_help_string = argv[1];
  if (user_help_string == "--help") {
     std::cout << "MODO DE USO\n" <<
    argv[0] << " inputfile.fa outputfile.txt\n" << 
    "DESCRIPCION DE LOS ARGUMENTOS:\n" <<
    " -inputfile.fa: Un fichero de texto en el que figura la especificación de un autómata finito\n" << 
    " -inputfile.txt: Un fichero de texto con extensión .txt en el que figura una serie de cadenas (una cadena por línea) sobre el alfabeto del autómata especificado en el primero de los ficheros." << std::endl;
  exit(0);
  }
  argumentFail(argv);
} 
  
 

