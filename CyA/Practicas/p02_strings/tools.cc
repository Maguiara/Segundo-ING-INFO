/**
 * @file tools.cc
 * @brief Implementación de las funciones herramienta.
 * Contiene la implementación de las funciones herramienta contenidas en el programa
 * para indicar al usuario el correcto funcionamiento del código.
 * 
 * @details
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Computabilidad y Algoritmia
 * Curso: 2º
 * Práctica 2: Cadenas y lenguajes
 * 
 * @author Marco Aguiar Álvarez
 * @date 19/09/2024
 * @note Correo: alu0101620961@ull.edu.es
 */

#include "tools.h"
#include "mystring.h"
#include "language.h"
#include "alphabet.h"

/** @brief: Funcion que explica al usuario que funcionalidad tiene el programa, y en caso de recibir la cadena
    "--help" indicara por pantalla una breve descripcion sobre como usar el programa.
    @param argc: numero de argumentos pasados por linea de comandos.
    @param argv: vector que contiene los argumentos pasados por linea de comando
*/
void usage (int argc, char* argv[]) {
    if(argc != 4 && argc != 2)  {
        errorMessage(argv);
    }
    (argc == 4) ? checkFiles(argv) : checkHelp(argv);
}

/**
 * @brief Verifica si los archivos de entrada y salida pueden ser abiertos.
 *
 * Esta función intenta abrir los archivos de entrada y salida especificados por los argumentos de la línea de comandos.
 * Si alguno de los archivos no puede ser abierto, imprime un mensaje de error y termina el programa.
 * Si ambos archivos se abren correctamente, procede a verificar el opcode.
 *
 * @param argv Array de argumentos de la línea de comandos. 
 *             argv[1] debe ser la ruta al archivo de entrada.
 *             argv[2] debe ser la ruta al archivo de salida.
 */
void checkFiles(char* argv[]) {
  std::ifstream user_input_file (argv[1]);
  std::ofstream user_output_file (argv[2]);
  if ( !user_input_file.is_open() || !user_output_file.is_open()) {
    std::cout << "No se pudo abrir los archivos. Comprueben que estos existan y/o esten en un estado usable" << std::endl;
    exit(-1);
  }
  checkOpcode(argv);
}

/**
 * @brief Verifica si se ha solicitado la ayuda del programa y muestra la información correspondiente.
 *
 * Esta función comprueba si el primer argumento pasado al programa es "--help". 
 * Si es así, imprime en la consola información detallada sobre el uso del programa, 
 * incluyendo la descripción de los ficheros de entrada y salida, así como las operaciones 
 * (opcodes) disponibles y su significado. Tras mostrar la información, el programa se cierra.
 *
 * @param argv[] Array que contiene los argumentos pasados al programa.
 *               argv[1] debe contener la cadena "--help" para mostrar información acerca del programa
 */
void checkHelp (char* argv[]) {
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
  errorMessage(argv);
}

/**
 * @brief Verifica si el opcode proporcionado es válido.
 *
 * Convierte el tercer argumento en un entero y verifica si está en el rango 1-5.
 * Si no es válido, imprime un mensaje de error y llama a errorMessage.
 *
 * @param argv Array de argumentos proporcionados por el usuario.
 */
void checkOpcode (char* argv[]) {
  int user_opcode(std::stoi(argv[3]));
  if (user_opcode < 1 || user_opcode > 5) {
    std::cout << "Opcode incorrecto" << std::endl;
    errorMessage(argv);
  }
  return;
}

/**
 * @brief Muestra un mensaje de error y termina la ejecución del programa.
 *
 * Esta función imprime un mensaje de uso correcto del programa y luego
 * finaliza la ejecución con un código de error.
 *
 * @param argv[] Array de cadenas de caracteres que contiene los argumentos
 *               pasados al programa desde la línea de comandos.
 */
void errorMessage(char * argv[]) {
  std::cout << "Modo de empleo del programa P02-strings: " << argv[0] << " filein.txt fileout.txt opcode\n" << 
  "Para mas informacion acerca del programa pruebe: " << argv[0] << " --help " << std::endl;
  exit(-1);
}

/**
 * @brief Realiza diversas operaciones en función del código de operación proporcionado.
 *
 * Esta función lee cadenas y alfabetos desde un archivo de entrada y realiza una operación
 * específica basada en el código de operación (opcode) proporcionado. Los resultados de 
 * las operaciones se escriben en un archivo de salida.
 *
 * @param input_file Archivo de entrada desde el cual se leen las cadenas y alfabetos.
 * @param output_file Archivo de salida donde se escriben los resultados de las operaciones.
 * @param opcode Código de operación que determina la operación a realizar:
 *               - 1: Escribe el alfabeto de cada cadena en el archivo de salida.
 *               - 2: Escribe el tamaño de cada cadena en el archivo de salida.
 *               - 3: Invierte cada cadena y la escribe en el archivo de salida.
 *               - 4: Genera y escribe los prefijos de cada cadena en el archivo de salida.
 *               - 5: Genera y escribe los sufijos de cada cadena en el archivo de salida.
 */
void operations(std::ifstream& input_file, std::ofstream& output_file, const int opcode) {
  MyString user_string;
  Alphabet user_alphabet;
  Language prefix, sufix;
  while (input_file >> user_string >> user_alphabet) {
    switch (opcode) {
    case 1:
        output_file << user_alphabet << std::endl;
      break;
    case 2:
        output_file << user_string.getSize() << std::endl;
      break;
    case 3:
        user_string.Invert();
        output_file << user_string << std::endl;
      break;
    case 4:
        prefix.Prefix(user_string);
        output_file << prefix << std::endl;
        prefix.clear(); 
      break;
    case 5:
        sufix.Sufix(user_string);
        output_file << sufix << std::endl;
        sufix.clear();
      break;
    default:
      break;
    }
  }
}