


#pragma once

#include <iostream>     // Para operaciones de entrada y salida
#include <string>       // Para manipulación de cadenas de texto
#include <string_view>  // Para vistas de cadenas de texto
#include <sstream>      // Para manipulación de cadenas de texto en streams
#include <vector>       // Para el uso de vectores
#include <fstream>      // Para operaciones de archivo
#include <expected>     // Para manejo de valores esperados y errores
#include <unistd.h>     // Para llamadas al sistema POSIX
#include <fcntl.h>      // Para control de archivos
#include <sys/types.h>  // Para tipos de datos de sistema
#include <sys/stat.h>   // Para obtener información de archivos
#include <errno.h>      // Para manejo de errores del sistema
#include <sys/mman.h>   // Para manejo de memoria
#include "SafeFD.h"     // Para el manejo de descriptores de archivo
#include "SafeMap.h"    // Para el manejo de archivos mapeados en memoria



enum class ErrorCode {
  // Errores de argumentos (error fatal)
  UNKNOWN_OPTION,
  MISSING_FILE,
  MISSING_ARGUMENTS,
  // Errores de lectura (error leve)
  PERMISSION_DENIED,
  FILE_NOT_FOUND,
  // Otros errores
  OTHER_ERROR,
};


struct OpcionesAdmitidas {
  // Flags de opciones
  bool show_help_flag = false;
  bool verbose_flag = false;
  // Argumentos
  std::string filename;
  std::vector<std::string> aditional_arguments;
};

class SafeMap; // declaración adelantada

void show_help();

std::expected<OpcionesAdmitidas, ErrorCode> parse_args(int argc, char* argv[]);
std::expected<std::string_view, int> read_all(const std::string& path);
void send_response(std::string_view header, std::string_view body = {});
std::string getenv(const std::string& name);