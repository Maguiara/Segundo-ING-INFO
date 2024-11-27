


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
  bool stop_flag = false;
  // Argumentos
  std::string filename;
  std::vector<std::string> aditional_arguments;
};

class SafeMap; // declaración adelantada

void show_help();

std::expected<OpcionesAdmitidas, ErrorCode> parse_args(int argc, char* argv[]);
std::expected<SafeMap, int> read_all(const std::string& path, bool verbose, bool stop);
void send_response(std::string_view header, std::string_view body = {});
std::string getenv(const std::string& name);