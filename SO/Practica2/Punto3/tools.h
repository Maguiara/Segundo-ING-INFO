


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
#include <errno.h>      // Para errno
#include <sys/mman.h>   // Para mmap
#include <cstring>      // Para strerror
#include <netinet/in.h> // Para sockaddr_in
#include <sys/socket.h> // Para socket, bind, listen
#include <arpa/inet.h>  // Para htons
#include <cstdlib>      // Para EXIT_SUCCESS, EXIT_FAILURE, std::getenv
#include <cstdint>      // Para uint16_t
#include <limits.h>    // Para PATH_MAX
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
  bool port_flag = false;
  // Argumentos
  // Ya no hace falta obligar a que haya un archivo
  std::string filename;
  std::vector<std::string> aditional_arguments;
  int port = 8080;
  std::string base_path = "/home/usuario";
};

class SafeMap; // declaración adelantada
class SafeFD;  // declaración adelantada

void show_help();

std::expected<OpcionesAdmitidas, ErrorCode> parse_args(int argc, char* argv[]);
std::expected<SafeMap, int> read_all(const std::string& path, bool verbose);
std::expected<SafeFD, int> make_socket(uint16_t port, const bool verbose);
int listen_connection(const SafeFD& socket, const bool verbose);
std::expected<SafeFD, int> accept_connection(const SafeFD& socket, sockaddr_in& client_addr, const bool verbose);
std::expected<std::string, int> receive_request(const SafeFD& socket, size_t max_size, const bool verbose);


int send_response(const SafeFD& socket, std::string_view header, std::string_view body);

std::string getenv(const std::string& name);