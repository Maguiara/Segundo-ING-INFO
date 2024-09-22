 // Universidad de La Laguna
 // Escuela Superior de Ingeniería y Tecnología
 // Grado en Ingeniería Informática
 // Asignatura: Computabilidad y Algoritmia
 // Curso: 2º
 // Práctica 2: Cadenas y lenguajes
 // Autor: Marco Aguiar Álvarez
 // Correo: alu0101620961@ull.edu.es
 // Fecha: 19/09/2024
 // Archivo tools.cc: programa de herramientas.
 // Contiene la definicion de las funciones herramienta contenidas en el programa
 // para indicar al usuario el correcto funcionamiento del codigo
 // Historial de revisiones
 // 17/09/2024- Creación (primera versión) del código

#include "tools.h"
#include "mystring.h"
#include "language.h"
#include "alphabet.h"

/** @Brief: Funcion que explica al usuario que funcionalidad tiene el programa, y en caso de recibir la cadena
    "--help" indicara por pantalla una breve descripcion sobre como usar el programa
    @Param argc: numero de argumentos pasados por linea de comandos
           argv: vector que contiene los argumentos pasados por linea de comando

*/

void Usage (int argc, char* argv[]) {
    if(argc != 4 && argc != 2)  {
        ErrorMesagge(argv);
    }
    (argc == 4) ? CheckFiles(argv) : CheckHelp(argv);
}

void CheckFiles(char* argv[]) {
  std::ifstream user_input_file (argv[1]);
  std::ofstream user_output_file (argv[2]);
  if ( !user_input_file.is_open() || !user_output_file.is_open()) {
    std::cout << "No se pudo abrir los archivos. Comprueben que estos existan y/o esten en un estado usable" << std::endl;
    exit(-1);
  }
  CheckOpcode(argv);
}

void CheckHelp (char* argv[]) {
  std::string user_help_string = argv[1];
  if (user_help_string == "--help") {
    std::cout << "INFORMACIÓN ACERCA DEL PROGRAMA\n" <<
    "Ficheros: Los ficheros usados en este programa seran uno de entrada y uno de salida en dicho orden\n" <<
    "  Fichero de entrada: Fichero en formato .txt que contendra los datos necesarios para el correcto funcionamiento del programa\n" <<
    "  Fichero de salida: Fichero en el que se guardaran los resultados de las diferentes operaciones realizadas sobre los datos del fihcero de entrada\n" <<
    "  Opcode: Numeros desde el 1 hasta el 5 en el que cada uno de estos representan una operacion distina a realizar sobre los datos incluidos \n" <<
    "          en el fichero de entrada\n " <<
    "   1. Alfabeto: Muestra en el fichero de salida asociado el alfabeto al que esa asociado una cadena del fichero de entrada\n " <<
    "   2. Longitud: Muestra en el fichero de salida asociado la longitud de las cadenas del fichero de entrada\n " <<
    "   3. Inversa: Muestra en el fichero de salida la cadena inversa asociada a cada cadena del fichero de entrada\n " <<
    "   4. Prefijos: Muestra en el fichero de salida todos los prefijos asociados a cada cadena del fichero de entrada\n " <<
    "   5. Sufijos: Muestra en el fichero de salida todos los sujifos asociados a cada acadena del fichero de entrada\n " << std::endl;
    exit(-1);
  }
  ErrorMesagge(argv);
}


void CheckOpcode (char* argv[]) {
  int user_opcode(std::stoi(argv[3]));
  if (user_opcode < 1 || user_opcode > 5) {
    ErrorMesagge(argv);
  }
  return;
}


void ErrorMesagge(char * argv[]) {
  std::cout << "Modo de empleo del programa P02-strings: " << argv[0] << " filein.txt fileout.txt opcode\n" << 
  "Para mas informacion acerca del programa pruebe: " << argv[0] << " --help " << std::endl;
  exit(-1);
}


void Operations(std::ifstream& input_file, std::ofstream& output_file, const int opcode) {
  MyString user_string;
  Alphabet user_alphabet;
  switch (opcode) {
  case 1:
    while (input_file >> user_string >> user_alphabet) {
      output_file << user_alphabet << std::endl;
    }
    break;
  case 2:
    while (input_file >> user_string >> user_alphabet) {
      output_file << user_string.size() << std::endl;
    }
    break;
  case 3:
    while (input_file >> user_string >> user_alphabet) {
      user_string.Invert();
      output_file << user_string << std::endl;
    }
    break;
  case 4:
    while (input_file >> user_string >> user_alphabet) {
      Language prefix;
      prefix.Prefix(user_string);
      output_file << prefix << std::endl;
    }

    break;
  case 5:
    while (input_file >> user_string >> user_alphabet) {
      Language sufix;
      sufix.Sufix(user_string);
      output_file << sufix << std::endl;
    }
    break;
  
  default:
    break;
  }
}