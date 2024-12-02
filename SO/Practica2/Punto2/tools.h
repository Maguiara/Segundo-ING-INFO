


#pragma once

#include <iostream>     
#include <string>       
#include <string_view>  
#include <sstream>      
#include <vector>       
#include <fstream>      
#include <expected>     // Para manejo de valores esperados y errores
#include <unistd.h>     // Para close, lseek, mmap
#include <fcntl.h>      // Para open
#include <sys/types.h>  // Para tipos de datos
#include <sys/stat.h>   // Para estructura stat
#include <errno.h>      // Para errno
#include <sys/mman.h>   // Para mmap
#include <cstring>      // Para strerror
#include <netinet/in.h> // Para sockaddr_in
#include <sys/socket.h> // Para socket, bind, listen
#include <arpa/inet.h>  // Para htons
#include <cstdlib>      // Para EXIT_SUCCESS, EXIT_FAILURE
#include <cstdint>      // Para uint16_t
#include "SafeFD.h"     // Para fd mas seguro
#include "SafeMap.h"    // Para mapear archivos



enum class ErrorCode {
  // Errores de argumentos (error fatal)
  UNKNOWN_OPTION,
  MISSING_FILE,
  MISSING_ARGUMENTS,
  // Errores de lectura de archivos (error leve)
  PERMISSION_DENIED,
  FILE_NOT_FOUND,
  // Otros errores (error fatal)
  OTHER_ERROR,
};


struct OpcionesAdmitidas {
  // Flags de opciones
  bool show_help_flag = false;
  bool verbose_flag = false;
  // Argumentos
  std::string filename;
  std::vector<std::string> aditional_arguments;
  int port = 8080;
};

class SafeMap; // declaración adelantada
class SafeFD;  // declaración adelantada

void show_help();

std::expected<OpcionesAdmitidas, ErrorCode> parse_args(int argc, char* argv[]);
std::expected<SafeMap, int> read_all(const std::string& path, bool verbose);
std::expected<SafeFD, int> make_socket(uint16_t port);
int listen_connection(const SafeFD& socket);
void send_response(std::string_view header, std::string_view body);

std::string getenv(const std::string& name);